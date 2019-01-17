#include "stdafx.h"
#include "life.h"

std::once_flag flagSetupView;

Life::Life(QWidget *parent)
    : QMainWindow(parent) {
    ui.setupUi(this);
}

void Life::paintEvent(QPaintEvent* event) {
    std::call_once(flagSetupView, [this]() {
        controller_.setupView(&ui);
        //applicationInitialized = true;
    });
}
