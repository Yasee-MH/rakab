#ifndef SAVEGAME_H
#define SAVEGAME_H
#include <vector>
#include <fstream>
#include <filesystem> //for put_time
#include "Player.h"


class SaveGame{
    public:
        void saveGame( std :: vector < Player > & player , int number , int startingPlayerIndex , std :: string warProvince);
        bool loadGame( const std::string& filename , std::vector<Player>& players , int& number , int& startingPlayerIndex , std :: string& warProvince);
        void printSavedGames();
    private :
        std :: string generateFilename() ;
        bool fileExists(const std::string& filename);
};

#endif // !SAVEGAME_H