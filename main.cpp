#include <iostream>
#include "Player.h"
//#include "Cart.cpp"
#include "Control.h"

using namespace std;

int main(){
    Control cont ;
    cont.getData();
    cont.show();
    cont.run();
    return 0;
}