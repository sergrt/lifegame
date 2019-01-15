#include "stdafx.h"
#include "model.h"
#include "observer.h"

Model::Model() {
    fieldWidth_ = 12;
    fieldHeight_ = 12;
    field_.resize(fieldHeight_);
    for (auto& f : field_)
        f.resize(fieldWidth_, 0);

    //notifyFieldDimensionsChanged();
}

Model::~Model() {
}

void Model::notifyFieldDimensionsChanged() const {
    for (const auto observer : observers_)
        observer->fieldDimensionsChanged();
}

void Model::addObserver(Observer* observer) {
    observers_.push_back(observer);
}