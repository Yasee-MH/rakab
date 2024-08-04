#ifndef DRUMMER_H
#define DRUMMER_H
class PurpleCard;
#include "PurpleCard.h"


class Drummer : public PurpleCard{
    public:
        void use( std :: vector < Player > &player , int numPlaye );
        
        
};

#endif // !DRUMMER_H
