#ifndef SCARECROW_H
#define SCARECROW_H
class Player;
#include "Player.h"
#include "PurpleCard.h"
#include <iostream>
#include <string>

class Scarecrow : public PurpleCard {
    public:
        void use(std :: vector < Player > &player , int numPlayer);//override ;
       // Scarecrow(){}
    private:
        std :: string choose;
};

#endif // !SCARECROW