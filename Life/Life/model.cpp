#include "stdafx.h"
#include "model.h"
#include "observer.h"
#include <random>

Model::Model() {
    simulationSpeed_ = 500;
    currentStep_ = 0;
    size_t fieldWidth_ = 24;
    size_t fieldHeight_ = 24;
    field_.resize(fieldHeight_);
    for (auto& f : field_)
        f.resize(fieldWidth_, 0);
    
    QObject::connect(&timer_, &QTimer::timeout, this, [this]() {
        lifeStep();
        notifyFieldChanged();
    });
    //timer_.start(500);
}

Model::~Model() {
}

void Model::notifyFieldDimensionsChanged() const {
    for (const auto observer : observers_)
        observer->fieldDimensionsChanged();
}
void Model::notifyFieldChanged() const {
    for (const auto observer : observers_)
        observer->fieldChanged();
}
void Model::notifySimulationStopped() const {
    for (const auto observer : observers_)
        observer->simulationStopped();
}
void Model::notifyStepPerformed(int step) const {
    for (const auto observer : observers_)
        observer->stepPerformed(step);
}
void Model::notifyAllCellsAreDead() const {
    for (const auto observer : observers_)
        observer->allCellsAreDead();
}

void Model::addObserver(Observer* observer) {
    observers_.push_back(observer);
}

void Model::removeObserver(Observer* observer) {
    observers_.erase(
        std::find(std::begin(observers_), std::end(observers_), observer)
    );
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

int Model::item(size_t row, size_t col) const {
    return field_[row][col];
}

int Model::neighboursCount(int row, int col) {
    int res = 0;
    for (int r = row - 1; r <= row + 1 && r < (int)field_.size(); ++r) {
        if (r >= 0) {
            for (int c = col - 1; c <= col + 1 && c < (int)field_[r].size(); ++c) {
                if (c >= 0) {
                    if (!(r == row && c == col))
                        res += item(r, c) == 1 ? 1 : 0;
                }
            }
        }
    }
    return res;
}

void Model::lifeStep() {
    auto newField = field_;
    for (size_t row = 0; row < field_.size(); ++row) {
        for (size_t col = 0; col < field_[row].size(); ++ col) {
            auto n = neighboursCount(row, col);
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
    notifyStepPerformed(++currentStep_);
    
    if (allCellsAreDead()) {
        notifyAllCellsAreDead();
        // TODO: maybe stop here
    }
}
bool Model::allCellsAreDead() const {
    for (const auto& row : field_) {
        for (const auto& cell : row) {
            if (cell != 0)
                return false;
        }
    }
    return true;
}

void Model::toggleFieldItem(Row row, Column col) {
    const auto oldVal = field_[row.get()][col.get()];
    field_[row.get()][col.get()] = oldVal == 0 ? 1 : 0;
    notifyFieldChanged();
}

void Model::startSimulation() {
    timer_.start(simulationSpeed_);
}
void Model::stopSimulation() {
    timer_.stop();
}
void Model::singleStep() {
    stopSimulation();
    notifySimulationStopped();
    lifeStep();
    notifyFieldChanged();
}
int Model::simulationSpeed() const {
    return simulationSpeed_;
}
void Model::setSimulationSpeed(int s) {
    simulationSpeed_ = s;
    if (timer_.isActive())
        timer_.start(simulationSpeed_);
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