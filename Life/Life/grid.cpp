#include "stdafx.h"
#include "grid.h"
#include "model.h"
#include "controller.h"

Grid::Grid(Model* model, Controller* controller)
    : model_{ model }, controller_{ controller } {
    model_->addObserver(this);
}

Grid::~Grid() {
    //model_->removeObserver(this);
}

void Grid::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    //painter.setRenderHint(QPainter::Antialiasing);

    const size_t rowCount = model_->height();
    const size_t colCount = model_->width();
    const int width = this->width();
    const int height = this->height();
    const int cellHeight = (height - 1) / colCount; // TODO: cache. Set as optional
    const int cellWidth = (width - 1) / rowCount;

    painter.setPen(QColor(0, 0, 0));

    for (size_t i = 0; i <= rowCount; ++i) {
        const float y = 0 + i * cellHeight;
        painter.drawLine(0, y, colCount * cellWidth, y);
    }

    for (size_t i = 0; i <= colCount; ++i) {
        const float x = 0 + i * cellWidth;
        painter.drawLine(x, 0, x, rowCount * cellHeight);
    }

    // Paint cells
    for (size_t row = 0; row < model_->height(); ++row) {
        for (size_t col = 0; col < model_->width(); ++col) {
            // get cell rect
            float x = col * cellWidth + 1;
            float y = row * cellHeight + 1;
            float cx = cellWidth-1;
            float cy = cellHeight-1;
            const QColor color = model_->item(row, col) == 0 ? QColor(255, 255, 255) : QColor(0, 0, 0);
            const QBrush brush(color);
            painter.fillRect(x, y, cx, cy, brush);
        }
    }
}

void Grid::fieldDimensionsChanged() {
    this->repaint();
}
void Grid::fieldChanged() {
    repaint();
}

std::pair<int, int> Grid::pointCoordsToFieldCoords(const QPoint& p) const {
    const size_t rowCount = model_->height();
    const size_t colCount = model_->width();
    const int width = this->width();
    const int height = this->height();
    const int cellHeight = (height - 1) / colCount; // TODO: cache. Set as optional
    const int cellWidth = (width - 1) / rowCount;

    auto res = std::make_pair<int, int>(p.y() / cellHeight, p.x() / cellWidth);
    return res;
}

void Grid::mousePressEvent(QMouseEvent* e) {
    if (controller_->fieldEditable()) {
        auto fieldCoords = pointCoordsToFieldCoords(e->pos());
        controller_->toggleFieldItem(fieldCoords);
    }

    QWidget::mousePressEvent(e);
}