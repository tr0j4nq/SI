#include "gameboard.h"
#include <QString>
#include <sstream>

using namespace std;

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
    ta[0]=0;ta[1]=0;ta[2]=0;ta[3]=0;ta[4]=1;ta[5]=1;ta[6]=1;ta[7]=1;ta[8]=1;ta[9]=2;ta[10]=2;ta[11]=2;ta[12]=2;ta[13]=2;ta[14]=2;ta[15]=3;ta[16]=3;ta[17]=3;ta[18]=3;ta[19]=3;ta[20]=3;ta[21]=3;ta[22]=4;ta[23]=4;ta[24]=4;ta[25]=4;ta[26]=4;ta[27]=4;ta[28]=5;ta[29]=5;ta[30]=5;ta[31]=5;ta[32]=5;ta[33]=6;ta[34]=6;ta[35]=6;ta[36]=6;
    tb[0]=0;tb[1]=1;tb[2]=2;tb[3]=3;tb[4]=0;tb[5]=1;tb[6]=2;tb[7]=3;tb[8]=4;tb[9]=0;tb[10]=1;tb[11]=2;tb[12]=3;tb[13]=4;tb[14]=5;tb[15]=0;tb[16]=1;tb[17]=2;tb[18]=3;tb[19]=4;tb[20]=5;tb[21]=6;tb[22]=0;tb[23]=1;tb[24]=2;tb[25]=3;tb[26]=4;tb[27]=5;tb[28]=0;tb[29]=1;tb[30]=2;tb[31]=3;tb[32]=4;tb[33]=0;tb[34]=1;tb[35]=2;tb[36]=3;
}

void GameBoard::drawBoard(){
    scene->clear();
    for(int j=-3;j<=3;j++){
        for(int i=-350+abs(j*50);i<=250-abs(j*50);i+=100){
            scene->addEllipse(i,(j*86+50),100,100);
            int x0,y0;
            x0=i+50;
            y0=j*86+100;
            QPolygon temp;
            for(int k=0;k<6;k++){
                int x,y;
                x=50*cos(PI*2*((double)1/6*k));
                y=50*sin(PI*2*((double)1/6*k));
                temp<<QPoint(x+x0,y+y0);
            }
            boardP.push_back(temp);
            boardC.push_back(QPoint(x0,y0));
        }
    }
    turn=0;
}

void GameBoard::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton){
        QPoint pos=QPoint((event->pos().x()-375),(event->pos().y()-225));
        for(int i=0;i<boardP.size();i++){
            if(boardP[i].containsPoint(pos,Qt::OddEvenFill)){
                drawStone(i);
                /*QString str;
                str.append(QString("%1").arg(pos.y()));
                QMessageBox msgbox;
                msgbox.setText(str);
                msgbox.exec();*/
                break;
            }
        }
    }
    else if(event->button()==Qt::RightButton){
        QPoint pos=QPoint((event->pos().x()-375),(event->pos().y()-225));
        for(int i=0;i<boardP.size();i++){
            if(boardP[i].containsPoint(pos,Qt::OddEvenFill)){
                drawTower(i);
                break;
            }
        }
    }
}

void GameBoard::drawStone(int n){
    if(!board[ta[n]][tb[n]]){
        if(!turn){
            if(colorP1==0)
                scene->addEllipse(boardC[n].x()-25,boardC[n].y()-25,50,50,QPen(QBrush(QColor(0,0,255)), 1),QBrush(QColor(0,0,255)));
            else if(colorP1==1)
                scene->addEllipse(boardC[n].x()-25,boardC[n].y()-25,50,50,QPen(QBrush(QColor(255,0,0)), 1),QBrush(QColor(255,0,0)));
            else if(colorP1==2)
                scene->addEllipse(boardC[n].x()-25,boardC[n].y()-25,50,50,QPen(QBrush(QColor(255,255,0)), 1),QBrush(QColor(255,255,0)));
            else
                scene->addEllipse(boardC[n].x()-25,boardC[n].y()-25,50,50,QPen(QBrush(QColor(0,255,0)), 1),QBrush(QColor(0,255,0)));
            board[ta[n]][tb[n]]=1;
        }
        else{
            if(colorP2==0)
                scene->addEllipse(boardC[n].x()-25,boardC[n].y()-25,50,50,QPen(QBrush(QColor(0,0,255)), 1),QBrush(QColor(0,0,255)));
            else if(colorP2==1)
                scene->addEllipse(boardC[n].x()-25,boardC[n].y()-25,50,50,QPen(QBrush(QColor(255,0,0)), 1),QBrush(QColor(255,0,0)));
            else if(colorP2==2)
                scene->addEllipse(boardC[n].x()-25,boardC[n].y()-25,50,50,QPen(QBrush(QColor(255,255,0)), 1),QBrush(QColor(255,255,0)));
            else
                scene->addEllipse(boardC[n].x()-25,boardC[n].y()-25,50,50,QPen(QBrush(QColor(0,255,0)), 1),QBrush(QColor(0,255,0)));
            board[ta[n]][tb[n]]=2;
        }
        turn=!turn;
    }
}

void GameBoard::drawTower(int n){
    if(!board[ta[n]][tb[n]]){
        scene->addEllipse(boardC[n].x()-35,boardC[n].y()-35,70,70,QPen(QBrush(QColor(210,105,30)), 1),QBrush(QColor(210,105,30)));
        board[ta[n]][tb[n]]=3;
        turn=!turn;
    }
}
