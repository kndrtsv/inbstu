#include "painter_window.h"
#include <QPushButton>
#include <QColorDialog>
#include <QFileDialog>
#include <QSpinBox>
#include <QHBoxLayout>
#include <QVBoxLayout>

PainterWindow::PainterWindow(QWidget *parent) : QWidget(parent)
{
    paintWidget = new PaintWidget;

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QHBoxLayout *toolLayout = new QHBoxLayout;
    QHBoxLayout *settingsLayout = new QHBoxLayout;

    QPushButton *btnPencil   = new QPushButton("Карандаш");
    QPushButton *btnEraser   = new QPushButton("Ластик");
    QPushButton *btnLine     = new QPushButton("Линия");
    QPushButton *btnRect     = new QPushButton("Прямоугольник");
    QPushButton *btnEllipse  = new QPushButton("Окружность");

    toolLayout->addWidget(btnPencil);
    toolLayout->addWidget(btnEraser);
    toolLayout->addWidget(btnLine);
    toolLayout->addWidget(btnRect);
    toolLayout->addWidget(btnEllipse);

    QPushButton *btnColor      = new QPushButton("Цвет");
    QSpinBox *spinThickness = new QSpinBox;
    QPushButton *btnSave       = new QPushButton("Сохранить");
    QPushButton *btnLoad       = new QPushButton("Загрузить");

    spinThickness->setRange(1, 100);
    spinThickness->setValue(5);

    settingsLayout->addWidget(btnColor);
    settingsLayout->addWidget(spinThickness);
    settingsLayout->addWidget(btnSave);
    settingsLayout->addWidget(btnLoad);

    mainLayout->addLayout(toolLayout);
    mainLayout->addLayout(settingsLayout);
    mainLayout->addWidget(paintWidget);

    setLayout(mainLayout);
    setWindowTitle("Painter");
    resize(900, 700);

    connect(btnPencil,  &QPushButton::clicked, this, &PainterWindow::setPencil);
    connect(btnEraser,  &QPushButton::clicked, this, &PainterWindow::setEraser);
    connect(btnLine,    &QPushButton::clicked, this, &PainterWindow::setLine);
    connect(btnRect,    &QPushButton::clicked, this, &PainterWindow::setRect);
    connect(btnEllipse, &QPushButton::clicked, this, &PainterWindow::setEllipse);

    connect(btnColor, &QPushButton::clicked, this, &PainterWindow::chooseColor);
    connect(spinThickness, QOverload<int>::of(&QSpinBox::valueChanged), paintWidget, &PaintWidget::setThickness);
    connect(btnSave, &QPushButton::clicked, this, &PainterWindow::saveImage);
    connect(btnLoad, &QPushButton::clicked, this, &PainterWindow::loadImage);
}

void PainterWindow::setPencil() {
    paintWidget->setShapeType(ShapeType::Pencil);
}

void PainterWindow::setEraser() {
    paintWidget->setShapeType(ShapeType::Eraser);
}

void PainterWindow::setLine() {
    paintWidget->setShapeType(ShapeType::Line);
}

void PainterWindow::setRect() {
    paintWidget->setShapeType(ShapeType::Rect);
}

void PainterWindow::setEllipse() {
    paintWidget->setShapeType(ShapeType::Ellipse);
}

void PainterWindow::chooseColor() {
    QColor color = QColorDialog::getColor(paintWidget->getColor(), this, "Выбрать цвет");
    if (color.isValid()) {
        paintWidget->setColor(color);
    }
}

void PainterWindow::saveImage() {
    QString fileName = QFileDialog::getSaveFileName(this, "Сохранить изображение", "", "PNG (*.png);;JPEG (*.jpg)");
    if (!fileName.isEmpty()) {
        paintWidget->saveImage(fileName);
    }
}

void PainterWindow::loadImage() {
    QString fileName = QFileDialog::getOpenFileName(this, "Загрузить изображение", "", "Images (*.png *.jpg *.bmp)");
    if (!fileName.isEmpty()) {
        paintWidget->loadImage(fileName);
    }
}
