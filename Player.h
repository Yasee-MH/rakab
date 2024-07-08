
#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <vector>

#include <iostream>
#include <algorithm>
#include <fstream>

class Player{
    public:
        int getAge();
        std :: string getName();
        void setAge(int a);
        void setName( std :: string n );
        void showHand();
        void displayPlayedCards();

        std::vector< std :: string > getHand();
        void setHand( std :: vector< std :: string > h );
        void chooseCard();
        void chooseYelCards();
    private: 
        int age;
        std :: string name , chosenCard;
        std :: vector< std :: string >hand;
        std :: vector< std :: string >playedCards;
        std :: vector< std :: string >playedYelCards;
};

#endif // !PLAYER_H
