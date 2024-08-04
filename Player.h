#ifndef PLAYER_H
#define PLAYER_H
#include "Cart.h"
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>   // For std::stringstream
#include <iterator>
class Cart;
#include "Cart.h" 
//#include <fstream>

class Player{
    public:
        Player(int sco ,int hero , int p);
        Player();
        int getAge();
        std :: string getName();
        int getScore() ;
        int getHeroine();
        int getYelCardsSize();
        int getPlayedCardsSize();
        int getPass();
        void setAge(int a);
        void setName( std :: string n );
        void setScoreOfPlayer(int s);
        void displayPlayedCards();
        void displayYelCards();
        void calculateScore();
        std::vector< std :: string > returnPlayedCards();
        std::vector< std :: string > returnCapturedProvinces();
        std::vector< std :: string > returnYelCards();
        void setHand( std :: vector< std :: string > h );
        void chooseCard(std :: string chosencard);
        void addCardFromHand(std :: string &c);
        void addState(std ::string state);
        void deleteCardFromPlayedCards(std :: string &c);
        void deleteCardFromYelCards(std :: string &c );
        std :: string indexPlayeCards(int numCards);
        std :: string indexCapturedProvinces(int numState);
        void showHand();
        void plusHeroine();
        void printState();
        void emptyAllVectors(Cart &cart);
        void chengePass(int number);
    private: 
        int age , score , heroine , pass;
        std :: string name ;
        std :: vector< std :: string > hand;
        std :: vector< std :: string > playedCards;
        std :: vector< std :: string > YelCards;
        std :: vector< std :: string > CapturedProvinces;

};

#endif // !PLAYER_H
