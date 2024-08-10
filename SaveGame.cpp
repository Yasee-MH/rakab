#include "SaveGame.h"


void SaveGame:: saveGame(std :: vector < Player > &player , int number  , int startingPlayerIndex , std ::string warProvice){
    
    std::string filename = generateFilename();
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Could not open file for saving game state.\n";
        return;
    }

    outFile << number << '\n';
    outFile << startingPlayerIndex << '\n'; //Save starting player index
    outFile << warProvice << '\n';

    for ( auto& players : player) {
        outFile << players.getName() << '\n';
        outFile << players.getHeroine() << '\n';
        outFile << players.getPass() << '\n';
        outFile << players.getAge() << '\n';
        outFile << players.getScore() << '\n';

        // Save hand
        outFile << players.returnHand().size() << '\n';
        for (const auto& card : players.returnHand()) {
            outFile << card << '\n';
        }

        // Save playedCards
        outFile << players.returnPlayedCards().size() << '\n';
        for (const auto& card : players.returnPlayedCards()) {
            outFile << card << '\n';
        }

        // Save YelCards
        outFile << players.returnYelCards().size() << '\n';
        for (const auto& card : players.returnYelCards()) {
            outFile << card << '\n';
        }

        // Save CapturedProvinces
        outFile << players.returnCapturedProvinces().size() << '\n';
        for (const auto& province : players.returnCapturedProvinces()) {
            outFile << province << '\n';
        }
    }
    outFile.close();
}

bool SaveGame ::loadGame( const std::string& filename , std::vector<Player>& players , int& number , int& startingPlayerIndex , std :: string &warProvince){
    if (!fileExists(filename)) {
        std::cerr << "File does not exist.\n";
        return false;
    }
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        std::cerr << "Could not open file for loading game state.\n";
        return false;
    }
    inFile >> number ;
    inFile >> startingPlayerIndex;  // Load starting player index
    inFile.ignore();
    std::getline(inFile, warProvince);
    inFile.ignore();

    players.clear();
    for (int i = 0; i < number; ++i) {
        Player player;
        std::string name;
        int age, score, heroine, pass;

        std::getline(inFile, name);
        inFile >> age >> score >> heroine >> pass;
        inFile.ignore();

        player.setName(name);
        player.setAge(age);
        player.setScoreOfPlayer(score);
        player.setHeroine(heroine);
        player.chengePass(pass);

        // Load hand
        int handSize;
        inFile >> handSize;
        inFile.ignore();
        std::vector<std::string> hand;
        for (int j = 0; j < handSize; ++j) {
            std::string card;
            std::getline(inFile, card);
            hand.push_back(card);
        }
        player.setHand(hand);

        // Load playedCards
        int playedCardsSize;
        inFile >> playedCardsSize;
        inFile.ignore();
        std::vector<std::string> playedCards;
        for (int j = 0; j < playedCardsSize; ++j) {
            std::string card;
            std::getline(inFile, card);
            playedCards.push_back(card);
        }
        player.setPlayedCards(playedCards);

        // Load YelCards
        int YelCardsSize;
        inFile >> YelCardsSize;
        inFile.ignore();
        std::vector<std::string> YelCards;
        for (int j = 0; j < YelCardsSize; ++j) {
            std::string card;
            std::getline(inFile, card);
            YelCards.push_back(card);
        }
        player.setYelCards(YelCards);

        // Load CapturedProvinces
        int capturedProvincesSize;
        inFile >> capturedProvincesSize;
        inFile.ignore();
        std::vector<std::string> capturedProvinces;
        for (int j = 0; j < capturedProvincesSize; ++j) {
            std::string province;
            std::getline(inFile, province);
            capturedProvinces.push_back(province);
        }
        player.setCapturedProvinces(capturedProvinces);

        players.push_back(player);
    }

    inFile.close();
    return true;
}

void SaveGame::printSavedGames() {
    std::vector<std::string> savedGames;
    for (const auto& entry : std::filesystem::directory_iterator(".")) {
        if (entry.path().extension() == ".sav") {
            savedGames.push_back(entry.path().filename().string());
        }
    }
    
    if (savedGames.empty()) {
        std::cout << "No saved games found.\n";
        return;
    }

    std::cout << "Saved games:\n";
    for (size_t i = 0; i < savedGames.size(); ++i) {
        std::cout << i + 1 << ". " << savedGames[i] << '\n';
    }
}


std::string SaveGame::generateFilename() {
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);

    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d_%H-%M-%S") << ".sav";
    return ss.str();
}

bool SaveGame ::fileExists(const std::string& filename) {
    std::ifstream file(filename);
    return file.is_open();
}


