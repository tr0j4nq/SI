#ifndef PAINTER_H
#define PAINTER_H

#include <QWidget>
#include <QtGui/QGraphicsScene>
#include <QtGui/QGraphicsView>
#include <QtGui/QHBoxLayout>

class Painter : public QWidget
{
    Q_OBJECT
public:
    explicit Painter(QWidget *parent = 0);

signals:

public slots:

private:
    QGraphicsScene* scene;
    QGraphicsView* view;

};

#endif // PAINTER_H
