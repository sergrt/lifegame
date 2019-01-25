#pragma once
#include <QTimer>
#include "model_named_types.h"
class Observer;

class Model : public QObject {
    Q_OBJECT

public:
    Model();
    ~Model();

    void addObserver(Observer* observer);
    void removeObserver(Observer* observer);

    // External handlers
    void randomize();
    void toggleFieldItem(Row row, Column col);

    void startSimulation();
    void stopSimulation();
    void singleStep();
    int simulationSpeed() const;
    void setSimulationSpeed(int s);
    void resizeField(size_t w, size_t h);
private:
    std::vector<Observer*> observers_;
    std::vector<std::vector<int>> field_;

    QTimer timer_;
    int simulationSpeed_;
    int currentStep_;

    void notifyFieldDimensionsChanged() const;
    void notifyFieldChanged() const;
    void notifySimulationStopped() const;
    void notifyStepPerformed(int step) const;
    void notifyAllCellsAreDead() const;
    void notifyStepStagnation() const;

    void lifeStep();
    int neighboursCount(int row, int col);
    bool allCellsAreDead() const;

    size_t previousHash_;
    size_t calcFieldHash();
public:
    // Accessors
    size_t width() const;
    size_t height() const;
    int item(size_t row, size_t col) const;
};

