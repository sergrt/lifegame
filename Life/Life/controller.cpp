#include "stdafx.h"
#include "controller.h"
#include "ui_life.h"

Controller::Controller() {
    model_ = std::make_unique<Model>();
    view_ = std::make_unique<Grid>(model_.get(), this);
    uiControlsView_ = std::make_unique<UiControlsView>(model_.get(), this);
}

void Controller::setupView(Ui::LifeClass* const ui) {
    ui->frameGrid->setLayout(new QGridLayout());
    ui->frameGrid->layout()->addWidget(view_.get());
    uiControlsView_->setUiPtr(ui);
}

void Controller::randomize() const {
    model_->randomize();
}

void Controller::fieldItemClick(const std::pair<size_t, size_t>& c) const {
    model_->toggleFieldItem(c);
}

void Controller::setFieldEditable(bool v) {
    fieldEditable_ = v;
}
void Controller::startSimulation() const {
    model_->startSimulation();
}
void Controller::stopSimulation() const {
    model_->stopSimulation();
}
void Controller::singleStep() const {
    model_->singleStep();
}
void Controller::setSimulationSpeed(int s) const {
    model_->setSimulationSpeed(s);
}

bool Controller::fieldEditable() const {
    return fieldEditable_;
}
void Controller::resizeField(size_t width, size_t height) const {
    model_->resizeField(width, height);
}
