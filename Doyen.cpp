#include "Doyen.h"

std :: string Doyen ::returnMaxYelCard(std :: vector<Player>player){

    int maxYel=0;
    std::string maxYelCard;
    for (int i = 0; i < player.size(); i++){
        for(const auto& card :player[i].returnPlayedCards()){

            size_t found = card.find("yel");
            if (found != std::string::npos) {
                int score = std::stoi(card.substr(found + 3)); // Extract the score
                maxYel = std::max(maxYel, score);
            }
        }
    }
    return  "yel" + std::to_string(maxYel);
    
}


void Doyen::deletLargestCards(std :: vector<Player> &player){
    
    std::string maxYelCard = returnMaxYelCard(player);
    for (int i = 0 ; i < player.size() ; i++){
        for (int j = 0 ; j < player[i].getPlayedCardsSize(); j++)
        {
            if(player[i].indexPlayeCards(j)==maxYelCard){
                player[i].deleteCardFromPlayedCards(maxYelCard);
                player[i].deleteCardFromYelCards(maxYelCard);
                pushCardToBurnedCards(maxYelCard);
            }
        }
        
    }
}



void Doyen::use(State &s, int numplayer) {
    std::string sta;
    s.pushBackProvinces();
    bool validInput = false;
    while (!validInput) {
        std::cout << "You can save a province from war: ";
        std::cin >> sta;

        // Trim leading and trailing whitespace
        sta.erase(std::remove_if(sta.begin(), sta.end(), ::isspace), sta.end());

        // Check if province exists in the vector
        for (const auto& province : s.returnProvinces()) {
            std::string trimmedProvince = province;
            trimmedProvince.erase(std::remove_if(trimmedProvince.begin(), trimmedProvince.end(), ::isspace), trimmedProvince.end());
            if (trimmedProvince == sta) {
                s.deletProvinces(trimmedProvince); // Call deleteProvinces to remove the province
                validInput = true;
                break;
            }
        }

        if (!validInput) {
            std::cout << "ERROR!!!\nProvince not found in Provinces. Please choose again:\n";
            std::cin.clear(); // Clear input error flags
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore remaining input
        }
    }
    system("CLS"); // Clear screen
}
