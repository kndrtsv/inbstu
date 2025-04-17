#ifndef PAINT_WIDGET_H
#define PAINT_WIDGET_H

#include <QWidget>
#include <QImage>
#include <QColor>
#include <QPoint>
#include "smart_ptr.h"

enum class ShapeType { Pencil, Eraser, Line, Rect, Ellipse };

class PaintWidget : public QWidget {
    Q_OBJECT
public:
    explicit PaintWidget(QWidget *parent = nullptr);
    void setColor(const QColor &c);
    QColor getColor() const;
    void setThickness(int t);
    int getThickness() const;
    void setShapeType(ShapeType s);
    void saveImage(const QString &path);
    void loadImage(const QString &path);

protected:
    void paintEvent(QPaintEvent*) override;
    void resizeEvent(QResizeEvent*) override;
    void mousePressEvent(QMouseEvent*) override;
    void mouseMoveEvent(QMouseEvent*) override;
    void mouseReleaseEvent(QMouseEvent*) override;

private:
    void drawShape(QPainter &p, const QPoint &a, const QPoint &b);

    smart_ptr<QImage> image;
    QColor currentColor;
    int currentThickness;
    bool drawing;
    ShapeType currentShape;
    QPoint startPoint, currentPoint, lastPoint;
};

#endif // PAINT_WIDGET_H
