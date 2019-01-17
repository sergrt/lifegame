#pragma once
#include <QTimer>
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
    void toggleFieldItem(const std::pair<size_t, size_t>& c);

    void startSimulation();
    void stopSimulation();
    void singleStep();
    int simulationSpeed() const;
    void setSimulationSpeed(int s);
private:
    std::vector<Observer*> observers_;
    size_t fieldWidth_;
    size_t fieldHeight_;

    std::vector<std::vector<int>> field_;

    QTimer timer_;
    int simulationSpeed_;
    int currentStep_;

    void notifyFieldDimensionsChanged() const;
    void notifyFieldChanged() const;
    void notifySimulationStopped() const;
    void notifyStepPerformed(int step) const;
    void notifyAllCellsAreDead() const;

    void lifeStep();
    int neighboursCount(int row, int col);
    bool allCellsAreDead() const;
public:
    // Accessors
    size_t width() const;
    size_t height() const;
    int item(size_t row, size_t col) const;
};

