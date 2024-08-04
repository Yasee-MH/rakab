#include "Scarecrow.h"

void Scarecrow ::use(std :: vector < Player > &players , int currentPlayerIndex){
    players[currentPlayerIndex].displayPlayedCards();

        std::string choose;
        bool validInput = false;

        while (!validInput) {
            std::cout << "Choose a yellow card to return to your hand: ";
            std::cin >> choose;

            // Trim leading and trailing whitespace
            choose.erase(std::remove_if(choose.begin(), choose.end(), ::isspace), choose.end());

            bool found = false;

            for (const std::string &card : players[currentPlayerIndex].returnPlayedCards()) {
                std::string trimmedCard = card;
                trimmedCard.erase(std::remove_if(trimmedCard.begin(), trimmedCard.end(), ::isspace), trimmedCard.end());

                if (trimmedCard == choose) {
                    // Move the card from played cards back to hand
                    players[currentPlayerIndex].addCardFromHand(trimmedCard);
                    players[currentPlayerIndex].deleteCardFromPlayedCards(trimmedCard);

                    // Also remove it from yellow cards if it's there
                    for (const std::string &cardFound : players[currentPlayerIndex].returnYelCards()){
                        std::string trimmedCardFound = cardFound;
                        trimmedCardFound.erase(std::remove_if(trimmedCardFound.begin(), trimmedCardFound.end(), ::isspace), trimmedCardFound.end());

                        if (trimmedCardFound == choose) {
                            // Move the card from played cards back to hand
                            players[currentPlayerIndex].deleteCardFromYelCards(trimmedCardFound);
                            found=true ;
                            break;
                        }
                    }
                }
            }

            if (found) {
                validInput = true;
            } else {
                std::cout << "ERROR!!!\nCard not found in PlayedCards. Please choose again:\n";
                std::cin.clear(); // Clear input error flags
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore remaining input
            }
        }

        system("CLS"); // Clear screen after successful selection
}