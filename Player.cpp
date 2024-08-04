#include "Player.h"
Player :: Player (int sco , int hero , int p):score(sco),heroine(hero) , pass(p){} //constructor

Player :: Player(){}

int Player :: getAge(){ return age; }

std :: string Player :: getName(){ return name; }

void Player :: setAge(int a){ age=a; }

void Player :: setName( std :: string n){ name=n; }

void Player :: setScoreOfPlayer(int s){score=s;}

int Player :: getScore(){return score ;}

std::vector< std :: string> Player :: returnPlayedCards(){ return playedCards; }

std::vector< std :: string> Player :: returnYelCards(){return YelCards;}

void Player :: setHand( std :: vector< std :: string > h ){ hand=h; }

void Player :: showHand(){
  for (const auto & card : hand) {
		std::cout << card << " / ";
  }
  std :: cout << std :: endl;
}

void Player::chooseCard(std :: string chosenCard){
  auto it = std :: find( hand.begin() , hand.end() , chosenCard );
  if ( it != hand.end() )
  {
    // Check if the chosenCard starts with "yel"
    if( chosenCard.substr ( 0 , 3) == "yel") {
      YelCards.push_back(*it);  // Add to yelCards vector
    }
    playedCards.push_back(*it);
    hand.erase(it);
  }
  else 
  {
    std::cout << "Card not found in hand. Please choose again.\n";
    std :: cin >> chosenCard ;
    chooseCard(chosenCard);
  }
}

int Player :: getYelCardsSize(){return YelCards.size();}

void Player :: displayPlayedCards() {
  
  for (const auto& card : playedCards) {
    std::cout << card << " / ";
  }
  //std::cout << std::endl;

}

void Player::calculateScore() {

  for (const auto& card : YelCards) {
    std::string pointStr = card.substr(3,5); // Assuming "yel" + points part
    int pointsInt = std::stoi(pointStr); // Convert points string to integer
    score += pointsInt;
  }
  setScoreOfPlayer(score);
}

int Player ::getPlayedCardsSize(){
  return playedCards.size();
}

std ::string  Player ::indexPlayeCards(int numCards){
  return playedCards[numCards];
} 

void Player ::deleteCardFromPlayedCards(std :: string &c ){
  
  auto it = std :: find(playedCards.begin() , playedCards.end() , c );
  if ( it != playedCards.end() )
  {
    playedCards.erase(it);
  }

}

void Player ::addCardFromHand(std :: string &c){
  hand.push_back(c);
}

void Player ::deleteCardFromYelCards(std :: string &c ){
  
  auto it = std :: find(YelCards.begin() , YelCards.end() , c );
  if ( it != YelCards.end() )
  {
    YelCards.erase(it);
  }

}

void Player ::plusHeroine(){ heroine++ ; }

int Player :: getHeroine(){return heroine;}

void Player ::displayYelCards(){
  for (const auto & card : YelCards) {
		std::cout << card << " / ";
    }
}

void Player ::addState(std ::string state){
  CapturedProvinces.push_back(state);
}

std::vector< std :: string > Player ::returnCapturedProvinces(){
  return CapturedProvinces;
}

std :: string Player ::indexCapturedProvinces(int numState){
  return CapturedProvinces[numState];
}

void Player :: printState(){
  for(const auto &state:CapturedProvinces){
    std :: cout << state;
  }
}

void Player :: emptyAllVectors(Cart &cart){
  for(const auto&card : playedCards){
    cart.pushCardToBurnedCards(card);
  }
  // std::vector<std::string>().swap(playedCards);
  playedCards.clear();
  // std::vector<std::string>().swap(YelCards);
  YelCards.clear();
}

void Player ::chengePass(int number) { pass=number; }

int Player :: getPass(){return pass;}