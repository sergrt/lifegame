#pragma once

class Observer {
    ////////////////////////////////
    // Observer pattern class. Model class is the subject.
    // Class to be inherited by any entities, which want to be aware about
    // what is going on with Model.

protected:
    Observer() = default;

public:
    // Disabling copy constructor and copy assignment operator also disables
    // move constructor and move assignment operator.
    Observer(const Observer&) = delete;
    Observer& operator=(const Observer&) = delete;

    virtual ~Observer() = default;
    
    // Handler of the event that field dimensions has been changed
    virtual void fieldDimensionsChanged() {}

    // Handler of the event that field cells have been changed
    virtual void fieldChanged() {}

    // Handler of the event that step with number 'step' has been performed
    virtual void stepPerformed(int step) {}

    // Handler of the event that all cells are dead
    virtual void allCellsAreDead() {}

    // Handler of the event that step repeats last one
    virtual void stepStagnation() {}

    ////////////////////////////////
    // UI-related stuff

    // Handler of the event that simulation has been stopped
    virtual void simulationStopped() {}
};