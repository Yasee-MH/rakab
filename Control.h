
#ifndef CONTROL_H
#define CONTROL_H
#include <string>
#include <iostream>
#include <vector>
#include "Player.h"
#include "Cart.h"
class Control{
    public:
        int getNumber();

        void setNumber(int n);

        void getData();

        void dealCardsToPlayers();

        int CheckSmall();

        void show();

        void choose();

        void run();
        
    private:
        int number , age ;
        std :: string name ;
        Cart card;
        std :: vector < Player > play;
        std :: vector < std :: string > sarbaz ;
};

#endif // !CONTROL_H
