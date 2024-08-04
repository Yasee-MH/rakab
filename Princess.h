#ifndef PRINCESS_H
#define PRINCESS_H
#include "PurpleCard.h"

class Princess : public PurpleCard{
    public:
        void use(std :: vector<Player> &player , int numplayer);
};

#endif // !PRINCESS_H