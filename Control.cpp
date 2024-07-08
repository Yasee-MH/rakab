#include "Control.h"


int Control::getNumber(){return number ;}

void Control:: setNumber(int n){number=n;}

void Control :: getData(){
    std :: cout << "Enter tne numbers of players : " ;
    std :: cin >> number;
    for (int i = 0; i < number; i++)
    {
        Player newPlayer;
        std :: cout << "Enter the name and age of player" << i+1 << " : " ;
        std :: cin >> name >> age;
        newPlayer.setAge(age);
        newPlayer.setName(name);
        play.push_back(newPlayer);
    }
    dealCardsToPlayers();
}

void Control :: dealCardsToPlayers(){
    for (int i = 0 ; i < number ; i++) {
        std :: vector < std :: string > hand = card.dealCards(10);
        play[i].setHand(hand);
    }
}

int Control :: CheckSmall(){
    std :: vector<int>temp(1);
    int j=0;
    temp[0]= play[0].getAge();
    for(int i=1 ; i<number ; i++){
        if(temp[0]>play[i].getAge())
        {
            temp[0]=play[i].getAge();
            j=i;
        }
    }
    return j;

}

void Control :: show(){
    std :: cout << play[CheckSmall()].getAge() << play[CheckSmall()].getName() << "\n-----" << std :: endl;

	for (int i = 0; i < number; i++) {
		std :: cout << "player " << (i + 1) << " : ";
        play[i].showHand();
		std :: cout << std ::endl;
		}
	

	/*for (int i = 0; i < number; i++) {
		std :: cout << "yel cards for player " << (i + 1) << " : ";
		for (const auto& yelCard : playersYelCards[i]) {
			std :: cout << yelCard << " / ";
		}
		std :: cout << std ::endl;
	}*/
}

void Control :: choose(){
    for(int i=0 ; i<number ; i++){
        play[i].chooseCard();
    }
}

void Control :: run(){
    while (true)
    {
        choose();
        for(int i=0 ; i<number ; i++){
            play[i].displayPlayedCards();
        }
        show();
    }
}
