#pragma once

class Observer {
    // TODO: make unconstructible
public:
    virtual void fieldDimensionsChanged() {}
    virtual void fieldChanged() {}

    // ui
    virtual void simulationStopped() {}

    // log
    virtual void stepPerformed(int step) {}
    virtual void allCellsAreDead() {}
};