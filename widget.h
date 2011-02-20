#ifndef WIDGET_H
#define WIDGET_H

#include <QtGui/QWidget>
#include <QtGui/QPushButton>
#include <QtGui/QGridLayout>
#include "gameboard.h"
#include <QtGui/QComboBox>
#include <QtGui/QLabel>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);

private:
    QPushButton* newButton;
    QPushButton* helpButton;
    QFrame* newGameWindow;
    GameBoard* game;
    QComboBox* player1Combo;
    QComboBox* player2Combo;
    QComboBox* comp1Combo;
    QComboBox* comp2Combo;
public slots:
    void newGame();
    void cancelNewGame();
    void startNewGame();
    void comp1ComboEnable();
    void comp2ComboEnable();
};

#endif // WIDGET_H
