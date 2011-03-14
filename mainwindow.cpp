#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setWindowTitle("SIEGESTONES");
    newButton = new QPushButton("Nowa gra",this);
    helpButton = new QPushButton("Pomoc",this);
    game = new GameBoard(this);
    newButton->setGeometry(15,15,100,30);
    helpButton->setGeometry(125,15,100,30);
    game->setGeometry(5,50,750,650);
    this->setMaximumSize(760,700);
    connect(newButton, SIGNAL(clicked()), this, SLOT(newGame()));
}

void MainWindow::newGame(){
    newButton->setDisabled(1);
    newGameWindow = new QFrame(this,Qt::Tool | Qt::Window | Qt::FramelessWindowHint);
    newGameWindow->resize(310,110);
    QPushButton* playButton = new QPushButton("Zacznij",newGameWindow);
    QPushButton* cancelButton = new QPushButton("Anuluj",newGameWindow);
    QLabel* player1Label = new QLabel("Gracz 1",newGameWindow);
    QLabel* player2Label = new QLabel("Gracz 2",newGameWindow);
    player1Combo = new QComboBox(newGameWindow);
    player2Combo = new QComboBox(newGameWindow);
    comp1Combo = new QComboBox(newGameWindow);
    comp2Combo = new QComboBox(newGameWindow);
    color1Combo = new QComboBox(newGameWindow);
    color2Combo = new QComboBox(newGameWindow);
    player1Combo->setEditable(0);
    player2Combo->setEditable(0);
    player1Combo->addItem("Komputer",Qt::DisplayRole);
    player1Combo->addItem("Czlowiek",Qt::DisplayRole);
    player2Combo->addItem("Komputer",Qt::DisplayRole);
    player2Combo->addItem("Czlowiek",Qt::DisplayRole);    
    comp1Combo->addItem("1",Qt::DisplayRole);
    comp1Combo->addItem("2",Qt::DisplayRole);
    comp2Combo->addItem("1",Qt::DisplayRole);
    comp2Combo->addItem("2",Qt::DisplayRole);
    color1Combo->addItem("Niebieski",Qt::DisplayRole);
    color2Combo->addItem("Niebieski",Qt::DisplayRole);
    color1Combo->addItem("Czerwony",Qt::DisplayRole);
    color2Combo->addItem("Czerwony",Qt::DisplayRole);
    color1Combo->addItem("Zolty",Qt::DisplayRole);
    color2Combo->addItem("Zolty",Qt::DisplayRole);
    color1Combo->addItem("Zielony",Qt::DisplayRole);
    color2Combo->addItem("Zielony",Qt::DisplayRole);

    color2Combo->setCurrentIndex(1);
    connect(playButton, SIGNAL(clicked()),this,SLOT(startNewGame()));
    connect(cancelButton, SIGNAL(clicked()),this,SLOT(cancelNewGame()));
    connect(player1Combo,SIGNAL(activated(int)),this,SLOT(comp1ComboEnable()));
    connect(player2Combo,SIGNAL(activated(int)),this,SLOT(comp2ComboEnable()));
    playButton->setGeometry(10,10,140,30);
    cancelButton->setGeometry(160,10,140,30);
    player1Label->setGeometry(10,50,50,20);
    player1Combo->setGeometry(50,50,100,20);
    comp1Combo->setGeometry(160,50,50,20);
    color1Combo->setGeometry(220,50,50,20);
    player2Label->setGeometry(10,80,50,20);
    player2Combo->setGeometry(50,80,100,20);
    comp2Combo->setGeometry(160,80,50,20);
    color2Combo->setGeometry(220,80,50,20);
    newGameWindow->show();
}

void MainWindow::cancelNewGame(){
    newButton->setDisabled(0);
    newGameWindow->close();
}

void MainWindow::startNewGame(){
    game->turn=0;
    game->gameClear();
    game->player[0]=player1Combo->currentIndex();
    game->player[1]=player2Combo->currentIndex();
    game->colorP1=color1Combo->currentIndex();
    game->colorP2=color2Combo->currentIndex();
    game->towers=8;
    game->drawBoard();
    game->gameOver=false;
    newButton->setDisabled(0);
    newGameWindow->close();
}

void MainWindow::comp1ComboEnable(){
    if(player1Combo->currentIndex()==0){
        comp1Combo->setDisabled(0);
    }
    else
        comp1Combo->setDisabled(1);
}

void MainWindow::comp2ComboEnable(){
    if(player2Combo->currentIndex()==0){
        comp2Combo->setDisabled(0);
    }
    else
        comp2Combo->setDisabled(1);
}

