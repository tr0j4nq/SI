#include "ai.h"

AI::AI(GameBoard* tempBoard)
{
    for(int i=0;i<37;i++){
        board[i]=false;
        stoneP1[i]=false;
        stoneP2[i]=false;
        towers[i]=false;
    }
    int tempInt=0;
    for(int i=0;i<tempBoard->board.size();i++){
        for(int j=0;j<tempBoard->board[i].size();j++){
            if(tempBoard->board[i][j]!=0){
                board[tempInt]=true;
                if(tempBoard->board[i][j]==1)
                    stoneP1[tempInt]=true;
                else if(tempBoard->board[i][j]==2)
                    stoneP2[tempInt]=true;
                else if(tempBoard->board[i][j]==3)
                    towers[tempInt]=true;
            }
            tempInt+=1;
        }
    }
}

void AI::comp1Play(){

}
