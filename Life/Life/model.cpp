#include "stdafx.h"
#include "model.h"
#include "observer.h"
#include <random>

Model::Model() {
    fieldWidth_ = 24;
    fieldHeight_ = 24;
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
    return fieldWidth_;
}

size_t Model::height() const {
    return fieldHeight_;
}

int Model::item(int row, int col) const {
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
}

void Model::toggleFieldItem(const std::pair<int, int>& c) {
    const auto oldVal = field_[c.first][c.second];
    field_[c.first][c.second] = oldVal == 0 ? 1 : 0;
    notifyFieldChanged();
}