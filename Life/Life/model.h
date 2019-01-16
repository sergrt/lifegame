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
    
private:
    std::vector<Observer*> observers_;
    size_t fieldWidth_;
    size_t fieldHeight_;

    std::vector<std::vector<int>> field_;

    QTimer timer_;

    void notifyFieldDimensionsChanged() const;
    void notifyFieldChanged() const;


    void lifeStep();
    int neighboursCount(int row, int col);
public:
    // Accessors
    size_t width() const;
    size_t height() const;
    int item(size_t row, size_t col) const;
};

