#include "stdafx.h"
#include "grid.h"
#include "model.h"

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

    const size_t rowCount = 24;
    const size_t colCount = 24;
    const float width = this->width();
    const float height = this->height();
    const float cellHeight = (height - 1) / colCount;
    const float cellWidth = (width - 1) / rowCount;

    painter.setPen(QColor(0, 0, 0));

    for (size_t i = 0; i <= rowCount; ++i) {
        const float y = 0 + i * cellHeight;
        painter.drawLine(0, y, this->width(), y);
    }

    for (size_t i = 0; i <= colCount; ++i) {
        const float x = 0 + i * cellWidth;
        painter.drawLine(x, 0, x, this->height());
    }
}

void Grid::fieldDimensionsChanged() {
    this->repaint();
}
