#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QWidget>
#include <QtGui/QGraphicsScene>
#include <QtGui/QGraphicsView>
#include <QtGui/QHBoxLayout>
#include <QtGui/QMouseEvent>
#include <QtGui/QMessageBox>
#include <QtGui/QApplication>
#include <QPoint>
#include <math.h>

#define PI 3.14159265

class GameBoard : public QWidget
{
    Q_OBJECT
public:
    explicit GameBoard(QWidget *parent = 0);
    void drawBoard();
    bool player[2]; //0-komputer,1-czlowiek
    char compAI[2];
    char compDepth[2];
    QVector<QVector<char> > board; //aktualny stan planszy, 0-brak piona, 1-p1, 2-p2, 3-wieza
    QVector<QPolygon> boardP;
    QVector<QPoint> boardC;
    void mousePressEvent(QMouseEvent *event);
    void drawStone(int n);
    int abCheck(char abBoard[37],bool type);
    int abNextTurn;
    bool abTowerTurn;
    char ta[37];
    char tb[37];
    bool turn;
    int colorP1;
    int colorP2;
    int towers;
    void drawTower(int n);
    void gameClear();
    void checkStone(int n);
    void checkTower(int x,int y);
    void checkTower(int n);
    void countTowers();
    void randTurn();
    void abTurn();
    int alphabeta(char abBoard[37],int depth,int alpha,int beta, bool type);
    int whoseTowers[37];
    int haveTowers[2];
    bool gameOver;
    QVector<QVector<char> > pointP1;
    QVector<QVector<char> > pointP2;


signals:

public slots:

private:
    QGraphicsScene* scene;
    QGraphicsView* view;

};

#endif // GAMEBOARD_H
