#ifndef CONTROL_H
#define CONTROL_H
#include <string>
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include "Player.h"
#include "Cart.h"
#include "Drummer.h"
#include "Scarecrow.h"
#include "Doyen.h"
#include "Gonfalonier.h"
#include "Heroine.h"
#include "Princess.h"
#include "Winter.h"
#include "Spring.h"
#include "State.h"

class Control{
    public:
        int getNumber();

        void setNumber(int n);

        void getData();

        void dealCardsToPlayers();

        int CheckSmall();

        void show();

        void preference(std::vector<Player>& player);

        void gamePlay();

        void run(std :: string choose , int num);

        void setStateForWar();

        int foundLargestScore(std::vector<Player>& player);


        void checkTheScoreOfPlayer(std::vector<Player>& player);

        int checkWinner( std::vector<Player>& player ,  int numPlayer);

        void DetermineTheWinnerOfTheProvince(std :: vector < int > &score ,std::vector<Player>& player );

        void pass(std :: string choose , std::vector<Player>& player , int numPlayer , int &num);

        void checkPass(std::vector<Player>& player);

        int FindTheLastPersonWhoPassed(std::vector<Player>& player) ;

        void RemovalOfTheOccupiedProvince(State &s, std::string sta);
        
        void deletPlayedCardVec(std::vector<Player>& player , Cart &cart);

        void showStateForPlayer(std::vector<Player>& player);

        int foundLargestAge(std::vector<Player>& player) ;

        void checkTheAgeOfPlayer ( std::vector<Player>& player , std::vector<int> &index);

        int DetermineWhoWillStartTheGameFirst(std::vector<Player>& player);

        void koft();
    private:
        int number , age ;
        std :: string name ;
        Cart card;
        State state;
        std :: vector < Player > play;
        std :: vector < int > score ;
        std :: vector < int > ageOfPlayer ;
};

#endif // !CONTROL_H
