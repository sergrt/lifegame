#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_life.h"
#include "controller.h"

class Life : public QMainWindow {
    Q_OBJECT

public:
    Life(QWidget *parent = Q_NULLPTR);

private:
    Ui::LifeClass ui;
    Controller controller_;
protected:
    void paintEvent(QPaintEvent*) override;
};
