#include "painter.h"

Painter::Painter(QWidget *parent) :
    QWidget(parent)
{
    scene = new QGraphicsScene;
    view = new QGraphicsView(scene,this);
    QHBoxLayout* layout = new QHBoxLayout;
    layout->addWidget(view);
    setLayout(layout);
}
