#include "Winter.h"

void Winter :: use( std :: vector < Player > &player , int numPlayer){
    for (int i = 0 ; i < player.size() ; i++)
    {
        int score = player[i].getYelCardsSize();
        player[i].setScoreOfPlayer(score);
    }
    
}