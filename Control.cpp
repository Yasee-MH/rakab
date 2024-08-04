#include "Control.h"


int Control::getNumber(){
    return number ;}

void Control:: setNumber(int n){number=n;}

void Control :: getData(){
    std :: cout << "Enter tne numbers of players : " ;
    std :: cin >> number;
    for (int i = 0; i < number; i++)
    {
        Player newPlayer(0 , 0 , 0);
        std :: cout << "Enter the name and age of player" << i+1 << " : " ;
        std :: cin >> name >> age;
        newPlayer.setAge(age);
        newPlayer.setName(name);
        play.push_back(newPlayer);
    }
    dealCardsToPlayers();
}

void Control :: dealCardsToPlayers(){
    
    card.readFile();   // Read cards from file

    // Get the cards directly from Cart's public member (cards)
    std::vector<std::string>& cards = card.cards;

    // Shuffle the cards
    std::shuffle(cards.begin(), cards.end(), std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count()));

    // Deal cards to players
    int numCardsPerPlayer = 10;
    int numPlayers = play.size();
    int totalCards = cards.size();

    for (int i = 0 ; i < numPlayers ; ++i) {
        std::vector<std::string> hand;
        for (int j = 0; j < numCardsPerPlayer && !cards.empty(); ++j) {
            hand.push_back(cards.back());
            cards.pop_back();
        }
        play[i].setHand(hand);
    }
}

int Control :: foundLargestAge(std::vector<Player>& player){
    int min= player[0].getAge();
    for (int i = 1; i < player.size(); i++)
    {
        if (player[i].getAge()<min)
        {
            min=player[i].getAge();
        }
    }
    return min;
}


void  Control :: checkTheAgeOfPlayer ( std::vector<Player>& player , std::vector<int> &index ){
    int min = foundLargestAge(player);
    for (int i = 0 ; i < player.size() ; i++)
    {
        if(player[i].getAge()==min){
            index.push_back(i);
        }
    }
    //std :: cout << index.size();
}

int Control :: DetermineWhoWillStartTheGameFirst(std::vector<Player>& player){
    std::vector<int> index;
    checkTheAgeOfPlayer(player, index);
    if(index.size()==1){
        return index[0];
    }
    else{
        srand(time(0));
        int num = rand()%(index.size());
        return index[num];
    }
}

void Control :: show(){
    int numPlayer=DetermineWhoWillStartTheGameFirst(play);
    std :: cout <<play[numPlayer].getAge() << play[numPlayer].getName() << "\n-----" << std :: endl;

	for (int i = 0; i < number; i++){
		std :: cout << "player " << (i + 1) << " : ";
        play[i].showHand();
		std :: cout << std ::endl;
	}
}

void Control :: run(std :: string choose , int num){
    if(choose=="rish_sefid"){
        Doyen doyen;
        doyen.use(state,0);
        doyen.deletLargestCards(play);
    }
    else if (choose=="matarsak")
    {
        Scarecrow scarecrow;
        scarecrow.use(play ,num );
    }
    else if(choose=="parcham_dar"){
        preference(play);
        foundLargestScore(play);
        checkTheScoreOfPlayer(play);
        DetermineTheWinnerOfTheProvince(score , play );
        
    }
}

void Control ::gamePlay(){
    state.pushBackProvinces();
    std :: string choose;
    int number=1;
    setStateForWar();
    int win=0;
    int numPlayer=DetermineWhoWillStartTheGameFirst(play);
    while(win==0){
        while (numPlayer<play.size())
        {
            pass(choose, play , numPlayer ,number);
            numPlayer++;
            if (numPlayer==play.size())
            {
                numPlayer=0;
            }
            if(checkWinner(play , numPlayer)==1){
                win==1;
                break;
            }
        }
    }
}

void Control::preference(std::vector<Player>& player) {
    for (int i = 0 ; i < player.size(); i++)
    {
        for (int j = 0; j < player[i].getPlayedCardsSize(); ++j){
            if (player[i].indexPlayeCards(j) == "zemestan") {
                Winter winter;
                winter.use(player, i);
                //std :: cout << players[i].getScore()  <<",";
            }
        }
    }
    int count=0;
    while(count==0){
        for (int i = 0 ; i < player.size(); i++)
        {
            for (int j = 0; j < player[i].getPlayedCardsSize(); ++j){
                if (player[i].indexPlayeCards(j) == "tabl_zan") {
                    Drummer drummer;
                    drummer.use(player, i);
                    count=1;
                    //std :: cout << players[i].getScore() <<",";
                }
                if(count==1){ break; }
            }
        }
    }
    for (int i = 0 ; i < player.size(); i++)
    {
        for (int j = 0; j < player[i].getPlayedCardsSize(); ++j){
            if (player[i].indexPlayeCards(j) == "bahar") {
                Spring spring;
                spring.use(player, i);
                //std :: cout << players[i].getScore()  <<",";
            }
        }
    }
    for (int i = 0 ; i < player.size(); i++)
    {
        for (int j = 0; j < player[i].getPlayedCardsSize(); ++j){
            if (player[i].indexPlayeCards(j) == "shir_zan") {
                Heroine heroine;
                heroine.use(player, i);
                //std :: cout << players[i].getScore()  <<",";
            } else if (player[i].indexPlayeCards(j) == "shah_dokht") {
                Princess princess;
                princess.use(player, i);
                //std :: cout << players[i].getScore()  <<",";
            } 
        }
    }
    
}


void  Control :: setStateForWar(){
    state.displayState();
    std :: cout << "\nEnter the state for war : ";
    std :: string s;
    std ::cin >> s;
    state.setState(s);
}

int Control :: foundLargestScore(std::vector<Player>& player){
    int max=0;
    for (int i = 0; i < player.size(); i++)
    {
        if (player[i].getScore()>max)
        {
            max=player[i].getScore();
        }
    }
    return max;
}

int Control ::checkWinner(std::vector<Player>& player , int numPlayer){
    if (player[numPlayer].returnCapturedProvinces().size()==3 &&state.checkAdjacent(player , numPlayer))
    {
        std ::cout <<"\n\n\t\tYOU WIN ^-^\n\n\n";
        return 1;
    }
    if (player[numPlayer].returnCapturedProvinces().size()==5)
    {
        system("CLS");
        std ::cout <<"\n\n\t\tYOU WIN ^-^\n\n\n";
        return 1;
    }
    else{
        return 0;
    }

}

void Control :: checkTheScoreOfPlayer(std::vector<Player>& player){
    for (int i = 0 ; i < player.size() ; i++)
    {
        if(player[i].getScore()==foundLargestScore(player)){
            score.push_back(i);
        }
    }
}

void Control ::DetermineTheWinnerOfTheProvince(std :: vector < int > &score , std::vector<Player>& player  ){
    if(score.size()==1){
        player[score[0]].addState(state.getState());
        RemovalOfTheOccupiedProvince(state,state.getState());
        setStateForWar();
        deletPlayedCardVec(player , card) ;
        showStateForPlayer(player);
    }
    else{
        std ::cout << "player " << FindTheLastPersonWhoPassed(player) << "chooses the next province to fight :";
        setStateForWar();
        deletPlayedCardVec( player,card) ;
        showStateForPlayer(player);
    }
}

void Control ::pass(std ::string choose , std::vector<Player>& player , int numPlayer , int &num){
    system("CLS");
    if(player[numPlayer].getPass()==0){

        std :: cout << "player " << (numPlayer+ 1) << " : ";
        player[numPlayer].showHand();
        std :: cout << "player " << numPlayer+1 << " enter the cards to play:";
        std :: cin >> choose ;

        if(choose=="pass"){
            player[numPlayer].chengePass(num);
            num++;
            std :: cout << "Player "<< numPlayer+1 << " has passed.\n";
            checkPass(player);
        }
        else{
            player[numPlayer].chooseCard(choose);
            run(choose , numPlayer);
            std::cout << "_______________\ncards to play for player  " << numPlayer+1 << " : ";
            player[numPlayer].displayPlayedCards();
            std :: cout <<"________________\n";
        }
    }
}

void Control :: checkPass(std::vector<Player>& player){
    int count=0 ;
    for(int i=0 ; i<player.size() ; i++){
        if(player[i].getPass()!=0){
            count ++;
        }
    }
    if (count==player.size())
    {
        preference(player);
        foundLargestScore(player);
        checkTheScoreOfPlayer(player);
        DetermineTheWinnerOfTheProvince(score , player );
    }
    
}

int Control :: FindTheLastPersonWhoPassed(std::vector<Player>& player){
    int count=1;
    int j=0;
    for (int i = 0; i < player.size(); i++)
    {
        if(player[i].getPass()>count){
            count=player[i].getPass();
            j=i+1;
        }
    }
    return j;
}

void Control ::RemovalOfTheOccupiedProvince(State &s, std :: string sta) {
    //std::string sta;
    bool validInput = false ;
    while (!validInput) {
        // Trim leading and trailing whitespace
        sta.erase(std::remove_if(sta.begin(), sta.end(), ::isspace), sta.end());
        // Check if province exists in the vector
        for (const auto& province : s.returnProvinces()) {
            std::string trimmedProvince = province;
            trimmedProvince.erase(std::remove_if(trimmedProvince.begin(), trimmedProvince.end(), ::isspace), trimmedProvince.end());
            if (trimmedProvince == sta) {
                s.deletProvinces(trimmedProvince); // Call deleteProvinces to remove the province
                validInput = true;
                break;
            }
        }

        if (!validInput) {
            std::cout << "ERROR!!!\nProvince not found in Provinces. Please choose again:\n";
            std::cin.clear(); // Clear input error flags
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore remaining input
        }
    }
    system("CLS"); // Clear screen
}

void Control ::deletPlayedCardVec(std::vector<Player>& player , Cart &cart){
    
    // for(int i=0 ; i<player.size() ; i++){
    //     player[i].emptyAllVectors(cart);
    //     std :: cout << player[i].getPlayedCardsSize();
    //      player[i].returnCapturedProvinces();
    // }
    for (int i = player.size() - 1; i >= 0; --i) {
        player[i].emptyAllVectors(cart);
        player[i].setScoreOfPlayer(0);
    }
}

void Control ::showStateForPlayer(std::vector<Player>& player){
    for (int i = 0 ; i < player.size(); i++)
    {
        std :: cout <<"\nplayer 1:"; 
        player[i].printState();
    }
}

void Control ::koft(){
    play[0].addState("PLADACI" );
    play[0].addState("BORGE") ;
    play[0].addState("DIMASE" ) ;
    checkWinner(play, 0);
}