#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QGridLayout>
#include "gameboard.h"
#include <QtGui/QComboBox>
#include <QtGui/QLabel>
#include <QtGui/QTextEdit>
#include "ai.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);

signals:

public slots:

private:
    QPushButton* newButton;
    QPushButton* helpButton;
    QFrame* newGameWindow;
    GameBoard* game;
    QComboBox* player1Combo;
    QComboBox* player2Combo;
    QComboBox* comp1Combo;
    QComboBox* comp2Combo;
    QComboBox* color1Combo;
    QComboBox* color2Combo;
    QComboBox* comp1Depth;
    QComboBox* comp2Depth;
public slots:
    void newGame();
    void cancelNewGame();
    void startNewGame();
    void comp1ComboEnable();
    void comp2ComboEnable();
};

#endif // MAINWINDOW_H
