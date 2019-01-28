#pragma once
#include <QTimer>
#include "model_named_types.h"
#include "subject.h"

class Model : public QObject, public Subject {
    ////////////////////////////////
    // Model class of MVC pattern. This class encapsulates field and simulation
    // routines
    Q_OBJECT

public:
    Model();

    ////////////////////////////////
    // Handlers of external events, fired by Controller

    // Set cells in a random state
    void randomize();

    // Toggle cell, indicated by supplied 'row' and 'col' to inverse state
    void toggleFieldItem(Row row, Column col);

    // Start simulation
    void startSimulation();

    // Stop simulation
    void stopSimulation();

    // Perform single simulation step. If simulation was running, this will
    // pause it after step is performed
    void singleStep();

    // Get delay between simulation steps
    int simulationStepDelay() const;

    // Set simulation speed
    void setSimulationSpeed(int speed);

    // Resize field to supplied dimensions
    void resizeField(size_t w, size_t h);

    // Reset model: clear field, reset step number etc.
    void reset();

private:
    ////////////////////////////////
    // Model data

    std::vector<std::vector<int>> field_;
        // Field - vector of rows
    QTimer timer_;
        // Timer used to perform automatic simulation run
    int stepDelay_;
        // Delay between simulation steps. Defines speed of the simulation
    int currentStep_;
        // Number of step of the simulation
    size_t previousHash_;
        // Hash of the previous field state. Used to detect field stagnation

    // Get if simulation is running
    bool simulationRunning() const;

    // Perform simulationStep
    void lifeStep();

    // Calculate number of alive neighbors of the cell, indicated by
    // supplied 'row' and 'col'
    int neighborsCount(int row, int col);

    // Check if all cells are dead
    bool allCellsAreDead() const;

    // Calculate hash of the current field state
    size_t calcFieldHash() const;

    // Combine hashes
    // This realization of hash combine function was taken from boost library
    // and considered safe
    template<typename T>
    void hashCombine(size_t& seed, const T& v) const {
        std::hash<T> hasher;
        seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }

public:
    ////////////////////////////////
    // Accessors

    // Get width of the field
    size_t width() const;
    
    // Get height of the field
    size_t height() const;
    
    // Get state of the cell at the position, indicated by supplied 'row' and
    // 'col'
    int item(Row row, Column col) const;
};

