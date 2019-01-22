#pragma once
#include "model.h"
#include "grid.h"
#include "ui_controls_view.h"

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
    void startSimulation() const;
    void stopSimulation() const;
    void singleStep() const;
    void setSimulationSpeed(int s) const;
    void resizeField(size_t width, size_t height) const;

    bool fieldEditable() const;
private:
    std::unique_ptr<Model> model_;
    std::unique_ptr<Grid> view_;
    std::unique_ptr<UiControlsView> uiControlsView_;

    bool fieldEditable_ = false;
};
