#include "stdafx.h"
#include "model.h"
#include <random>

const auto initialFieldWidth = size_t(24);
const auto initialFieldHeight = size_t(24);

Model::Model()
    : stepDelay_{ 500 },
    currentStep_ { 0 },
    previousHash_ { 0 } {
    field_.resize(initialFieldHeight, std::vector<int>(initialFieldWidth, 0));

    // Set timer function - perform simulation step at every timeout
    QObject::connect(&timer_, &QTimer::timeout, this, [this]() {
        lifeStep();
    });
}

void Model::randomize() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, 2);
    /*
    for (auto& row : field_) {
        for (auto& cell : row)
            cell = dist(mt) > 1 ? 1 : 0;
    }
    */
    field_[0][1] = 1;
    
    field_[1][2] = 1;

    field_[2][0] = 1;
    field_[2][1] = 1;
    field_[2][2] = 1;
    notifyFieldChanged();
}

size_t Model::width() const {
    return field_[0].size();
}

size_t Model::height() const {
    return field_.size();
}

int Model::item(Row row, Column col) const {
    return field_[row.get()][col.get()];
}

int Model::neighborsCount(int row, int col) {
    int res = 0;
    for (int r = row - 1; r <= row + 1 && r < (int)field_.size(); ++r) {
        if (r >= 0) {
            for (int c = col - 1; c <= col + 1 && c < (int)field_[r].size(); ++c) {
                if (c >= 0) {
                    if (!(r == row && c == col))
                        res += item(Row(r), Column(c)) == 1 ? 1 : 0;
                }
            }
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
            if (field_[row][col] == 1) {
                if (n < 2)
                    newField[row][col] = 0;
                else if (n > 3)
                    newField[row][col] = 0;
            } else {
                if (n == 3)
                    newField[row][col] = 1;
            }
        }
    }
    field_ = newField;
    // This notification should be here to notify that step performed prior to
    // stagnation and all-cells-dead detections
    notifyStepPerformed(++currentStep_);

    const auto newHash = calcFieldHash();
    if (newHash == previousHash_) {
        notifyStepStagnation();
        stopSimulation();
    } else {
        previousHash_ = newHash;
        if (allCellsAreDead()) {
            notifyAllCellsAreDead();
            stopSimulation();
        }
    }
    notifyFieldChanged();
}

bool Model::allCellsAreDead() const {
    for (const auto& row : field_) {
        if (std::find_if(row.cbegin(), row.cend(), [](const int cell) { return cell != 0; }) != row.cend())
            return false;
    }
    return true;
}

void Model::toggleFieldItem(Row row, Column col) {
    const auto oldVal = field_[row.get()][col.get()];
    field_[row.get()][col.get()] = oldVal == 0 ? 1 : 0;
    notifyFieldChanged();
}

void Model::startSimulation() {
    timer_.start(stepDelay_);
}

void Model::stopSimulation() {
    timer_.stop();
    notifySimulationStopped();
}

bool Model::simulationRunning() const {
    return timer_.isActive();
}

void Model::singleStep() {
    if (simulationRunning())
        stopSimulation();
    lifeStep();
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
    field_.resize(h, std::vector<int>(w, 0));
    
    for (size_t sz = std::min(height(), oldHeight), i = 0; i < sz; ++i)
        field_[i].resize(w, 0);

    if (oldHeight != height() || oldWidth != width())
        notifyFieldDimensionsChanged();
}

void Model::reset() {
    if (simulationRunning())
        stopSimulation();
    
    currentStep_ = 0;
    for (auto& row : field_)
        std::fill(row.begin(), row.end(), 0);
    
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
