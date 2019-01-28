#pragma once
#include <vector>

class Observer;

class Subject {
    ////////////////////////////////
    // Subject class of Observer pattern. Inherited by Model.

protected:
    Subject() = default;

public:
    // Disabling copy constructor and copy assignment operator also disables
    // move constructor and move assignment operator.
    Subject(const Subject&) = delete;
    Subject& operator=(const Subject&) = delete;
    virtual ~Subject() = default;

    // Register observer
    void addObserver(Observer* observer);

    // Unregister observer
    void removeObserver(Observer* observer);

    // Notify that field dimensions changed
    virtual void notifyFieldDimensionsChanged() const;

    // Notify that field content changed
    virtual void notifyFieldChanged() const;

    // Notify that simulation has been stopped
    virtual void notifySimulationStopped() const;

    // Notify that step was performed
    virtual void notifyStepPerformed(int step) const;

    // Notify that all cells detected as dead
    virtual void notifyAllCellsAreDead() const;

    // Notify that there were no changes since last step
    virtual void notifyStepStagnation() const;

private:
    // Observers to be notified
    std::vector<Observer*> observers_;
};
