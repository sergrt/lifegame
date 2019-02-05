#pragma once
#include "observer.h"

class Model;
class Controller;

namespace Ui {
    class LifeClass;
}

class UiControlsView : public QObject, public Observer {
    ////////////////////////////////
    // View class of MVC pattern, implementing handling of ui-related stuff
    // except Grid (there is Grid class for this). All controls, log, etc. are
    // encapsulated here
    Q_OBJECT

public:
    // TODO: define custom copy constructor, move constructor, copy assignment 
    //       operator and move assignment operator
    UiControlsView(Model* model, Controller* controller);
    ~UiControlsView();

    ////////////////////////////////
    // Observer overrides

    // React on simulation stop:
    // - uncheck appropriate button
    // - log event
    virtual void simulationStopped() override;

    // React on step performed - log event
    virtual void stepPerformed(int step) override;

    // React on all cells death detection - log event
    virtual void allCellsAreDead() override;

    // React on stagnation event - log event
    virtual void stepStagnation() override;

    // Setup ui on the initialization by Controller.
    // - sync it with model state
    // - sync it with controller state
    // - setup signals/slots connections
    void setupUi(Ui::LifeClass* const ui);

private:
    Ui::LifeClass* ui_ = nullptr;
    // Set Width label text as related slider value
    void syncWidthLabelText() const;

    // Set Height label text as related slider value
    void syncHeightLabelText() const;

    // Sync UI controls state with Model and Controller state
    void syncUi() const;

    // Set up signals/slots connecting UI elements with Controller
    void setupUiSignals();

    // Set up spawn button actions and handlers
    void setupSpawnButton();

    ////////////////////////////////
    // Non-owning pointers to MVC objects
    Model* model_;
    Controller* controller_;
};
