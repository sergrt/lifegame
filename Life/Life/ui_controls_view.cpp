#include "stdafx.h"
#include "ui_controls_view.h"
#include "ui_life.h"
#include "model.h"
#include "controller.h"

UiControlsView::UiControlsView(Model* model, Controller* controller)
    : model_{ model },
    controller_{ controller }{
    
    model_->addObserver(this);
}
void UiControlsView::setUiPtr(Ui::LifeClass* const ui) {
    ui_ = ui;

    ui_->manual->setChecked(controller_->fieldEditable());
    ui_->speed->setValue(model_->simulationSpeed());


    // UI controls connections to the Controller.
    // Used as a simplest approach
    connect(ui_->randomize, &QPushButton::clicked, this, [this]() {
        controller_->randomize();
    });
    connect(ui_->manual, &QPushButton::clicked, this, [this]() {
        controller_->setFieldEditable(!ui_->manual->isChecked());
    });
    connect(ui_->runPause, &QPushButton::clicked, this, [this]() {
        const bool isRunning = !ui_->runPause->isChecked();
        if (isRunning)
            controller_->stopSimulation();
        else
            controller_->startSimulation();
    });
    connect(ui_->step, &QPushButton::clicked, this, [this]() {
        controller_->singleStep();
    });
    connect(ui->speed, &QSlider::valueChanged, this, [this]() {
        controller_->setSimulationSpeed(ui_->speed->value());
    });
}
UiControlsView::~UiControlsView() {
    model_->removeObserver(this);
}

void UiControlsView::simulationStopped() {
    if (ui_)
        ui_->runPause->setChecked(false);
}

void UiControlsView::stepPerformed(int step) {
    if (ui_)
        ui_->log->append(QString("Step performed: %1").arg(step));
}
void UiControlsView::allCellsAreDead() {
    if (ui_)
        ui_->log->append("All cells are dead");
}