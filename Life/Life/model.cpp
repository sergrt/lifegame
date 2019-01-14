#include "stdafx.h"
#include "model.h"
#include "observer.h"

Model::Model() {
    fieldWidth_ = 12;
    fieldHeight_ = 12;
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