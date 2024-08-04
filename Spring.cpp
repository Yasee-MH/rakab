#include "Spring.h"

void Spring :: use(std :: vector < Player >&player , int numPlayer){
    
    player[numPlayer].calculateScore();
    int score = player[numPlayer].getYelCardsSize()*3 +player[numPlayer].getScore();
    player[numPlayer].setScoreOfPlayer(score);
    
}
