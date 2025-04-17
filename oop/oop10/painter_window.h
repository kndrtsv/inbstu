#ifndef PAINTER_WINDOW_H
#define PAINTER_WINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QSpinBox>
#include <QColorDialog>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "paint_widget.h"

class PainterWindow : public QWidget {
    Q_OBJECT

public:
    explicit PainterWindow(QWidget *parent = nullptr);

private slots:
    void setPencil();
    void setEraser();
    void setLine();
    void setRect();
    void setEllipse();
    void chooseColor();
    void saveImage();
    void loadImage();

private:
    PaintWidget *paintWidget;
    QPushButton *btnPencil, *btnEraser, *btnLine, *btnRect, *btnEllipse;
    QPushButton *btnColor, *btnSave, *btnLoad;
    QSpinBox *spinThickness;
};

#endif // PAINTER_WINDOW_H
