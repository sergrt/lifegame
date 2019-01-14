#pragma once
#include "model.h"
#include "grid.h"

namespace Ui {
    class LifeClass;
}

class Controller {
public:
    Controller();
    void setupView(Ui::LifeClass* const ui);
private:
    Model* model_;
    Grid* view_;
};
