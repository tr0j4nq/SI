#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("SIEGESTONES");
    newButton = new QPushButton("Nowa gra",this);

    QGridLayout* mainLayout = new QGridLayout;
    QHBoxLayout* buttonLayout = new QHBoxLayout;

    painter = new Painter(this);

    buttonLayout->addWidget(newButton);

    mainLayout->addLayout(buttonLayout,0,0);
    mainLayout->addWidget(painter,1,0);

    setLayout(mainLayout);
    showMaximized();
}

Widget::~Widget()
{

}
