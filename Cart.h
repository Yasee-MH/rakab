
#ifndef CART_H
#define CART_H
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <time.h>
#include <algorithm>

class Cart{
    public:
        void shuffleArray(std :: vector< std :: string>& arr, int n);
        std :: vector < std :: string > dealCards(int numCards);
        int readFile();

    private:
        std :: vector < std :: string > cards;
        std :: string card ;

};


#endif // !CART_H
