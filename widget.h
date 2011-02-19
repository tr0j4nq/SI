#ifndef WIDGET_H
#define WIDGET_H

#include <QtGui/QWidget>
#include <QtGui/QPushButton>
#include <QtGui/QGridLayout>
#include "painter.h"
#include <QtGui/QComboBox>
#include <QtGui/QLabel>
#include "game.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);

private:
    QPushButton* newButton;
    QPushButton* helpButton;
    QFrame* newGameWindow;
    Painter* painter;
    QComboBox* player1Combo;
    QComboBox* player2Combo;
    QComboBox* comp1Combo;
    QComboBox* comp2Combo;
    Game* game;
public slots:
    void newGame();
    void cancelNewGame();
    void startNewGame();
    void comp1ComboEnable();
    void comp2ComboEnable();
};

#endif // WIDGET_H
