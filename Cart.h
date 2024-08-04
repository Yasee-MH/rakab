
#ifndef CART_H
#define CART_H
#include "Player.h"
class Player;
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <random>    // For std::default_random_engine
#include <chrono>    // For std::chrono::system_clock

class Cart{//BaseClass
    public:
        std :: vector < std :: string > cards;

        int readFile();
        
        void shuffleCards();  //Function to shuffle the cards

        virtual void use();// Virtual function for polymorphism
    
        void pushCardToBurnedCards(std :: string card);

        void print(); 

        int returnSize();

        void printIndex(int n);
    private:
        std :: string card ;
        std :: vector<std ::string > BurnedCards;

};


#endif // !CART_H
