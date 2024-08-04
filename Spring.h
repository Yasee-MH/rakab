#ifndef SPRING_H
#define SPRING_H
#include "PurpleCard.h"

class Spring : public PurpleCard{
    public:
        void use(std :: vector < Player >&player , int numPlayer);
};

#endif // !SPRING_H