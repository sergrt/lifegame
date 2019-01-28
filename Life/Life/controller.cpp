#include "stdafx.h"
#include "controller.h"
#include "ui_life.h"

Controller::Controller()
    : fieldEditable_{ false } {
    model_ = std::make_unique<Model>();
    view_ = std::make_unique<Grid>(model_.get(), this);
    uiControlsView_ = std::make_unique<UiControlsView>(model_.get(), this);
}

void Controller::setupViews(Ui::LifeClass* const ui) const {
    // TODO: Here is a mix of abstraction layers, consider to refactor
    ui->frameGrid->setLayout(new QGridLayout());
    ui->frameGrid->layout()->addWidget(view_.get());

    uiControlsView_->setupUi(ui);
}

void Controller::randomize() const {
    model_->randomize();
}

void Controller::fieldItemClick(Row row, Column col) const {
    model_->toggleFieldItem(row, col);
}

void Controller::setFieldEditable(bool editable) {
    fieldEditable_ = editable;
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

void Controller::setSimulationSpeed(int speed) const {
    model_->setSimulationSpeed(speed);
}

bool Controller::fieldEditable() const {
    return fieldEditable_;
}
void Controller::resizeField(size_t width, size_t height) const {
    model_->resizeField(width, height);
}

void Controller::resetModel() const {
    model_->reset();
}
