
#include "Player.h"

int Player :: getAge(){ return age; }

std :: string Player :: getName(){ return name; }

void Player :: setAge(int a){ age=a; }

void Player :: setName( std :: string n){ name=n; }

std::vector< std :: string> Player :: getHand(){ return hand; }

void Player :: setHand( std :: vector< std :: string > h ){ hand=h; }

void Player :: showHand(){
  for (const auto & card : hand) {
		std::cout << card << " / ";
    }
}

void Player::chooseCard(){
  
  std :: cout << "Enter the cards:";
  std :: cin >> chosenCard ;

  auto it = std :: find( hand.begin() , hand.end() , chosenCard );
  if ( it != hand.end() )
  {
    if (chosenCard.find("yel") != std::string::npos) {
      playedYelCards.push_back(*it); // Add to playedYelCards if it contains "yel"
    }
    playedCards.push_back(*it);
    hand.erase(it);
  }
  else 
  {
    std::cout << "Card not found in hand. Please choose again.\n";
    chooseCard();
  }
}

void Player :: displayPlayedCards() {
  std::cout << "Played cards: ";
  for (const auto& card : playedCards) {
    std::cout << card << " ";
  }
  std::cout << std::endl;
  for (const auto& car : playedYelCards) {
    std::cout << car << "/";
  }
  std::cout << std::endl;
}

void Player::chooseYelCards(){
  auto it = std::find_if(playedCards.begin(), playedCards.end(), [](const std::string& card)
  { return card.find("yel") != std::string::npos; });

  if (it != playedCards.end()) {
    playedYelCards.push_back(*it);
    //playedCards.erase(it);
  }
}