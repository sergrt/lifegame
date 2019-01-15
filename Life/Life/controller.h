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
    std::unique_ptr<Model> model_;
    std::unique_ptr<Grid> view_;
};
