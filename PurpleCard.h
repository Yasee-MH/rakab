#ifndef PURPLECARD_H
#define PURPLECARD_H
#include "Cart.h"

class PurpleCard : public Cart{
    public:
        void use();
        //void setPlayer(Player* player); // Setter for Control pointer
    // private :
    //     Player *p;
};

#endif // !PURPLECARD_H