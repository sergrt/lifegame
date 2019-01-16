#pragma once
#include <QWidget>
#include "observer.h"
#include <optional>

class Model;
class Controller;

class Grid : public QWidget, public Observer {
    Q_OBJECT

public:
    Grid(Model* model, Controller* controller);
    Grid(const Grid&) = default;
    Grid(Grid&&) = default;
    Grid& operator=(const Grid&) = default;
    Grid& operator=(Grid&&) = default;

    ~Grid();

    // Observer
    virtual void fieldDimensionsChanged() override;
    virtual void fieldChanged() override;
protected:
    void paintEvent(QPaintEvent* e) override;
    void mousePressEvent(QMouseEvent* e) override;
    void resizeEvent(QResizeEvent* e) override;
private:
    Model* model_;
    Controller* controller_;

    // Cached values
    std::optional<int> cellWidth_;
    std::optional<int> cellHeight_;
    int cellWidth();
    int cellHeight();
    void calcCellDimensions();

    std::pair<int, int> pointCoordsToFieldCoords(const QPoint& p);
        // Cannot be const because it calls non-const functions.
        // TODO: think about it
};
