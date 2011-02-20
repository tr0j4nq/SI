#include "gameboard.h"

GameBoard::GameBoard(QWidget *parent) :
    QWidget(parent)
{
    scene = new QGraphicsScene;
    view = new QGraphicsView(scene,this);
    QHBoxLayout* layout = new QHBoxLayout;
    layout->addWidget(view);
    setLayout(layout);
    board.resize(7);
    for(int i=-3;i<=3;i++){
        board[i+3].resize(7-abs(i));
    }
}

void GameBoard::drawBoard(){
    scene->clear();
    for(int j=-3;j<=3;j++){
        if(j%2==0){
            for(int i=-350+abs(j*50);i<=250-abs(j*50);i+=100)
                scene->addEllipse(i,(j*86+50),100,100);
        }
        else{
            for(int i=-350+abs(j*50);i<=250-abs(j*50);i+=100){
                scene->addEllipse(i,(j*86+50),100,100);
            }

        }
    }
}

void GameBoard::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton){
        QPoint pos=event->pos();
    }
}
