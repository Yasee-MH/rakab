#ifndef HEROINE_H
#define HEROINE_H
#include "PurpleCard.h"

class Heroine : public PurpleCard{
    public:
        void use(std :: vector<Player> &player , int numplayer);
        void FindTheMostHeroinCards(std :: vector<Player> &player , int numplayer);

};

#endif // !HEROINE_H