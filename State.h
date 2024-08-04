#ifndef STATE_H
#define STATE_H
#include <iostream>
#include <unordered_set>
#include <string>
#include <fstream>
#include "Player.h"

class State{
    public:
        bool areAdjacent(const std::string &firstState , const std::string &secondState);

        void readMapFromFile(const std :: string &filename);

        bool checkAdjacent(std :: vector<Player> &player ,int numPlayer);

        void deletProvinces(std :: string &p);

        void setState(std::string s);

        std :: string getState();

        void displayState();

        std::vector< std :: string >returnProvinces();
         
        void pushBackProvinces();

    private:
    
        struct pair_hash {  // Custom hash function for std::pair
            template <class T1, class T2>
            std::size_t operator() (const std::pair<T1, T2>& pair) const {
                auto hash1 = std::hash<T1>{}(pair.first);
                auto hash2 = std::hash<T2>{}(pair.second);
                return hash1 ^ hash2; // Combine the hash values
            }
        };    
        std ::unordered_set < std ::pair < std::string , std::string > , pair_hash> adjacencySet;

        std :: string state;

        std :: vector<std ::string > Provinces;//={ "BELLA" , "CALINE" , "ENNA" , "ATELA" , "PLADACI" , "BORGE" , "DIMASE" , "MORINA"
        //                                         ,"OLIVADI" , "ROLLO" , "TALMONE" , "ARMENTO" , "LIA" , "ELINIA" };
};

#endif // !STATE_H