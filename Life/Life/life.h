#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_life.h"
#include "controller.h"

class Life : public QMainWindow {
    ////////////////////////////////
    // Main class
    Q_OBJECT

public:
    Life(QWidget *parent = Q_NULLPTR);

private:
    Ui::LifeClass ui;
    Controller controller_;

protected:
    // Override paint event to perform initial setup of the MVC pattern
    // at first repaint
    void paintEvent(QPaintEvent*) override;
};
