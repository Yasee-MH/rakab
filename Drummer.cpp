#include "Drummer.h"

void Drummer :: use( std :: vector < Player > &player , int numPlayer){
    player[numPlayer].calculateScore();
    //std :: cout << "\ntabl_zan" <<player[numPlayer].getScore();
    int score = player[numPlayer].getScore()*2;
    //std :: cout << "\ntabl_zan" <<score;
    player[numPlayer].setScoreOfPlayer(score);
    
}

