#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QWidget>
#include <QtGui/QGraphicsScene>
#include <QtGui/QGraphicsView>
#include <QtGui/QHBoxLayout>
#include <QtGui/QMouseEvent>
#include <QPoint>



class GameBoard : public QWidget
{
    Q_OBJECT
public:
    explicit GameBoard(QWidget *parent = 0);
    void drawBoard();
    bool player1; //0-komputer,1-czlowiek
    bool player2; //0-komputer,1-czlowiek
    QVector<QVector<char> > board;
    void mousePressEvent(QMouseEvent *event);

signals:

public slots:

private:
    QGraphicsScene* scene;
    QGraphicsView* view;

};

#endif // GAMEBOARD_H
