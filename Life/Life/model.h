#pragma once

class Observer;

class Model {
public:
    Model();
    ~Model();

    void addObserver(Observer* observer);
private:
    std::vector<Observer*> observers_;
    size_t fieldWidth_;
    size_t fieldHeight_;

    std::vector<std::vector<int>> field_;

    void notifyFieldDimensionsChanged() const;
};

