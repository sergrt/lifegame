#include "stdafx.h"
#include "controller.h"
#include "ui_life.h"

Controller::Controller() {
    model_ = new Model();
    view_ = new Grid(model_, this);
}

void Controller::setupView(Ui::LifeClass* const ui) {
    ui->frameGrid->setLayout(new QGridLayout());
    ui->frameGrid->layout()->addWidget(view_);
}