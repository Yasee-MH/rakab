#ifndef DOYEN_H
#define DOYEN_H
class PurpleCard;
#include "PurpleCard.h"
#include "State.h"
#include <vector>

class Doyen : public PurpleCard{
    public:
        void use(State &s, int numplayer);
        std :: string returnMaxYelCard(std :: vector<Player>player);
        void deletLargestCards(std :: vector<Player> &player);
        

};

#endif // !DOYEN_H