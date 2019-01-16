#include "stdafx.h"
#include "controller.h"
#include "ui_life.h"

Controller::Controller() {
    model_ = std::make_unique<Model>();
    view_ = std::make_unique<Grid>(model_.get(), this);
}

void Controller::setupView(Ui::LifeClass* const ui) {
    ui->frameGrid->setLayout(new QGridLayout());
    ui->frameGrid->layout()->addWidget(view_.get());
    ui->manual->setChecked(fieldEditable_);

}

void Controller::randomize() const {
    model_->randomize();
}

void Controller::fieldItemClick(const std::pair<int, int>& c) const {
    model_->toggleFieldItem(c);
}

void Controller::setFieldEditable(bool v) {
    fieldEditable_ = v;
}
