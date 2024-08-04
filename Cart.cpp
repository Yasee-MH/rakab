#include "Cart.h"

int Cart :: readFile(){
    //open the file
    std :: ifstream infile("cards.txt");
    if (!infile)
    {
        std :: cerr << "Error opening file 'cards.txt'\n";
        return 1;
    }
    //read cards from file 
    while (infile >> card)
    {
        cards.push_back(card);
    }
    infile.close();
    return 0;
}

void Cart ::shuffleCards(){

    std::shuffle(cards.begin(), cards.end(), std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count()));

}

void Cart :: use(){}

void Cart :: pushCardToBurnedCards(std :: string card){
    BurnedCards.push_back(card);
}

void Cart :: print(){
    for (int i = 0; i <BurnedCards.size(); i++)
    {
        std :: cout <<BurnedCards[i];
    }
    
}

int Cart::returnSize(){
    return BurnedCards.size();
}

void Cart::printIndex(int n){
    std ::cout << BurnedCards[n-1];
}