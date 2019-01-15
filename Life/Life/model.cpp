#include "stdafx.h"
#include "model.h"
#include "observer.h"
#include <random>

Model::Model() {
    


    fieldWidth_ = 12;
    fieldHeight_ = 12;
    field_.resize(fieldHeight_);
    for (auto& f : field_)
        f.resize(fieldWidth_, 0);


    
    QObject::connect(&timer_, &QTimer::timeout, this, [this]() {
        notifyFieldChanged();
    });
    //timer_.start(5000);
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

void Model::randomize() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, 2);

    for (auto& row : field_) {
        for (auto& cell : row)
            cell = dist(mt) > 1 ? 1 : 0;
    }
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