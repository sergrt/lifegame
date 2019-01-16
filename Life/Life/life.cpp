#include "stdafx.h"
#include "life.h"

std::once_flag flagSetupView;

Life::Life(QWidget *parent)
    : QMainWindow(parent) {
    ui.setupUi(this);

    // UI controls connections to the Controller.
    // Used as a simplest approach
    connect(ui.randomize, &QPushButton::pressed, this, [this]() {
        controller_.randomize();
    });
    connect(ui.manual, &QPushButton::pressed, this, [this]() {
        controller_.setFieldEditable(!ui.manual->isChecked());
    });

}

void Life::paintEvent(QPaintEvent* event) {
    std::call_once(flagSetupView, [this]() {
        controller_.setupView(&ui);
        //applicationInitialized = true;
    });
}
