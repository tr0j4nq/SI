#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("SIEGESTONES");
    newButton = new QPushButton("Nowa gra",this);
    helpButton = new QPushButton("Pomoc",this);


    QGridLayout* mainLayout = new QGridLayout;
    QHBoxLayout* buttonLayout = new QHBoxLayout;

    game = new GameBoard(this);

    buttonLayout->addWidget(newButton);
    buttonLayout->addWidget(helpButton);

    mainLayout->addLayout(buttonLayout,0,0);
    mainLayout->addWidget(game,1,0);

    connect(newButton, SIGNAL(clicked()), this, SLOT(newGame()));

    setLayout(mainLayout);
    showMaximized();
}

void Widget::newGame(){
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
    connect(playButton, SIGNAL(clicked()),this,SLOT(startNewGame()));
    connect(cancelButton, SIGNAL(clicked()),this,SLOT(cancelNewGame()));
    connect(player1Combo,SIGNAL(activated(int)),this,SLOT(comp1ComboEnable()));
    connect(player2Combo,SIGNAL(activated(int)),this,SLOT(comp2ComboEnable()));
    playButton->setGeometry(10,10,140,30);
    cancelButton->setGeometry(160,10,140,30);
    player1Label->setGeometry(10,50,50,20);
    player1Combo->setGeometry(50,50,100,20);
    comp1Combo->setGeometry(160,50,50,20);
    player2Label->setGeometry(10,80,50,20);
    player2Combo->setGeometry(50,80,100,20);
    comp2Combo->setGeometry(160,80,50,20);
    newGameWindow->show();
}

void Widget::cancelNewGame(){
    newButton->setDisabled(0);
    newGameWindow->close();
}

void Widget::startNewGame(){
    if(player1Combo->currentIndex()==0)
        game->player1=0;
    else
        game->player1=1;
    if(player2Combo->currentIndex()==0)
        game->player2=0;
    else
        game->player2=1;
    game->drawBoard();
    newButton->setDisabled(0);
    newGameWindow->close();
}

void Widget::comp1ComboEnable(){
    if(player1Combo->currentIndex()==0){
        comp1Combo->setDisabled(0);
    }
    else
        comp1Combo->setDisabled(1);
}

void Widget::comp2ComboEnable(){
    if(player2Combo->currentIndex()==0){
        comp2Combo->setDisabled(0);
    }
    else
        comp2Combo->setDisabled(1);
}
