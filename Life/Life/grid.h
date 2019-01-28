#pragma once
#include <QWidget>
#include "observer.h"
#include <optional>
#include "model_named_types.h"

class Model;
class Controller;

class Grid : public QWidget, public Observer {
    ////////////////////////////////
    // Grid class object is used to display field in a grid. Acts like a view
    // in MVC pattern
    Q_OBJECT

public:
    Grid(Model* model, Controller* controller);
    ~Grid();
    Grid(const Grid&) = delete;
    Grid(Grid&&) = delete;
    Grid& operator=(const Grid&) = delete;
    Grid& operator=(Grid&&) = delete;

    ////////////////////////////////
    // Observer member functions implementation

    // React on field dimensions changed - recalc cell dimensions and repaint
    virtual void fieldDimensionsChanged() override;

    // React on field content changed - repaint
    virtual void fieldChanged() override;

protected:
    ////////////////////////////////
    // Qt functions overrides to allow painting and field editing
    void paintEvent(QPaintEvent* e) override;
    void mousePressEvent(QMouseEvent* e) override;
    void resizeEvent(QResizeEvent* e) override;

private:
    ////////////////////////////////
    // Non-owning pointers to MVC pattern members
    Model* model_;
    Controller* controller_;

    ////////////////////////////////
    // Cached values - it is unnecessary to calculate cell dimensions every time
    // (only if widget size changed), so it is wise to cache these values
    std::optional<int> cellWidth_;
    std::optional<int> cellHeight_;
    
    // Return cell width. Calculate new value if needed, and cache it
    int cellWidth();

    // Return cell height. Calculate new value if needed, and cache it
    int cellHeight();

    // Calculate cell dimensions and cache new values
    void calcCellDimensions();

    // Alias type to explicitly work with rows and columns
    using FieldPoint = std::pair<Row, Column>;

    // Translate pixel coordinates to field row/column pair
    // This function cannot be const because it calls (indirectly) calculations
    // of cell dimensions if cache invalidated
    FieldPoint pointCoordsToFieldCoords(const QPoint& p);

    ////////////////////////////////
    // Drawing
    void paintGrid();
    void paintCells();
};
