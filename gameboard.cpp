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
    pointP1.resize(7);
    pointP2.resize(7);
    for(int i=-3;i<=3;i++){
        board[i+3].resize(7-abs(i));
        pointP1[i+3].resize(7-abs(i));
        pointP2[i+3].resize(7-abs(i));
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
    for(int i=0;i<37;i++)
        whoseTowers[i]=0;
    haveTowers[0]=0;
    haveTowers[1]=0;
}

void GameBoard::mousePressEvent(QMouseEvent *event)
{
    if(!gameOver&&player[turn]){
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
        countTowers();
        if(haveTowers[0]==4&&haveTowers[0]!=haveTowers[1]){
            gameOver=true;
            QMessageBox msgbox;
            msgbox.setText("Wygral gracz 1!");
            msgbox.exec();
        }
        if(haveTowers[1]==4&&haveTowers[0]!=haveTowers[1]){
            gameOver=true;
            QMessageBox msgbox;
            msgbox.setText("Wygral gracz 2!");
            msgbox.exec();
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
            pointP1[ta[n]][tb[n]]=6;
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
            pointP2[ta[n]][tb[n]]=6;
        }
        checkStone(n);
        turn=!turn;
    }
}

void GameBoard::drawTower(int n){
    if(!board[ta[n]][tb[n]]){
        if(!turn&&towers[turn]){
            scene->addEllipse(boardC[n].x()-35,boardC[n].y()-35,70,70,QPen(QBrush(QColor(210,105,30)), 1),QBrush(QColor(210,105,30)));
            board[ta[n]][tb[n]]=3;
            checkTower(n);
            towers[turn]--;
            turn=!turn;
            checkTower(n);
        }
        else if(turn&&towers[turn]){
            scene->addEllipse(boardC[n].x()-35,boardC[n].y()-35,70,70,QPen(QBrush(QColor(210,105,30)), 1),QBrush(QColor(210,105,30)));
            board[ta[n]][tb[n]]=3;
            checkTower(n);
            towers[turn]--;
            turn=!turn;
            checkTower(n);
        }
    }
}

void GameBoard::gameClear(){
    this->turn=0;
    for(int i=0;i<this->board.size();i++){
        for(int j=0;j<board[i].size();j++){
            this->board[i][j]=0;
            this->pointP1[i][j]=0;
            this->pointP2[i][j]=0;
        }
    }
}

void GameBoard::checkStone(int n){
    int x,y;
    x=ta[n];
    y=tb[n];
    if(board[x][y]==1){
        pointP1[ta[n]][tb[n]]=6;
        if(x==0){                   //pierwszy rzad planszy
            if(y<3){
                if(board[x][y+1]==3){
                    pointP1[x][y]-=1;
                }
            }
            if(y>0){
                if(board[x][y-1]==3){
                    pointP1[x][y]-=1;
                }
            }
            if(board[x+1][y]==3){
                pointP1[x][y]-=1;
            }
            if(board[x+1][y+1]==3){
                pointP1[x][y]-=1;
            }
        }
        else if(x>0&&x<3){          //drugi i trzeci rzad
            if(y<board[x].size()-1){
                if(board[x][y+1]==3){
                    pointP1[x][y]-=1;
                }
                if(board[x-1][y]==3){
                    pointP1[x][y]-=1;
                }
            }
            if(y>0){
                if(board[x][y-1]==3){
                    pointP1[x][y]-=1;
                }
                if(board[x-1][y-1]==3){
                    pointP1[x][y]-=1;
                }
            }
            if(board[x+1][y]==3){
                pointP1[x][y]-=1;
            }
            if(board[x+1][y+1]==3){
                pointP1[x][y]-=1;
            }
        }
        else if(x==3){              //rzad czwarty
            if(y<6){
                if(board[x][y+1]==3){
                    pointP1[x][y]-=1;
                }
                if(board[x-1][y]==3){
                    pointP1[x][y]-=1;
                }
                if(board[x+1][y]==3){
                    pointP1[x][y]-=1;
                }
            }
            if(y>0){
                if(board[x][y-1]==3){
                    pointP1[x][y]-=1;
                }
                if(board[x-1][y-1]==3){
                    pointP1[x][y]-=1;
                }
                if(board[x+1][y-1]==3){
                    pointP1[x][y]-=1;
                }
            }
        }
        else if(x>3&&x<6){          //5 i 6 rzad
            if(y<board[x].size()-1){
                if(board[x][y+1]==3){
                    pointP1[x][y]-=1;
                }
                if(board[x+1][y]==3){
                    pointP1[x][y]-=1;
                }
            }
            if(y>0){
                if(board[x][y-1]==3){
                    pointP1[x][y]-=1;
                }
                if(board[x+1][y-1]==3){
                    pointP1[x][y]-=1;
                }
            }
            if(board[x-1][y]==3){
                pointP1[x][y]-=1;
            }
            if(board[x-1][y+1]==3){
                pointP1[x][y]-=1;
            }
        }
        else if(x==6){                   //7 rzad planszy
            if(y<3){
                if(board[x][y+1]==3){
                    pointP1[x][y]-=1;
                }
            }
            if(y>0){
                if(board[x][y-1]==3){
                    pointP1[x][y]-=1;
                }
            }
            if(board[x-1][y]==3){
                pointP1[x][y]-=1;
            }
            if(board[x-1][y+1]==3){
                pointP1[x][y]-=1;
            }
        }
    }
    else if(board[x][y]==2){
        pointP2[ta[n]][tb[n]]=6;
        if(x==0){                   //pierwszy rzad planszy
            if(y<3){
                if(board[x][y+1]==3){
                    pointP2[x][y]-=1;
                }
            }
            if(y>0){
                if(board[x][y-1]==3){
                    pointP2[x][y]-=1;
                }
            }
            if(board[x+1][y]==3){
                pointP2[x][y]-=1;
            }
            if(board[x+1][y+1]==3){
                pointP2[x][y]-=1;
            }
        }
        else if(x>0&&x<3){          //drugi i trzeci rzad
            if(y<board[x].size()-1){
                if(board[x][y+1]==3){
                    pointP2[x][y]-=1;
                }
                if(board[x-1][y]==3){
                    pointP2[x][y]-=1;
                }
            }
            if(y>0){
                if(board[x][y-1]==3){
                    pointP2[x][y]-=1;
                }
                if(board[x-1][y-1]==3){
                    pointP2[x][y]-=1;
                }
            }
            if(board[x+1][y]==3){
                pointP2[x][y]-=1;
            }
            if(board[x+1][y+1]==3){
                pointP2[x][y]-=1;
            }
        }
        else if(x==3){              //rzad czwarty
            if(y<6){
                if(board[x][y+1]==3){
                    pointP2[x][y]-=1;
                }
                if(board[x-1][y]==3){
                    pointP2[x][y]-=1;
                }
                if(board[x+1][y]==3){
                    pointP2[x][y]-=1;
                }
            }
            if(y>0){
                if(board[x][y-1]==3){
                    pointP2[x][y]-=1;
                }
                if(board[x-1][y-1]==3){
                    pointP2[x][y]-=1;
                }
                if(board[x+1][y-1]==3){
                    pointP2[x][y]-=1;
                }
            }
        }
        else if(x>3&&x<6){          //5 i 6 rzad
            if(y<board[x].size()-1){
                if(board[x][y+1]==3){
                    pointP2[x][y]-=1;
                }
                if(board[x+1][y]==3){
                    pointP2[x][y]-=1;
                }
            }
            if(y>0){
                if(board[x][y-1]==3){
                    pointP2[x][y]-=1;
                }
                if(board[x+1][y-1]==3){
                    pointP2[x][y]-=1;
                }
            }
            if(board[x-1][y]==3){
                pointP2[x][y]-=1;
            }
            if(board[x-1][y+1]==3){
                pointP2[x][y]-=1;
            }
        }
        else if(x==6){                   //7 rzad planszy
            if(y<3){
                if(board[x][y+1]==3){
                    pointP2[x][y]-=1;
                }
            }
            if(y>0){
                if(board[x][y-1]==3){
                    pointP2[x][y]-=1;
                }
            }
            if(board[x-1][y]==3){
                pointP2[x][y]-=1;
            }
            if(board[x-1][y+1]==3){
                pointP2[x][y]-=1;
            }
        }
    }
    if(x==0){                   //pierwszy rzad planszy
        if(y<3){
            if(board[x][y+1]==3){
                checkTower(x,y+1);
            }
        }
        if(y>0){
            if(board[x][y-1]==3){
                checkTower(x,y-1);
            }
        }
        if(board[x+1][y]==3){
            checkTower(x+1,y);
        }
        if(board[x+1][y+1]==3){
            checkTower(x+1,y+1);
        }
    }
    else if(x>0&&x<3){          //drugi i trzeci rzad
        if(y<board[x].size()-1){
            if(board[x][y+1]==3){
                checkTower(x,y+1);
            }
            if(board[x-1][y]==3){
                checkTower(x-1,y);
            }
        }
        if(y>0){
            if(board[x][y-1]==3){
                checkTower(x,y-1);
            }
            if(board[x-1][y-1]==3){
                checkTower(x-1,y-1);
            }
        }
        if(board[x+1][y]==3){
            checkTower(x+1,y);
        }
        if(board[x+1][y+1]==3){
            checkTower(x+1,y+1);
        }
    }
    else if(x==3){              //rzad czwarty
        if(y<6){
            if(board[x][y+1]==3){
                checkTower(x,y+1);
            }
            if(board[x-1][y]==3){
                checkTower(x-1,y);
            }
            if(board[x+1][y]==3){
                checkTower(x+1,y);
            }
        }
        if(y>0){
            if(board[x][y-1]==3){
                checkTower(x,y-1);
            }
            if(board[x-1][y-1]==3){
                checkTower(x-1,y-1);
            }
            if(board[x+1][y-1]==3){
                checkTower(x+1,y-1);
            }
        }
    }
    else if(x>3&&x<6){          //5 i 6 rzad
        if(y<board[x].size()-1){
            if(board[x][y+1]==3){
                checkTower(x,y+1);
            }
            if(board[x+1][y]==3){
                checkTower(x+1,y);
            }
        }
        if(y>0){
            if(board[x][y-1]==3){
                checkTower(x,y-1);
            }
            if(board[x+1][y-1]==3){
                checkTower(x+1,y-1);
            }
        }
        if(board[x-1][y]==3){
            checkTower(x-1,y);
        }
        if(board[x-1][y+1]==3){
            checkTower(x-1,y+1);
        }
    }
    else if(x==6){                   //7 rzad planszy
        if(y<3){
            if(board[x][y+1]==3){
                checkTower(x,y+1);
            }
        }
        if(y>0){
            if(board[x][y-1]==3){
                checkTower(x,y-1);
            }
        }
        if(board[x-1][y]==3){
            checkTower(x-1,y);
        }
        if(board[x-1][y+1]==3){
            checkTower(x-1,y+1);
        }
    }
}

void GameBoard::checkTower(int x,int y){
    int p1=0;
    int p2=0;
    if(y>0){
        p1+=pointP1[x][y-1];
        p2+=pointP2[x][y-1];
    }
    if(y<board[x].size()-1){
        p1+=pointP1[x][y+1];
        p2+=pointP2[x][y+1];
    }
    if(x<3){
        p1+=pointP1[x+1][y];
        p1+=pointP1[x+1][y+1];
        p2+=pointP2[x+1][y];
        p2+=pointP2[x+1][y+1];
    }
    if(x>0 && x<3){
        if(y>0){
            p1+=pointP1[x-1][y-1];
            p2+=pointP2[x-1][y-1];
        }
        if(y<board[x].size()-1){
            p1+=pointP1[x-1][y];
            p2+=pointP2[x-1][y];
        }
    }
    if(x==3){
        if(y<6){
            p1+=pointP1[x-1][y];
            p1+=pointP1[x+1][y];
            p2+=pointP2[x-1][y];
            p2+=pointP2[x+1][y];
        }
        if(y>0){
            p1+=pointP1[x-1][y-1];
            p1+=pointP1[x+1][y-1];
            p2+=pointP2[x-1][y-1];
            p2+=pointP2[x+1][y-1];
        }
    }
    if(x>3 && x<6){
        if(y>0){
            p1+=pointP1[x+1][y-1];
            p2+=pointP2[x+1][y-1];
        }
        if(y<board[x].size()-1){
            p1+=pointP1[x+1][y];
            p2+=pointP2[x+1][y];
        }
    }
    if(x>3){
        p1+=pointP1[x-1][y];
        p1+=pointP1[x-1][y+1];
        p2+=pointP2[x-1][y];
        p2+=pointP2[x-1][y+1];
    }
    int n=0;
    for(int i=0;i<=x;i++){
        for(int j=0;j<board[i].size();j++){
            if(x==i && y==j)
                break;
            n++;
        }
    }
    if(p1>=5){
        if(p1>p2){
            whoseTowers[n]=1;
            if(colorP1==0)
                scene->addEllipse(boardC[n].x()-25,boardC[n].y()-25,50,50,QPen(QBrush(QColor(0,0,255)), 1),QBrush(QColor(0,0,255)));
            else if(colorP1==1)
                scene->addEllipse(boardC[n].x()-25,boardC[n].y()-25,50,50,QPen(QBrush(QColor(255,0,0)), 1),QBrush(QColor(255,0,0)));
            else if(colorP1==2)
                scene->addEllipse(boardC[n].x()-25,boardC[n].y()-25,50,50,QPen(QBrush(QColor(255,255,0)), 1),QBrush(QColor(255,255,0)));
            else
                scene->addEllipse(boardC[n].x()-25,boardC[n].y()-25,50,50,QPen(QBrush(QColor(0,255,0)), 1),QBrush(QColor(0,255,0)));
        }
    }
    if(p2>=5){
        if(p2>p1){
            whoseTowers[n]=2;
            if(colorP2==0)
                scene->addEllipse(boardC[n].x()-25,boardC[n].y()-25,50,50,QPen(QBrush(QColor(0,0,255)), 1),QBrush(QColor(0,0,255)));
            else if(colorP2==1)
                scene->addEllipse(boardC[n].x()-25,boardC[n].y()-25,50,50,QPen(QBrush(QColor(255,0,0)), 1),QBrush(QColor(255,0,0)));
            else if(colorP2==2)
                scene->addEllipse(boardC[n].x()-25,boardC[n].y()-25,50,50,QPen(QBrush(QColor(255,255,0)), 1),QBrush(QColor(255,255,0)));
            else
                scene->addEllipse(boardC[n].x()-25,boardC[n].y()-25,50,50,QPen(QBrush(QColor(0,255,0)), 1),QBrush(QColor(0,255,0)));
        }
    }
    if(p1==p2||(p2<5&&p1<5)){
        whoseTowers[n]=0;
        scene->addEllipse(boardC[n].x()-35,boardC[n].y()-35,70,70,QPen(QBrush(QColor(210,105,30)), 1),QBrush(QColor(210,105,30)));
    }
}

void GameBoard::checkTower(int n){
    int x,y;
    x=ta[n];
    y=tb[n];
    if(y>0){
        int nn=0;
        for(int i=0;i<=x;i++){
            for(int j=0;j<board[i].size();j++){
                if(x==i && y-1==j)
                    break;
                nn++;
            }
        }
        if(board[x][y-1]==1)
            checkStone(nn);
        else if(board[x][y-1]==2)
            checkStone(nn);
    }
    if(y<board[x].size()-1){
        int nn=0;
        for(int i=0;i<=x;i++){
            for(int j=0;j<board[i].size();j++){
                if(x==i && y+1==j)
                    break;
                nn++;
            }
        }
        if(board[x][y+1]==1)
            checkStone(nn);
        else if(board[x][y+1]==2)
            checkStone(nn);
    }
    if(x<3){
        int nn=0;
        for(int i=0;i<=x+1;i++){
            for(int j=0;j<board[i].size();j++){
                if(x+1==i && y==j)
                    break;
                nn++;
            }
        }
        if(board[x+1][y]==1)
            checkStone(nn);
        else if(board[x+1][y]==2)
            checkStone(nn);
        nn=0;
        for(int i=0;i<=x+1;i++){
            for(int j=0;j<board[i].size();j++){
                if(x+1==i && y+1==j)
                    break;
                nn++;
            }
        }
        if(board[x+1][y+1]==1)
            checkStone(nn);
        else if(board[x+1][y+1]==2)
            checkStone(nn);
    }
    if(x>0 && x<3){
        if(y>0){
            int nn=0;
            for(int i=0;i<=x-1;i++){
                for(int j=0;j<board[i].size();j++){
                    if(x-1==i && y-1==j)
                        break;
                    nn++;
                }
            }
            if(board[x-1][y-1]==1)
                checkStone(nn);
            else if(board[x-1][y-1]==2)
                checkStone(nn);
        }
        if(y<board[x].size()-1){
            int nn=0;
            for(int i=0;i<=x-1;i++){
                for(int j=0;j<board[i].size();j++){
                    if(x-1==i && y==j)
                        break;
                    nn++;
                }
            }
            if(board[x-1][y]==1||board[x-1][y]==2)
                checkStone(nn);
        }
    }
    if(x==3){
        if(y<6){
            int nn=0;
            for(int i=0;i<=x-1;i++){
                for(int j=0;j<board[i].size();j++){
                    if(x-1==i && y==j)
                        break;
                    nn++;
                }
            }
            if(board[x-1][y]==1||board[x-1][y]==2)
                checkStone(nn);
            nn=0;
            for(int i=0;i<=x+1;i++){
                for(int j=0;j<board[i].size();j++){
                    if(x+1==i && y==j)
                        break;
                    nn++;
                }
            }
            if(board[x+1][y]==1||board[x+1][y]==2)
                checkStone(nn);
        }
        if(y>0){
            int nn=0;
            for(int i=0;i<=x-1;i++){
                for(int j=0;j<board[i].size();j++){
                    if(x-1==i && y-1==j)
                        break;
                    nn++;
                }
            }
            if(board[x-1][y-1]==1||board[x-1][y-1]==2)
                checkStone(nn);
            nn=0;
            for(int i=0;i<=x+1;i++){
                for(int j=0;j<board[i].size();j++){
                    if(x+1==i && y-1==j)
                        break;
                    nn++;
                }
            }
            if(board[x+1][y-1]==1||board[x+1][y-1]==2)
                checkStone(nn);
        }
    }
    if(x>3 && x<6){
        if(y>0){
            int nn=0;
            for(int i=0;i<=x+1;i++){
                for(int j=0;j<board[i].size();j++){
                    if(x+1==i && y-1==j)
                        break;
                    nn++;
                }
            }
            if(board[x+1][y-1]==1||board[x+1][y-1]==2)
                checkStone(nn);
        }
        if(y<board[x].size()-1){
            int nn=0;
            for(int i=0;i<=x+1;i++){
                for(int j=0;j<board[i].size();j++){
                    if(x+1==i && y==j)
                        break;
                    nn++;
                }
            }
            if(board[x+1][y]==1||board[x+1][y]==2)
                checkStone(nn);
        }
    }
    if(x>3){
        int nn=0;
        for(int i=0;i<=x-1;i++){
            for(int j=0;j<board[i].size();j++){
                if(x-1==i && y==j)
                    break;
                nn++;
            }
        }
        if(board[x-1][y]==1||board[x-1][y]==2)
            checkStone(nn);
        nn=0;
        for(int i=0;i<=x-1;i++){
            for(int j=0;j<board[i].size();j++){
                if(x-1==i && y+1==j)
                    break;
                nn++;
            }
        }
        if(board[x-1][y+1]==1||board[x-1][y+1]==2)
            checkStone(nn);
    }
}

void GameBoard::countTowers(){
    int p1=0,p2=0;
    for(int i=0;i<37;i++){
        if(whoseTowers[i]==1)
            p1+=1;
        else if(whoseTowers[i]==2)
            p2+=1;
    }
    haveTowers[0]=p1;
    haveTowers[1]=p2;
}
