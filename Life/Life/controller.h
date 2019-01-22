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

    // Initial setup of views
    void setupViews(Ui::LifeClass* const ui) const;


    ////////
    // UI messages handling

    // Randomize field
    void randomize() const;

    // Route click on cell
    void fieldItemClick(Row row, Column col) const;

    // Set field "editable", so click on cell sets/clears cell
    void setFieldEditable(bool editable);

    // Start simulation
    void startSimulation() const;

    // Stop simulation
    void stopSimulation() const;

    // Single simulation step
    void singleStep() const;

    // Set simulation speed to supplied value
    void setSimulationSpeed(int speed) const;

    // Resize field to supplied dimensions
    void resizeField(size_t width, size_t height) const;


    ////////
    // Getters

    // Get if field editable
    bool fieldEditable() const;

private:
    // MVC stuff
    std::unique_ptr<Model> model_;
    std::unique_ptr<Grid> view_; // Grid view
    std::unique_ptr<UiControlsView> uiControlsView_; // UI controls view

    bool fieldEditable_; // is field editable, i.e. click sets/clears cell
};
