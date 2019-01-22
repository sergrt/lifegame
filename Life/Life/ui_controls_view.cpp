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
    ui_->width->setValue(model_->width());
    syncWidthLabelText();
    ui_->height->setValue(model_->height());
    syncHeightLabelText();
    
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
    connect(ui_->speed, &QSlider::valueChanged, this, [this]() {
        controller_->setSimulationSpeed(ui_->speed->value());
    });
    connect(ui_->width, &QSlider::valueChanged, this, [this]() {
        syncWidthLabelText();        
        controller_->resizeField(ui_->width->value(),
            ui_->height->value());
    });
    connect(ui_->height, &QSlider::valueChanged, this, [this]() {
        syncHeightLabelText();
        ui_->heightLabel->setText(QString("%1").arg(ui_->height->value()));
        controller_->resizeField(ui_->width->value(),
            ui_->height->value());
    });
}
UiControlsView::~UiControlsView() {
    model_->removeObserver(this);
}

void UiControlsView::syncWidthLabelText() const {
    ui_->widthLabel->setText(QString("%1").arg(ui_->width->value()));
}
void UiControlsView::syncHeightLabelText() const {
    ui_->heightLabel->setText(QString("%1").arg(ui_->height->value()));
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
