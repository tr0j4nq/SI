#ifndef AI_H
#define AI_H
#include <QVector>
#include "gameboard.h"

class AI
{
public:
    AI(GameBoard* board);
    bool board[37];
    bool stoneP1[37];
    bool stoneP2[37];
    bool towers[37];
    QVector<AI> state;
    void comp1Play();
};

#endif // AI_H
