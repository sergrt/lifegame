#include "stdafx.h"
#include "grid.h"
#include "model.h"
#include "controller.h"

Grid::Grid(Model* model, Controller* controller)
    : model_{ model },
    controller_{ controller } {

    model_->addObserver(this);
}

Grid::~Grid() {
    model_->removeObserver(this);
}

void Grid::calcCellDimensions() {
    const size_t rowCount = model_->height();
    const size_t colCount = model_->width();
    const int width = this->width();
    const int height = this->height();
    cellWidth_ = (width - 1) / colCount;
    cellHeight_ = (height - 1) / rowCount;
    qDebug(QString("cellWidth_ = %1, cellHeight = %2").arg(*cellWidth_).arg(*cellHeight_).toStdString().c_str());
}

int Grid::cellWidth() {
    if (!cellWidth_)
        calcCellDimensions();
    
    return *cellWidth_;
}

int Grid::cellHeight()  {
    if (!cellHeight_)
        calcCellDimensions();

    return *cellHeight_;
}

void Grid::paintGrid() {
    QPainter painter(this);
    painter.setPen(QColor(0, 0, 0));

    const auto rowCount = model_->height();
    const auto colCount = model_->width();
    const auto cellW = cellWidth();
    const auto cellH = cellHeight();

    // Draw grid
    for (size_t i = 0; i <= rowCount; ++i) {
        const int y = i * cellH;
        painter.drawLine(0, y, colCount * cellW, y);
    }

    for (size_t i = 0; i <= colCount; ++i) {
        const int x = i * cellW;
        painter.drawLine(x, 0, x, rowCount * cellH);
    }
}

void Grid::paintCells() {
    QPainter painter(this);
    const auto cellW = cellWidth();
    const auto cellH = cellHeight();

    const auto filledBrush = QBrush(QColor(0, 0, 0));
    const auto emptyBrush = QBrush(QColor(255, 255, 255));

    // Paint cells
    for (size_t row = 0; row < model_->height(); ++row) {
        for (size_t col = 0; col < model_->width(); ++col) {
            // get cell rect
            const int x = col * cellW + 1;
            const int y = row * cellH + 1;
            const int cx = cellW - 1;
            const int cy = cellH - 1;
            const auto& brush = model_->item(Row(row), Column(col)).isAlive() ? filledBrush : emptyBrush;
            painter.fillRect(x, y, cx, cy, brush);
        }
    }
}

void Grid::paintEvent(QPaintEvent* e) {
    paintGrid();
    paintCells();
    QWidget::paintEvent(e);
}

void Grid::fieldDimensionsChanged() {
    calcCellDimensions();
    this->repaint();
}

void Grid::fieldChanged() {
    repaint();
}

Grid::FieldPoint Grid::pointCoordsToFieldCoords(const QPoint& p) {
    auto res = std::make_pair<Row, Column>(
        Row(static_cast<int>(p.y() / cellHeight())),
        Column(static_cast<int>(p.x() / cellWidth())));
    
    return res;
}

void Grid::mousePressEvent(QMouseEvent* e) {
    const auto fieldPoint = pointCoordsToFieldCoords(e->pos());
    controller_->fieldItemClick(fieldPoint.first, fieldPoint.second);

    QWidget::mousePressEvent(e);
}

void Grid::resizeEvent(QResizeEvent* e) {
    cellWidth_.reset();
    cellHeight_.reset();
    QWidget::resizeEvent(e);
}