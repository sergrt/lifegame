#include "stdafx.h"
#include "subject.h"
#include "observer.h"

void Subject::addObserver(Observer* observer) {
    observers_.push_back(observer);
}

void Subject::removeObserver(Observer* observer) {
    observers_.erase(
        std::find(std::begin(observers_), std::end(observers_), observer)
    );
}

void Subject::notifyFieldDimensionsChanged() const {
    for (const auto observer : observers_)
        observer->fieldDimensionsChanged();
}

void Subject::notifyFieldChanged() const {
    for (const auto observer : observers_)
        observer->fieldChanged();
}

void Subject::notifySimulationStopped() const {
    for (const auto observer : observers_)
        observer->simulationStopped();
}

void Subject::notifyStepPerformed(int step) const {
    for (const auto observer : observers_)
        observer->stepPerformed(step);
}

void Subject::notifyAllCellsAreDead() const {
    for (const auto observer : observers_)
        observer->allCellsAreDead();
}

void Subject::notifyStepStagnation() const {
    for (const auto observer : observers_)
        observer->stepStagnation();
}
