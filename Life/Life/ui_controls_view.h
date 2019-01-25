#pragma once
#include "observer.h"

class Model;
class Controller;

namespace Ui {
    class LifeClass;
}

class UiControlsView : public QObject, public Observer {
    Q_OBJECT

public:
    UiControlsView(Model* model, Controller* controller);
    ~UiControlsView();
    virtual void simulationStopped() override;
    virtual void stepPerformed(int step) override;
    virtual void allCellsAreDead() override;
    virtual void stepStagnation() override;

    void setUiPtr(Ui::LifeClass* const ui);
private:
    Ui::LifeClass* ui_ = nullptr;
    void syncWidthLabelText() const;
    void syncHeightLabelText() const;

    Model* model_;
    Controller* controller_;
};
