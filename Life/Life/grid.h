#pragma once
#include <QWidget>
#include "observer.h"

class Model;
class Controller;

class Grid : public QWidget, public Observer {
    Q_OBJECT

public:
    Grid(Model* model, Controller* controller);
    ~Grid();

    // Observer
    virtual void fieldDimensionsChanged() override;
    virtual void fieldChanged() override;
protected:
    void paintEvent(QPaintEvent*) override;
private:
    Model* model_;
    Controller* controller_;
};
