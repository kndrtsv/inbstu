#include "paint_widget.h"
#include <QMouseEvent>
#include <QPainter>
#include <QPen>

PaintWidget::PaintWidget(QWidget *parent) : QWidget(parent), image(new QImage(size(), QImage::Format_RGB32)), currentColor(Qt::black), currentThickness(10), drawing(false), currentShape(ShapeType::Pencil)
{
    image->fill(Qt::white);
    setAttribute(Qt::WA_StaticContents);
}

void PaintWidget::setColor(const QColor &c) {
    currentColor = c;
}

QColor PaintWidget::getColor() const {
    return currentColor;
}

void PaintWidget::setThickness(int t) {
    currentThickness = t;
}

int PaintWidget::getThickness() const {
    return currentThickness;
}

void PaintWidget::setShapeType(ShapeType s) {
    currentShape = s;
}

void PaintWidget::saveImage(const QString &path) {
    image->save(path);
}

void PaintWidget::loadImage(const QString &path) {
    QImage loaded;
    if (loaded.load(path)) {
        image = smart_ptr<QImage>(new QImage(loaded));
        update();
    }
}

void PaintWidget::paintEvent(QPaintEvent*) {
    QPainter p(this);
    p.drawImage(0, 0, *image);
    if (drawing && (currentShape==ShapeType::Line || currentShape==ShapeType::Rect || currentShape==ShapeType::Ellipse)) {
        QPen pen(currentColor, currentThickness, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin);
        p.setPen(pen);
        drawShape(p, startPoint, currentPoint);
    }
}

void PaintWidget::resizeEvent(QResizeEvent *evt) {
    if (width() > image->width() || height() > image->height()) {
        QImage newImage(size(), QImage::Format_RGB32);
        newImage.fill(Qt::white);
        QPainter p(&newImage);
        p.drawImage(0, 0, *image);
        image = smart_ptr<QImage>(new QImage(newImage));
    }
    QWidget::resizeEvent(evt);
}

void PaintWidget::mousePressEvent(QMouseEvent *evt) {
    if (evt->button() != Qt::LeftButton) return;
    drawing = true;
    startPoint = evt->pos();
    currentPoint = startPoint;
    if (currentShape==ShapeType::Pencil || currentShape==ShapeType::Eraser)
        lastPoint = evt->pos();
}

void PaintWidget::mouseMoveEvent(QMouseEvent *evt) {
    if (!drawing) return;
    if (currentShape==ShapeType::Pencil || currentShape==ShapeType::Eraser) {
        QPainter p(image.get());
        QColor col = (currentShape==ShapeType::Eraser ? Qt::white : currentColor);
        p.setPen(QPen(col, currentThickness, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        p.drawLine(lastPoint, evt->pos());
        lastPoint = evt->pos();
        update();
    } else {
        currentPoint = evt->pos();
        update();
    }
}

void PaintWidget::mouseReleaseEvent(QMouseEvent *evt) {
    if (evt->button()!=Qt::LeftButton || !drawing) return;
    drawing = false;
    if (currentShape==ShapeType::Line || currentShape==ShapeType::Rect || currentShape==ShapeType::Ellipse) {
        QPainter p(image.get());
        QPen pen(currentColor, currentThickness, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin);
        p.setPen(pen);
        drawShape(p, startPoint, evt->pos());
        update();
    }
}

void PaintWidget::drawShape(QPainter &p, const QPoint &a, const QPoint &b) {
    switch (currentShape) {
    case ShapeType::Line:
        p.drawLine(a, b);
        break;
    case ShapeType::Rect:
        p.drawRect(QRect(a, b));
        break;
    case ShapeType::Ellipse:
        p.drawEllipse(QRect(a, b));
        break;
    default:
        break;
    }
}
