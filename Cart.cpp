#include "Cart.h"

void Cart :: shuffleArray(std :: vector< std :: string>& arr, int n) {
    srand(time(nullptr));
    for (int i = n - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        swap(arr[i], arr[j]);
    }
}

std :: vector < std :: string > Cart :: dealCards (int numCards) {
    readFile();
    shuffleArray(cards, cards.size());
    std :: vector < std :: string > dealtCards;
    for (int i = 0; i < numCards; i++) {
        dealtCards.push_back(cards.back());
        cards.pop_back();
    }
    return dealtCards;
}

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
