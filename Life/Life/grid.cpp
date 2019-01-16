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
    cellWidth_ = (width - 1) / rowCount;
    cellHeight_ = (height - 1) / colCount;
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

void Grid::paintEvent(QPaintEvent* e) {
    QPainter painter(this);
    //painter.setRenderHint(QPainter::Antialiasing);
    
    const auto rowCount = model_->height();
    const auto colCount = model_->width();

    const auto cellW = cellWidth();
    const auto cellH = cellHeight();

    painter.setPen(QColor(0, 0, 0));

    for (size_t i = 0; i <= rowCount; ++i) {
        const float y = 0 + i * cellH;
        painter.drawLine(0, y, colCount * cellW, y);
    }

    for (size_t i = 0; i <= colCount; ++i) {
        const float x = 0 + i * cellW;
        painter.drawLine(x, 0, x, rowCount * cellH);
    }

    // Paint cells
    for (size_t row = 0; row < model_->height(); ++row) {
        for (size_t col = 0; col < model_->width(); ++col) {
            // get cell rect
            float x = col * cellW + 1;
            float y = row * cellH + 1;
            float cx = cellW - 1;
            float cy = cellH - 1;
            const auto color = model_->item(row, col) == 0 ? QColor(255, 255, 255) : QColor(0, 0, 0);
            const QBrush brush(color);
            painter.fillRect(x, y, cx, cy, brush);
        }
    }

    QWidget::paintEvent(e);
}

void Grid::fieldDimensionsChanged() {
    this->repaint();
}

void Grid::fieldChanged() {
    repaint();
}

std::pair<int, int> Grid::pointCoordsToFieldCoords(const QPoint& p) {
    auto res = std::make_pair<size_t, size_t>(
        static_cast<int>(p.y() / cellHeight()),
        static_cast<int>(p.x() / cellWidth()));
    
    return res;
}

void Grid::mousePressEvent(QMouseEvent* e) {
    const auto fieldCoords = pointCoordsToFieldCoords(e->pos());
    controller_->fieldItemClick(fieldCoords);

    QWidget::mousePressEvent(e);
}

void Grid::resizeEvent(QResizeEvent* e) {
    cellWidth_.reset();
    cellHeight_.reset();
    QWidget::resizeEvent(e);
}