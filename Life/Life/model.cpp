#include "stdafx.h"
#include "model.h"
#include <random>

const auto initialFieldWidth = size_t(24);
const auto initialFieldHeight = size_t(24);

bool LifeEntity::isAlive() const {
    return value_ != 0;
}
void LifeEntity::setAlive(bool alive) {
    value_ = alive;
}


Model::Model()
    : stepDelay_{ 200 },
    currentStep_ { 0 } {

    field_.resize(initialFieldHeight, std::vector<LifeEntity>(initialFieldWidth, LifeEntity()));
    // Set timer function - perform simulation step at every timeout
    connect(&timer_, &QTimer::timeout, this, [this]() {
        lifeStep();
    });
}

void Model::randomize() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, 2);
    for (auto& row : field_) {
        for (auto& cell : row)
            cell.setAlive(dist(mt) > 1 ? true : false);
    }
    notifyFieldChanged();
}

void Model::spawnBlinker() {
    if (height() >= 4 && width() >= 3) {
        field_[1][2].setAlive(true);
        field_[2][2].setAlive(true);
        field_[3][2].setAlive(true);
        notifyFieldChanged();
    }
}

void Model::spawnToad() {
    if (height() >= 4 && width() >= 5) {
        field_[2][2].setAlive(true);
        field_[2][3].setAlive(true);
        field_[2][4].setAlive(true);
        field_[3][1].setAlive(true);
        field_[3][2].setAlive(true);
        field_[3][3].setAlive(true);
        notifyFieldChanged();
    }
}

void Model::spawnBeacon() {
    if (height() >= 5 && width() >= 5) {
        field_[1][1].setAlive(true);
        field_[1][2].setAlive(true);
        field_[2][1].setAlive(true);

        field_[3][4].setAlive(true);
        field_[4][3].setAlive(true);
        field_[4][4].setAlive(true);
        notifyFieldChanged();
    }
}

void Model::spawnGlider() {
    if (height() >= 3 && width() >= 3) {
        field_[0][1].setAlive(true);
        field_[1][2].setAlive(true);
        field_[2][0].setAlive(true);
        field_[2][1].setAlive(true);
        field_[2][2].setAlive(true);
        notifyFieldChanged();
    }
}

void Model::spawnLightweightSpaceship() {
    if (height() >= 6 && width() >= 7) {
        field_[2][3].setAlive(true);
        field_[2][4].setAlive(true);
        field_[2][5].setAlive(true);
        field_[2][6].setAlive(true);
        field_[3][6].setAlive(true);
        field_[4][6].setAlive(true);
        field_[5][5].setAlive(true);
        field_[3][2].setAlive(true);
        field_[5][3].setAlive(true);
        notifyFieldChanged();
    }
}

size_t Model::width() const {
    if (field_.empty())
        throw std::logic_error("Trying to get field width before field initialization");
    return field_[0].size();
}

size_t Model::height() const {
    if (field_.empty())
        throw std::logic_error("Trying to get field height before field initialization");
    return field_.size();
}

LifeEntity Model::item(Row row, Column col) const {
    return field_[row.get()][col.get()];
}

int Model::neighborsCount(size_t row, size_t col) {
    int res = 0;
    for (size_t r = std::max(0, static_cast<int>(row) - 1); r < std::min(row + 2, field_.size()); ++r) {
        for (size_t c = std::max(0, static_cast<int>(col) - 1); c < std::min(col + 2, field_[r].size()); ++c) {
            if (!(r == row && c == col))
                res += item(Row(r), Column(c)).isAlive() ? 1 : 0;
        }
    }
    return res;
}

void Model::lifeStep() {
    // Use Singe-entry single-exit here to allow all notifications to be fired
    auto newField = field_;
    for (size_t row = 0; row < field_.size(); ++row) {
        for (size_t col = 0; col < field_[row].size(); ++ col) {
            const auto n = neighborsCount(row, col);
            if (field_[row][col].isAlive()) {
                if (n < 2 || n > 3)
                    newField[row][col].setAlive(false);
            } else {
                if (n == 3)
                    newField[row][col].setAlive(true);
            }
        }
    }
    field_ = newField;
    // This notification should be here to notify that step performed prior to
    // stagnation and all-cells-dead detections
    notifyStepPerformed(++currentStep_);

    const auto newHash = calcFieldHash();
    // Only previous step is checked for repeated configuration, so periodic
    // oscillations are not detected as stagnation. To do this - use vector of
    // hashes and check for periodic repetitions
    if (!previousHashes_.empty() && newHash == previousHashes_[0]) {
        notifyStepStagnation();
        stopSimulation();
    } else {
        if (previousHashes_.empty())
            previousHashes_.push_back(newHash);
        else
            previousHashes_[0] = newHash;

        if (allCellsAreDead()) {
            notifyAllCellsAreDead();
            stopSimulation();
        }
    }
    notifyFieldChanged();
}

bool Model::allCellsAreDead() const {
    for (const auto& row : field_) {
        if (std::find_if(row.cbegin(), row.cend(), [](const auto cell) { return cell.isAlive(); }) != row.cend())
            return false;
    }
    return true;
}

void Model::toggleFieldItem(Row row, Column col) {
    const auto oldItem = field_[row.get()][col.get()];
    field_[row.get()][col.get()].setAlive(!oldItem.isAlive());
    notifyFieldChanged();
}

void Model::startSimulation() {
    timer_.start(stepDelay_);
}

void Model::stopSimulation() {
    timer_.stop();
    previousHashes_.clear();
    notifySimulationStopped();
}

bool Model::simulationRunning() const {
    return timer_.isActive();
}

void Model::singleStep() {
    if (simulationRunning())
        stopSimulation();
    lifeStep();
    previousHashes_.clear();
}

int Model::simulationStepDelay() const {
    return stepDelay_;
}

void Model::setSimulationSpeed(int speed) {
    stepDelay_ = speed;
    if (simulationRunning())
        startSimulation();
}

void Model::resizeField(size_t w, size_t h) {
    const size_t oldWidth = width();
    const size_t oldHeight = height();
    field_.resize(h, std::vector<LifeEntity>(w, LifeEntity()));
    
    for (size_t sz = std::min(height(), oldHeight), i = 0; i < sz; ++i)
        field_[i].resize(w, LifeEntity());

    if (oldHeight != height() || oldWidth != width())
        notifyFieldDimensionsChanged();
}

void Model::reset() {
    if (simulationRunning())
        stopSimulation();
    
    currentStep_ = 0;
    for (auto& row : field_)
        std::fill(row.begin(), row.end(), LifeEntity());
    
    notifyFieldChanged();
}

size_t Model::calcFieldHash() const {
    size_t seed = 0;
    for (const auto& row : field_) {
        for (const auto& cell : row)
            hashCombine(seed, cell);
    }
    return seed;
}
