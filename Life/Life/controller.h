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

    // UI handling
    void randomize() const;
    void fieldItemClick(const std::pair<size_t, size_t>& c) const;

    void setFieldEditable(bool v);
private:
    std::unique_ptr<Model> model_;
    std::unique_ptr<Grid> view_;

    bool fieldEditable_ = false;
};
