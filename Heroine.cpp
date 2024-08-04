#include "Heroine.h"

void  Heroine ::use(std :: vector<Player> &player , int numplayer){

    player[numplayer].setScoreOfPlayer(player[numplayer].getScore()+1);
}

void Heroine :: FindTheMostHeroinCards(std :: vector<Player> &player , int numplayer){
    int maxPlayedHero =0;
    int i=0;
    if(i<player.size())
    {
        if (player[i].getHeroine()>maxPlayedHero)
        {
            maxPlayedHero=player[i].getHeroine();
        }
        i++;
    }
    std :: cout << "player" << i+1 << "you can choose the state for war:";
}




