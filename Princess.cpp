#include "Princess.h" //shir_dokht

void Princess :: use(std :: vector<Player> &player , int numplayer){
    
    player[numplayer].setScoreOfPlayer(player[numplayer].getScore()+10);
}