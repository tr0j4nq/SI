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
            if(colorP1==0)
                scene->addEllipse(-350,-200,50,50,QPen(QBrush(QColor(0,0,255)), 1),QBrush(QColor(0,0,255)));
            else if(colorP1==1)
                scene->addEllipse(-350,-200,50,50,QPen(QBrush(QColor(255,0,0)), 1),QBrush(QColor(255,0,0)));
            else if(colorP1==2)
                scene->addEllipse(-350,-200,50,50,QPen(QBrush(QColor(255,255,0)), 1),QBrush(QColor(255,255,0)));
            else
                scene->addEllipse(-350,-200,50,50,QPen(QBrush(QColor(0,255,0)), 1),QBrush(QColor(0,255,0)));
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

int GameBoard::abCheck(char abBoard[37],bool type){
    char tempBoard[37];
    for(int i=0;i<37;i++){
        if(abBoard[i]==1 || abBoard[i]==2)
            tempBoard[i]=6;
    }
    for(int i=0;i<37;i++){
        if(abBoard[i]==3){ //przeliczenie pol woko³ wiez
            if(i==0){
                if(abBoard[1]==1 || abBoard[1]==2)
                    tempBoard[1]--;
                if(abBoard[4]==1 || abBoard[4]==2)
                    tempBoard[4]--;
                if(abBoard[5]==1 || abBoard[5]==2)
                    tempBoard[5]--;
            }
            else if(i==1||i==2){
                if(abBoard[i-1]==1 || abBoard[i-1]==2)
                    tempBoard[i-1]--;
                if(abBoard[i+1]==1 || abBoard[i+1]==2)
                    tempBoard[i+1]--;
                if(abBoard[i+4]==1 || abBoard[i+4]==2)
                    tempBoard[i+4]--;
                if(abBoard[i+5]==1 || abBoard[i+5]==2)
                    tempBoard[i+5]--;
            }
            else if(i==3){
                if(abBoard[2]==1 || abBoard[2]==2)
                    tempBoard[2]--;
                if(abBoard[7]==1 || abBoard[7]==2)
                    tempBoard[7]--;
                if(abBoard[8]==1 || abBoard[8]==2)
                    tempBoard[8]--;
            }
            else if(i==4){
                if(abBoard[0]==1 || abBoard[0]==2)
                    tempBoard[0]--;
                if(abBoard[5]==1 || abBoard[5]==2)
                    tempBoard[5]--;
                if(abBoard[9]==1 || abBoard[9]==2)
                    tempBoard[9]--;
                if(abBoard[10]==1 || abBoard[10]==2)
                    tempBoard[10]--;
            }
            else if(i>4 && i<8){
                if(abBoard[i-5]==1 || abBoard[i-5]==2)
                    tempBoard[i-5]--;
                if(abBoard[i-4]==1 || abBoard[i-4]==2)
                    tempBoard[i-4]--;
                if(abBoard[i-1]==1 || abBoard[i-1]==2)
                    tempBoard[i-1]--;
                if(abBoard[i+1]==1 || abBoard[i+1]==2)
                    tempBoard[i+1]--;
                if(abBoard[i+5]==1 || abBoard[i+5]==2)
                    tempBoard[i+5]--;
                if(abBoard[i+6]==1 || abBoard[i+6]==2)
                    tempBoard[i+6]--;
            }
            else if(i==8){
                if(abBoard[3]==1 || abBoard[3]==2)
                    tempBoard[3]--;
                if(abBoard[7]==1 || abBoard[7]==2)
                    tempBoard[7]--;
                if(abBoard[13]==1 || abBoard[13]==2)
                    tempBoard[13]--;
                if(abBoard[14]==1 || abBoard[14]==2)
                    tempBoard[14]--;
            }
            else if(i==9){
                if(abBoard[4]==1 || abBoard[4]==2)
                    tempBoard[4]--;
                if(abBoard[10]==1 || abBoard[10]==2)
                    tempBoard[10]--;
                if(abBoard[15]==1 || abBoard[15]==2)
                    tempBoard[15]--;
                if(abBoard[16]==1 || abBoard[16]==2)
                    tempBoard[16]--;
            }
            else if(i>9 && i<14){
                if(abBoard[i-6]==1 || abBoard[i-6]==2)
                    tempBoard[i-6]--;
                if(abBoard[i-5]==1 || abBoard[i-5]==2)
                    tempBoard[i-5]--;
                if(abBoard[i-1]==1 || abBoard[i-1]==2)
                    tempBoard[i-1]--;
                if(abBoard[i+1]==1 || abBoard[i+1]==2)
                    tempBoard[i+1]--;
                if(abBoard[i+6]==1 || abBoard[i+6]==2)
                    tempBoard[i+6]--;
                if(abBoard[i+7]==1 || abBoard[i+7]==2)
                    tempBoard[i+7]--;
            }
            else if(i==14){
                if(abBoard[8]==1 || abBoard[8]==2)
                    tempBoard[8]--;
                if(abBoard[13]==1 || abBoard[13]==2)
                    tempBoard[13]--;
                if(abBoard[20]==1 || abBoard[20]==2)
                    tempBoard[20]--;
                if(abBoard[21]==1 || abBoard[21]==2)
                    tempBoard[21]--;
            }
            else if(i==15){
                if(abBoard[9]==1 || abBoard[9]==2)
                    tempBoard[9]--;
                if(abBoard[16]==1 || abBoard[16]==2)
                    tempBoard[16]--;
                if(abBoard[22]==1 || abBoard[22]==2)
                    tempBoard[22]--;
            }
            else if(i>15 && i<21){
                if(abBoard[i-7]==1 || abBoard[i-7]==2)
                    tempBoard[i-7]--;
                if(abBoard[i-6]==1 || abBoard[i-6]==2)
                    tempBoard[i-6]--;
                if(abBoard[i-1]==1 || abBoard[i-1]==2)
                    tempBoard[i-1]--;
                if(abBoard[i+1]==1 || abBoard[i+1]==2)
                    tempBoard[i+1]--;
                if(abBoard[i+6]==1 || abBoard[i+6]==2)
                    tempBoard[i+6]--;
                if(abBoard[i+7]==1 || abBoard[i+7]==2)
                    tempBoard[i+7]--;
            }
            else if(i==21){
                if(abBoard[14]==1 || abBoard[14]==2)
                    tempBoard[14]--;
                if(abBoard[20]==1 || abBoard[20]==2)
                    tempBoard[20]--;
                if(abBoard[27]==1 || abBoard[27]==2)
                    tempBoard[27]--;
            }
            else if(i==22){
                if(abBoard[15]==1 || abBoard[15]==2)
                    tempBoard[15]--;
                if(abBoard[16]==1 || abBoard[16]==2)
                    tempBoard[16]--;
                if(abBoard[23]==1 || abBoard[23]==2)
                    tempBoard[23]--;
                if(abBoard[28]==1 || abBoard[28]==2)
                    tempBoard[28]--;
            }
            else if(i>22 && i<27){
                if(abBoard[i-7]==1 || abBoard[i-7]==2)
                    tempBoard[i-7]--;
                if(abBoard[i-6]==1 || abBoard[i-6]==2)
                    tempBoard[i-6]--;
                if(abBoard[i-1]==1 || abBoard[i-1]==2)
                    tempBoard[i-1]--;
                if(abBoard[i+1]==1 || abBoard[i+1]==2)
                    tempBoard[i+1]--;
                if(abBoard[i+5]==1 || abBoard[i+5]==2)
                    tempBoard[i+5]--;
                if(abBoard[i+6]==1 || abBoard[i+6]==2)
                    tempBoard[i+6]--;
            }
            else if(i==27){
                if(abBoard[20]==1 || abBoard[20]==2)
                    tempBoard[20]--;
                if(abBoard[21]==1 || abBoard[21]==2)
                    tempBoard[21]--;
                if(abBoard[26]==1 || abBoard[26]==2)
                    tempBoard[26]--;
                if(abBoard[32]==1 || abBoard[32]==2)
                    tempBoard[32]--;
            }
            else if(i==28){
                if(abBoard[22]==1 || abBoard[22]==2)
                    tempBoard[22]--;
                if(abBoard[23]==1 || abBoard[23]==2)
                    tempBoard[23]--;
                if(abBoard[29]==1 || abBoard[29]==2)
                    tempBoard[29]--;
                if(abBoard[33]==1 || abBoard[33]==2)
                    tempBoard[33]--;
            }
            else if(i>28 && i<32){
                if(abBoard[i-6]==1 || abBoard[i-6]==2)
                    tempBoard[i-6]--;
                if(abBoard[i-5]==1 || abBoard[i-5]==2)
                    tempBoard[i-5]--;
                if(abBoard[i-1]==1 || abBoard[i-1]==2)
                    tempBoard[i-1]--;
                if(abBoard[i+1]==1 || abBoard[i+1]==2)
                    tempBoard[i+1]--;
                if(abBoard[i+4]==1 || abBoard[i+4]==2)
                    tempBoard[i+4]--;
                if(abBoard[i+5]==1 || abBoard[i+5]==2)
                    tempBoard[i+5]--;
            }
            else if(i==32){
                if(abBoard[26]==1 || abBoard[26]==2)
                    tempBoard[26]--;
                if(abBoard[27]==1 || abBoard[27]==2)
                    tempBoard[27]--;
                if(abBoard[31]==1 || abBoard[31]==2)
                    tempBoard[31]--;
                if(abBoard[36]==1 || abBoard[36]==2)
                    tempBoard[36]--;
            }
            else if(i==33){
                if(abBoard[28]==1 || abBoard[28]==2)
                    tempBoard[28]--;
                if(abBoard[29]==1 || abBoard[29]==2)
                    tempBoard[29]--;
                if(abBoard[34]==1 || abBoard[34]==2)
                    tempBoard[34]--;
            }
            else if(i>33 && i<36){
                if(abBoard[i-5]==1 || abBoard[i-5]==2)
                    tempBoard[i-5]--;
                if(abBoard[i-4]==1 || abBoard[i-4]==2)
                    tempBoard[i-4]--;
                if(abBoard[i-1]==1 || abBoard[i-1]==2)
                    tempBoard[i-1]--;
                if(abBoard[i+1]==1 || abBoard[i+1]==2)
                    tempBoard[i+1]--;
            }
            else if(i==36){
                if(abBoard[31]==1 || abBoard[31]==2)
                    tempBoard[31]--;
                if(abBoard[32]==1 || abBoard[32]==2)
                    tempBoard[32]--;
                if(abBoard[35]==1 || abBoard[35]==2)
                    tempBoard[35]--;
            }
        }
    }
    for(int i=0;i<37;i++){
        int p1=0,p2=0;
        if(abBoard[i]==3){ //przeliczenie zajetych wiez
           if(i==0){
                if(abBoard[1]==1)
                    p1+=tempBoard[1];
                if(abBoard[4]==1)
                    p1+=tempBoard[4];
                if(abBoard[5]==1)
                    p1+=tempBoard[5];
            }
            else if(i==1||i==2){
                if(abBoard[i-1]==1)
                    p1+=tempBoard[i-1];
                if(abBoard[i+1]==1)
                    p1+=tempBoard[i+1];
                if(abBoard[i+4]==1)
                    p1+=tempBoard[i+4];
                if(abBoard[i+5]==1)
                    p1+=tempBoard[i+5];
            }
            else if(i==3){
                if(abBoard[2]==1)
                    p1+=tempBoard[2];
                if(abBoard[7]==1)
                    p1+=tempBoard[7];
                if(abBoard[8]==1)
                    p1+=tempBoard[8];
            }
            else if(i==4){
                if(abBoard[0]==1)
                    p1+=tempBoard[0];
                if(abBoard[5]==1)
                    p1+=tempBoard[5];
                if(abBoard[9]==1)
                    p1+=tempBoard[9];
                if(abBoard[10]==1)
                    p1+=tempBoard[10];
            }
            else if(i>4 && i<8){
                if(abBoard[i-5]==1)
                    p1+=tempBoard[i-5];
                if(abBoard[i-4]==1)
                    p1+=tempBoard[i-4];
                if(abBoard[i-1]==1)
                    p1+=tempBoard[i-1];
                if(abBoard[i+1]==1)
                    p1+=tempBoard[i+1];
                if(abBoard[i+5]==1)
                    p1+=tempBoard[i+5];
                if(abBoard[i+6]==1)
                    p1+=tempBoard[i+6];
            }
            else if(i==8){
                if(abBoard[3]==1)
                    p1+=tempBoard[3];
                if(abBoard[7]==1)
                    p1+=tempBoard[7];
                if(abBoard[13]==1)
                    p1+=tempBoard[13];
                if(abBoard[14]==1)
                    p1+=tempBoard[14];
            }
            else if(i==9){
                if(abBoard[4]==1)
                    p1+=tempBoard[4];
                if(abBoard[10]==1)
                    p1+=tempBoard[10];
                if(abBoard[15]==1)
                    p1+=tempBoard[15];
                if(abBoard[16]==1)
                    p1+=tempBoard[16];
            }
            else if(i>9 && i<14){
                if(abBoard[i-6]==1)
                    p1+=tempBoard[i-6];
                if(abBoard[i-5]==1)
                    p1+=tempBoard[i-5];
                if(abBoard[i-1]==1)
                    p1+=tempBoard[i-1];
                if(abBoard[i+1]==1)
                    p1+=tempBoard[i+1];
                if(abBoard[i+6]==1)
                    p1+=tempBoard[i+6];
                if(abBoard[i+7]==1)
                    p1+=tempBoard[i+7];
            }
            else if(i==14){
                if(abBoard[8]==1)
                    p1+=tempBoard[8];
                if(abBoard[13]==1)
                    p1+=tempBoard[13];
                if(abBoard[20]==1)
                    p1+=tempBoard[20];
                if(abBoard[21]==1)
                    p1+=tempBoard[21];
            }
            else if(i==15){
                if(abBoard[9]==1)
                    p1+=tempBoard[9];
                if(abBoard[16]==1)
                    p1+=tempBoard[16];
                if(abBoard[22]==1)
                    p1+=tempBoard[22];
            }
            else if(i>15 && i<21){
                if(abBoard[i-7]==1)
                    p1+=tempBoard[i-7];
                if(abBoard[i-6]==1)
                    p1+=tempBoard[i-6];
                if(abBoard[i-1]==1)
                    p1+=tempBoard[i-1];
                if(abBoard[i+1]==1)
                    p1+=tempBoard[i+1];
                if(abBoard[i+6]==1)
                    p1+=tempBoard[i+6];
                if(abBoard[i+7]==1)
                    p1+=tempBoard[i+7];
            }
            else if(i==21){
                if(abBoard[14]==1)
                    p1+=tempBoard[14];
                if(abBoard[20]==1)
                    p1+=tempBoard[20];
                if(abBoard[27]==1)
                    p1+=tempBoard[27];
            }
            else if(i==22){
                if(abBoard[15]==1)
                    p1+=tempBoard[15];
                if(abBoard[16]==1)
                    p1+=tempBoard[16];
                if(abBoard[23]==1)
                    p1+=tempBoard[23];
                if(abBoard[28]==1)
                    p1+=tempBoard[28];
            }
            else if(i>22 && i<27){
                if(abBoard[i-7]==1)
                    p1+=tempBoard[i-7];
                if(abBoard[i-6]==1)
                    p1+=tempBoard[i-6];
                if(abBoard[i-1]==1)
                    p1+=tempBoard[i-1];
                if(abBoard[i+1]==1)
                    p1+=tempBoard[i+1];
                if(abBoard[i+5]==1)
                    p1+=tempBoard[i+5];
                if(abBoard[i+6]==1)
                    p1+=tempBoard[i+6];
            }
            else if(i==27){
                if(abBoard[20]==1)
                    p1+=tempBoard[20];
                if(abBoard[21]==1)
                    p1+=tempBoard[21];
                if(abBoard[26]==1)
                    p1+=tempBoard[26];
                if(abBoard[32]==1)
                    p1+=tempBoard[32];
            }
            else if(i==28){
                if(abBoard[22]==1)
                    p1+=tempBoard[22];
                if(abBoard[23]==1)
                    p1+=tempBoard[23];
                if(abBoard[29]==1)
                    p1+=tempBoard[29];
                if(abBoard[33]==1)
                    p1+=tempBoard[33];
            }
            else if(i>28 && i<32){
                if(abBoard[i-6]==1)
                    p1+=tempBoard[i-6];
                if(abBoard[i-5]==1)
                    p1+=tempBoard[i-5];
                if(abBoard[i-1]==1)
                    p1+=tempBoard[i-1];
                if(abBoard[i+1]==1)
                    p1+=tempBoard[i+1];
                if(abBoard[i+4]==1)
                    p1+=tempBoard[i+4];
                if(abBoard[i+5]==1)
                    p1+=tempBoard[i+5];
            }
            else if(i==32){
                if(abBoard[26]==1)
                    p1+=tempBoard[26];
                if(abBoard[27]==1)
                    p1+=tempBoard[27];
                if(abBoard[31]==1)
                    p1+=tempBoard[31];
                if(abBoard[36]==1)
                    p1+=tempBoard[36];
            }
            else if(i==33){
                if(abBoard[28]==1)
                    p1+=tempBoard[28];
                if(abBoard[29]==1)
                    p1+=tempBoard[29];
                if(abBoard[34]==1)
                    p1+=tempBoard[34];
            }
            else if(i>33 && i<36){
                if(abBoard[i-5]==1)
                    p1+=tempBoard[i-5];
                if(abBoard[i-4]==1)
                    p1+=tempBoard[i-4];
                if(abBoard[i-1]==1)
                    p1+=tempBoard[i-1];
                if(abBoard[i+1]==1)
                    p1+=tempBoard[i+1];
            }
            else if(i==36){
                if(abBoard[31]==1)
                    p1+=tempBoard[31];
                if(abBoard[32]==1)
                    p1+=tempBoard[32];
                if(abBoard[35]==1)
                    p1+=tempBoard[35];
            }
        }
        if(abBoard[i]==3){
           if(i==0){
                if(abBoard[1]==2)
                    p2+=tempBoard[1];
                if(abBoard[4]==2)
                    p2+=tempBoard[4];
                if(abBoard[5]==2)
                    p2+=tempBoard[5];
            }
            else if(i==1||i==2){
                if(abBoard[i-1]==2)
                    p2+=tempBoard[i-1];
                if(abBoard[i+1]==2)
                    p2+=tempBoard[i+1];
                if(abBoard[i+4]==2)
                    p2+=tempBoard[i+4];
                if(abBoard[i+5]==2)
                    p2+=tempBoard[i+5];
            }
            else if(i==3){
                if(abBoard[2]==2)
                    p2+=tempBoard[2];
                if(abBoard[7]==2)
                    p2+=tempBoard[7];
                if(abBoard[8]==2)
                    p2+=tempBoard[8];
            }
            else if(i==4){
                if(abBoard[0]==2)
                    p2+=tempBoard[0];
                if(abBoard[5]==2)
                    p2+=tempBoard[5];
                if(abBoard[9]==2)
                    p2+=tempBoard[9];
                if(abBoard[10]==2)
                    p2+=tempBoard[10];
            }
            else if(i>4 && i<8){
                if(abBoard[i-5]==2)
                    p2+=tempBoard[i-5];
                if(abBoard[i-4]==2)
                    p2+=tempBoard[i-4];
                if(abBoard[i-1]==2)
                    p2+=tempBoard[i-1];
                if(abBoard[i+1]==2)
                    p2+=tempBoard[i+1];
                if(abBoard[i+5]==2)
                    p2+=tempBoard[i+5];
                if(abBoard[i+6]==2)
                    p2+=tempBoard[i+6];
            }
            else if(i==8){
                if(abBoard[3]==2)
                    p2+=tempBoard[3];
                if(abBoard[7]==2)
                    p2+=tempBoard[7];
                if(abBoard[13]==2)
                    p2+=tempBoard[13];
                if(abBoard[14]==2)
                    p2+=tempBoard[14];
            }
            else if(i==9){
                if(abBoard[4]==2)
                    p2+=tempBoard[4];
                if(abBoard[10]==2)
                    p2+=tempBoard[10];
                if(abBoard[15]==2)
                    p2+=tempBoard[15];
                if(abBoard[16]==2)
                    p2+=tempBoard[16];
            }
            else if(i>9 && i<14){
                if(abBoard[i-6]==2)
                    p2+=tempBoard[i-6];
                if(abBoard[i-5]==2)
                    p2+=tempBoard[i-5];
                if(abBoard[i-1]==2)
                    p2+=tempBoard[i-1];
                if(abBoard[i+1]==2)
                    p2+=tempBoard[i+1];
                if(abBoard[i+6]==2)
                    p2+=tempBoard[i+6];
                if(abBoard[i+7]==2)
                    p2+=tempBoard[i+7];
            }
            else if(i==14){
                if(abBoard[8]==2)
                    p2+=tempBoard[8];
                if(abBoard[13]==2)
                    p2+=tempBoard[13];
                if(abBoard[20]==2)
                    p2+=tempBoard[20];
                if(abBoard[21]==2)
                    p2+=tempBoard[21];
            }
            else if(i==15){
                if(abBoard[9]==2)
                    p2+=tempBoard[9];
                if(abBoard[16]==2)
                    p2+=tempBoard[16];
                if(abBoard[22]==2)
                    p2+=tempBoard[22];
            }
            else if(i>15 && i<21){
                if(abBoard[i-7]==2)
                    p2+=tempBoard[i-7];
                if(abBoard[i-6]==2)
                    p2+=tempBoard[i-6];
                if(abBoard[i-1]==2)
                    p2+=tempBoard[i-1];
                if(abBoard[i+1]==2)
                    p2+=tempBoard[i+1];
                if(abBoard[i+6]==2)
                    p2+=tempBoard[i+6];
                if(abBoard[i+7]==2)
                    p2+=tempBoard[i+7];
            }
            else if(i==21){
                if(abBoard[14]==2)
                    p2+=tempBoard[14];
                if(abBoard[20]==2)
                    p2+=tempBoard[20];
                if(abBoard[27]==2)
                    p2+=tempBoard[27];
            }
            else if(i==22){
                if(abBoard[15]==2)
                    p2+=tempBoard[15];
                if(abBoard[16]==2)
                    p2+=tempBoard[16];
                if(abBoard[23]==2)
                    p2+=tempBoard[23];
                if(abBoard[28]==2)
                    p2+=tempBoard[28];
            }
            else if(i>22 && i<27){
                if(abBoard[i-7]==2)
                    p2+=tempBoard[i-7];
                if(abBoard[i-6]==2)
                    p2+=tempBoard[i-6];
                if(abBoard[i-1]==2)
                    p2+=tempBoard[i-1];
                if(abBoard[i+1]==2)
                    p2+=tempBoard[i+1];
                if(abBoard[i+5]==2)
                    p2+=tempBoard[i+5];
                if(abBoard[i+6]==2)
                    p2+=tempBoard[i+6];
            }
            else if(i==27){
                if(abBoard[20]==2)
                    p2+=tempBoard[20];
                if(abBoard[21]==2)
                    p2+=tempBoard[21];
                if(abBoard[26]==2)
                    p2+=tempBoard[26];
                if(abBoard[32]==2)
                    p2+=tempBoard[32];
            }
            else if(i==28){
                if(abBoard[22]==2)
                    p2+=tempBoard[22];
                if(abBoard[23]==2)
                    p2+=tempBoard[23];
                if(abBoard[29]==2)
                    p2+=tempBoard[29];
                if(abBoard[33]==2)
                    p2+=tempBoard[33];
            }
            else if(i>28 && i<32){
                if(abBoard[i-6]==2)
                    p2+=tempBoard[i-6];
                if(abBoard[i-5]==2)
                    p2+=tempBoard[i-5];
                if(abBoard[i-1]==2)
                    p2+=tempBoard[i-1];
                if(abBoard[i+1]==2)
                    p2+=tempBoard[i+1];
                if(abBoard[i+4]==2)
                    p2+=tempBoard[i+4];
                if(abBoard[i+5]==2)
                    p2+=tempBoard[i+5];
            }
            else if(i==32){
                if(abBoard[26]==2)
                    p2+=tempBoard[26];
                if(abBoard[27]==2)
                    p2+=tempBoard[27];
                if(abBoard[31]==2)
                    p2+=tempBoard[31];
                if(abBoard[36]==2)
                    p2+=tempBoard[36];
            }
            else if(i==33){
                if(abBoard[28]==2)
                    p2+=tempBoard[28];
                if(abBoard[29]==2)
                    p2+=tempBoard[29];
                if(abBoard[34]==2)
                    p2+=tempBoard[34];
            }
            else if(i>33 && i<36){
                if(abBoard[i-5]==2)
                    p2+=tempBoard[i-5];
                if(abBoard[i-4]==2)
                    p2+=tempBoard[i-4];
                if(abBoard[i-1]==2)
                    p2+=tempBoard[i-1];
                if(abBoard[i+1]==2)
                    p2+=tempBoard[i+1];
            }
            else if(i==36){
                if(abBoard[31]==2)
                    p2+=tempBoard[31];
                if(abBoard[32]==2)
                    p2+=tempBoard[32];
                if(abBoard[35]==2)
                    p2+=tempBoard[35];
            }
        }
        if (p1>p2 && p1>=5)
            tempBoard[i]=7;
        else if(p2>p1 && p2>=5)
            tempBoard[i]=8;
    }
    if(!type){
        int p1T=0,p2T=0;
        for(int i=0;i<37;i++){
            if(tempBoard[i]==7)
                p1T++;
            else if(tempBoard[i]==8)
                p2T++;
        }
        if((p1T!=p2T)&&(p1T>=4||p2T>=4))
            type=!type;
        else
            return 1000;
    }
    if(!turn&&type){
        int result=0;
        for(int i=0;i<37;i++){
            if(abBoard[i]==1)
                result+=1;
            else if(abBoard[i]==2)
                result-=1;
            if(abBoard[i]==3 && tempBoard[i]==7)
                result+=19;
            if(abBoard[i]==3 && tempBoard[i]==8)
                result-=19;
        }
        return result;
    }
    else{
        int result=0;
        for(int i=0;i<37;i++){
            if(abBoard[i]==1)
                result-=1;
            else if(abBoard[i]==2)
                result+=1;
            if(abBoard[i]==3 && tempBoard[i]==7)
                result-=19;
            if(abBoard[i]==3 && tempBoard[i]==8)
                result+=19;
        }
        return result;
    }
}

int GameBoard::alphabeta(char abBoard[37],int depth,int alpha,int beta, bool type){
    if(depth==0){
        return abCheck(abBoard,true);
    }//zwraca wynik planszy
    bool over=1;  //czy mozna zrobic ruch, 1-nie, 0-tak
    int  abTower=8;
    for(int i=0;i<37;i++){
        if(!abBoard[i])
            over=0;
        if(abBoard[i]==3)
            abTower--;
    }
    if (over)
        return abCheck(abBoard,true);//zwraca wynik planszy
    int tempCheck=abCheck(abBoard,false);
    if(tempCheck!=1000){
        return tempCheck;
    }
    qApp->processEvents();
    if(type){   //jezeli MAX
        for(int i=0;i<37;i++){
            if(abBoard[i]==0){
                char tempabBoard[37];
                for(int j=0;j<37;j++)
                    tempabBoard[j]=abBoard[j];
                int val;
                tempabBoard[i]=turn+1;
                val=alphabeta(tempabBoard,depth-1,alpha,beta,!type);
                if(val>=alpha){
                    alpha=val;
                    if(depth==compDepth[turn]){
                        abNextTurn=i;
                        abTowerTurn=0;
                    }
                }
                if(alpha>beta)
                    return beta;
                if(abTower){
                    for(int j=0;j<37;j++)
                        tempabBoard[j]=abBoard[j];
                    tempabBoard[i]=3;
                    val=alphabeta(tempabBoard,depth-1,alpha,beta,!type);
                    if(val>alpha){
                        alpha=val;
                        if(depth==compDepth[turn]){
                            abNextTurn=i;
                            abTowerTurn=1;
                        }
                    }
                    if(alpha>=beta)
                        return beta;
                }
            }
        }
        return alpha;
    }
    else{
        for(int i=0;i<37;i++){
            if(abBoard[i]==0){
                char tempabBoard[37];
                for(int j=0;j<37;j++)
                    tempabBoard[j]=abBoard[j];
                int val;
                tempabBoard[i]=(!turn)+1;
                val=alphabeta(tempabBoard,depth-1,alpha,beta,!type);
                beta=min(beta,val);
                if(alpha>=beta)
                    return alpha;
                if(abTower){
                    for(int j=0;j<37;j++)
                        tempabBoard[j]=abBoard[j];
                    tempabBoard[i]=3;
                    val=alphabeta(tempabBoard,depth-1,alpha,beta,!type);
                    beta=min(beta,val);
                    if(alpha>=beta)
                        return alpha;
                }
            }
        }
        return beta;
    }
}

void GameBoard::abTurn(){
    int k=0;
    char tempBoard[37];
    for(int i=0;i<board.size();i++){
        for(int j=0;j<board[i].size();j++){
            tempBoard[k]=board[i][j];
            k++;
        }
    }
    alphabeta(tempBoard,compDepth[turn],-1000,1000,1);
    if(!abTowerTurn)
        drawStone(abNextTurn);
    else
        drawTower(abNextTurn);
    countTowers();
    if(haveTowers[0]==4&&haveTowers[0]!=haveTowers[1]){
        gameOver=true;
        QMessageBox msgbox;
        msgbox.setText("Wygral gracz 1!");
        msgbox.exec();
        return;
    }
    if(haveTowers[1]==4&&haveTowers[0]!=haveTowers[1]){
        gameOver=true;
        QMessageBox msgbox;
        msgbox.setText("Wygral gracz 2!");
        msgbox.exec();
        return;
    }
    if(!turn&&!gameOver){
        if(colorP1==0)
            scene->addEllipse(-350,-200,50,50,QPen(QBrush(QColor(0,0,255)), 1),QBrush(QColor(0,0,255)));
        else if(colorP1==1)
            scene->addEllipse(-350,-200,50,50,QPen(QBrush(QColor(255,0,0)), 1),QBrush(QColor(255,0,0)));
        else if(colorP1==2)
            scene->addEllipse(-350,-200,50,50,QPen(QBrush(QColor(255,255,0)), 1),QBrush(QColor(255,255,0)));
        else
            scene->addEllipse(-350,-200,50,50,QPen(QBrush(QColor(0,255,0)), 1),QBrush(QColor(0,255,0)));
    }
    else if(!gameOver){
        if(colorP2==0)
            scene->addEllipse(-350,-200,50,50,QPen(QBrush(QColor(0,0,255)), 1),QBrush(QColor(0,0,255)));
        else if(colorP2==1)
            scene->addEllipse(-350,-200,50,50,QPen(QBrush(QColor(255,0,0)), 1),QBrush(QColor(255,0,0)));
        else if(colorP2==2)
            scene->addEllipse(-350,-200,50,50,QPen(QBrush(QColor(255,255,0)), 1),QBrush(QColor(255,255,0)));
        else
            scene->addEllipse(-350,-200,50,50,QPen(QBrush(QColor(0,255,0)), 1),QBrush(QColor(0,255,0)));
    }
    if(gameOver){
        if(haveTowers[0]>haveTowers[1]){
            QMessageBox msgbox;
            msgbox.setText("Wygral gracz 1!");
            msgbox.exec();
        }
        else if(haveTowers[1]>haveTowers[0]){
            QMessageBox msgbox;
            msgbox.setText("Wygral gracz 2!");
            msgbox.exec();
        }
        else{
            int p1=0,p2=0;
            for(int i=0;i<board.size();i++){
                for(int j=0;j<board[i].size();j++){
                    if(board[i][j]==1)
                        p1+=1;
                    else if(board[i][j]==2)
                        p2+=1;
                }
            }
            if(p1>p2){
                QMessageBox msgbox;
                msgbox.setText("Wygral gracz 1!");
                msgbox.exec();
            }
            else if(p2>p1){
                QMessageBox msgbox;
                msgbox.setText("Wygral gracz 2!");
                msgbox.exec();
            }
            else{
                QMessageBox msgbox;
                msgbox.setText("Remis!");
                msgbox.exec();
            }
        }
    }
    if (!gameOver&&!player[turn]){
        if(compAI[turn]==0)
            randTurn();
        else if(compAI[turn]==1)
            abTurn();
        else
            ;
    }


}

void GameBoard::randTurn(){
    if(rand()%100>=20)
        drawStone(rand()%37);
    else
        drawTower(rand()%37);
    countTowers();
    if(haveTowers[0]==4&&haveTowers[0]!=haveTowers[1]){
        gameOver=true;
        QMessageBox msgbox;
        msgbox.setText("Wygral gracz 1!");
        msgbox.exec();
        return;
    }
    if(haveTowers[1]==4&&haveTowers[0]!=haveTowers[1]){
        gameOver=true;
        QMessageBox msgbox;
        msgbox.setText("Wygral gracz 2!");
        msgbox.exec();
        return;
    }
    if(!turn&&!gameOver){
        if(colorP1==0)
            scene->addEllipse(-350,-200,50,50,QPen(QBrush(QColor(0,0,255)), 1),QBrush(QColor(0,0,255)));
        else if(colorP1==1)
            scene->addEllipse(-350,-200,50,50,QPen(QBrush(QColor(255,0,0)), 1),QBrush(QColor(255,0,0)));
        else if(colorP1==2)
            scene->addEllipse(-350,-200,50,50,QPen(QBrush(QColor(255,255,0)), 1),QBrush(QColor(255,255,0)));
        else
            scene->addEllipse(-350,-200,50,50,QPen(QBrush(QColor(0,255,0)), 1),QBrush(QColor(0,255,0)));
    }
    else if(!gameOver){
        if(colorP2==0)
            scene->addEllipse(-350,-200,50,50,QPen(QBrush(QColor(0,0,255)), 1),QBrush(QColor(0,0,255)));
        else if(colorP2==1)
            scene->addEllipse(-350,-200,50,50,QPen(QBrush(QColor(255,0,0)), 1),QBrush(QColor(255,0,0)));
        else if(colorP2==2)
            scene->addEllipse(-350,-200,50,50,QPen(QBrush(QColor(255,255,0)), 1),QBrush(QColor(255,255,0)));
        else
            scene->addEllipse(-350,-200,50,50,QPen(QBrush(QColor(0,255,0)), 1),QBrush(QColor(0,255,0)));
    }
    if(gameOver){
        if(haveTowers[0]>haveTowers[1]){
            QMessageBox msgbox;
            msgbox.setText("Wygral gracz 1!");
            msgbox.exec();
        }
        else if(haveTowers[1]>haveTowers[0]){
            QMessageBox msgbox;
            msgbox.setText("Wygral gracz 2!");
            msgbox.exec();
        }
        else{
            int p1=0,p2=0;
            for(int i=0;i<board.size();i++){
                for(int j=0;j<board[i].size();j++){
                    if(board[i][j]==1)
                        p1+=1;
                    else if(board[i][j]==2)
                        p2+=1;
                }
            }
            if(p1>p2){
                QMessageBox msgbox;
                msgbox.setText("Wygral gracz 1!");
                msgbox.exec();
            }
            else if(p2>p1){
                QMessageBox msgbox;
                msgbox.setText("Wygral gracz 2!");
                msgbox.exec();
            }
            else{
                QMessageBox msgbox;
                msgbox.setText("Remis!");
                msgbox.exec();
            }
        }
    }
    if (!gameOver&&!player[turn]){
        if(compAI[turn]==0)
            randTurn();
        else if(compAI[turn]==1)
            abTurn();
        else
            ;
    }

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
            return;
        }
        if(haveTowers[1]==4&&haveTowers[0]!=haveTowers[1]){
            gameOver=true;
            QMessageBox msgbox;
            msgbox.setText("Wygral gracz 2!");
            msgbox.exec();
            return;
        }
        if(!turn&&!gameOver){
            if(colorP1==0)
                scene->addEllipse(-350,-200,50,50,QPen(QBrush(QColor(0,0,255)), 1),QBrush(QColor(0,0,255)));
            else if(colorP1==1)
                scene->addEllipse(-350,-200,50,50,QPen(QBrush(QColor(255,0,0)), 1),QBrush(QColor(255,0,0)));
            else if(colorP1==2)
                scene->addEllipse(-350,-200,50,50,QPen(QBrush(QColor(255,255,0)), 1),QBrush(QColor(255,255,0)));
            else
                scene->addEllipse(-350,-200,50,50,QPen(QBrush(QColor(0,255,0)), 1),QBrush(QColor(0,255,0)));
        }
        else if(!gameOver){
            if(colorP2==0)
                scene->addEllipse(-350,-200,50,50,QPen(QBrush(QColor(0,0,255)), 1),QBrush(QColor(0,0,255)));
            else if(colorP2==1)
                scene->addEllipse(-350,-200,50,50,QPen(QBrush(QColor(255,0,0)), 1),QBrush(QColor(255,0,0)));
            else if(colorP2==2)
                scene->addEllipse(-350,-200,50,50,QPen(QBrush(QColor(255,255,0)), 1),QBrush(QColor(255,255,0)));
            else
                scene->addEllipse(-350,-200,50,50,QPen(QBrush(QColor(0,255,0)), 1),QBrush(QColor(0,255,0)));
        }
        if(!gameOver&&!player[turn]){
            if(compAI[turn]==0){
                randTurn();
                return;
            }
            else if(compAI[turn]==1){
                abTurn();
                return;
            }
            else
                ;
        }
        if(gameOver){
            if(haveTowers[0]>haveTowers[1]){
                QMessageBox msgbox;
                msgbox.setText("Wygral gracz 1!");
                msgbox.exec();
            }
            else if(haveTowers[1]>haveTowers[0]){
                QMessageBox msgbox;
                msgbox.setText("Wygral gracz 2!");
                msgbox.exec();
            }
            else{
                int p1=0,p2=0;
                for(int i=0;i<board.size();i++){
                    for(int j=0;j<board[i].size();j++){
                        if(board[i][j]==1)
                            p1+=1;
                        else if(board[i][j]==2)
                            p2+=1;
                    }
                }
                if(p1>p2){
                    QMessageBox msgbox;
                    msgbox.setText("Wygral gracz 1!");
                    msgbox.exec();
                }
                else if(p2>p1){
                    QMessageBox msgbox;
                    msgbox.setText("Wygral gracz 2!");
                    msgbox.exec();
                }
                else{
                    QMessageBox msgbox;
                    msgbox.setText("Remis!");
                    msgbox.exec();
                }
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
        if(!turn&&towers){
            scene->addEllipse(boardC[n].x()-35,boardC[n].y()-35,70,70,QPen(QBrush(QColor(210,105,30)), 1),QBrush(QColor(210,105,30)));
            board[ta[n]][tb[n]]=3;
            checkTower(n);
            towers--;
            turn=!turn;
            checkTower(n);
        }
        else if(turn&&towers){
            scene->addEllipse(boardC[n].x()-35,boardC[n].y()-35,70,70,QPen(QBrush(QColor(210,105,30)), 1),QBrush(QColor(210,105,30)));
            board[ta[n]][tb[n]]=3;
            checkTower(n);
            towers--;
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
    for(int i=0;i<board.size();i++){
        for(int j=0;j<board[i].size();j++){
            if(!board[i][j])
                return;
        }
    }
    gameOver=true;
}
