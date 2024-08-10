#include "Control.h"

int Control::getNumber()
{
    return number;
}

void Control::setNumber(int n) { number = n; }

void Control::setNumberOfPlayer(){
    int num;
    while ( true ){
        std :: cout << "Enter the number of players : " ;
        std :: cin >> num ;
        if ( num >= 3 ){
            setNumber(num);
            break ;
        }else {
            std :: cout << "Error !\n" ;
            continue ;
        }
    }
    system ( "cls" ) ;
}

void Control ::getData()
{
    setNumberOfPlayer();
    for (int i = 0; i < number; i++)
    {
        Player newPlayer(0, 0, 0);
        std ::cout << "Enter the name and age of player" << i + 1 << " : ";
        std ::cin >> name >> age;
        newPlayer.setAge(age);
        newPlayer.setName(name);
        play.push_back(newPlayer);
    }
    dealCardsToPlayers(10);
}

void Control ::dealCardsToPlayers(int numCards)
{

    card.readFile(); // Read cards from file

    // Get the cards directly from Cart's public member (cards)
    std::vector<std::string> &cards = card.cards;

    // Shuffle the cards
    std::shuffle(cards.begin(), cards.end(), std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count()));

    // Deal cards to players
    int numCardsPerPlayer = numCards;
    int numPlayers = play.size();
    int totalCards = cards.size();

    for (int i = 0; i < numPlayers; ++i)
    {
        std::vector<std::string> hand;
        for (int j = 0; j < numCardsPerPlayer && !cards.empty(); ++j)
        {
            hand.push_back(cards.back());
            cards.pop_back();
        }
        play[i].setHand(hand);
    }
}

int Control ::foundLargestAge(std::vector<Player> &player) //found smallest age in player
{
    int min = player[0].getAge();
    for (int i = 1; i < player.size(); i++)
    {
        if (player[i].getAge() < min)
        {
            min = player[i].getAge();
        }
    }
    return min;
}

void Control ::checkTheAgeOfPlayer(std::vector<Player> &player, std::vector<int> &index) //check age of player for start game
{
    int min = foundLargestAge(player);
    for (int i = 0; i < player.size(); i++)
    {
        if (player[i].getAge() == min)
        {
            index.push_back(i);
        }
    }
}

int Control ::DetermineWhoWillStartTheGameFirst(std::vector<Player> &player) //determine how start game
{
    std::vector<int> index;
    checkTheAgeOfPlayer(player, index);
    if (index.size() == 1)
    {
        return index[0];
    }
    else
    {
        srand(time(0));
        int num = rand() % (index.size());
        return index[num];
    }
}

void Control ::show(std::vector<Player> &player)
{
    //system("CLS");
    for (int i = 0; i < getNumber(); i++)
    {
        std ::cout << "player " << (i + 1) << " : ";
        player[i].displayPlayedCards();
    }
    std :: cout << "-------------------\n";
    for (int i = 0; i < getNumber(); i++)
    {
        std ::cout << "player " << (i + 1) << " : ";
        player[i].printState();
        std ::cout << std ::endl;
    }
}

void Control ::run(std ::string choose, int &num )
{
    if (choose == "rish_sefid")
    {
        Doyen doyen;
        doyen.use(state, 0);
        doyen.deletLargestCards(play);
    }
    else if (choose == "matarsak")
    {
        Scarecrow scarecrow;
        scarecrow.use(play, num);
    }
    else if (choose == "parcham_dar")
    {
        preference(play);
        foundLargestScore(play);
        checkTheScoreOfPlayer(play);
        DetermineTheWinnerOfTheProvince(score, play , num );
    }
}

void Control ::gamePlay()
{
    std ::string choose;
    int number = 1;
    bool win = false;
    int numPlayer = DetermineWhoWillStartTheGameFirst(play);
    setStateForWar(numPlayer);
    while (!win)
    {
        while (numPlayer < play.size())
        {
            gaming(choose, play, numPlayer, number ,1 );
            numPlayer++;
            if (numPlayer == play.size())
            {
                numPlayer = 0;
            }
            //system ("CLS");
        }
    }
}

void Control ::setStateForWar(int numPlayer)
{
    state.displayState();
    std ::cout << "\nplayer " << numPlayer+1 <<" select the state for war : ";
    std ::string s;
    std ::cin >> s;
    state.setState(s);
}

int Control ::foundLargestScore(std::vector<Player> &player) //found largest score
{
    int max = 0;
    for (int i = 0; i < player.size(); i++)
    {
        if (player[i].getScore() > max)
        {
            max = player[i].getScore();
        }
    }
    return max;
}

void Control ::checkWinner(std::vector<Player> &player, int numPlayer)
{
    if (player[numPlayer].returnSize() >= 3 && state.checkAdjacent(player, numPlayer))
    {
        system("CLS");
        std ::cout << "\n\n\t\tYOU WIN ^-^\n\n\n";
        exit(0);
    }
    if (player[numPlayer].returnCapturedProvinces().size() == 5)
    {
        system("CLS");
        std ::cout << "\n\n\t\tYOU WIN ^-^\n\n\n";
        exit(0);
    }
}

void Control ::checkTheScoreOfPlayer(std::vector<Player> &player)
{
    for (int i = 0; i < player.size(); i++)
    {
        if (player[i].getScore() == foundLargestScore(player))
        {
            score.push_back(i);
        }
    }
}

void Control ::DetermineTheWinnerOfTheProvince(std ::vector<int> &score, std::vector<Player> &player , int &numPlayer)
{
    if (score.size() == 1)
    {
        player[score[0]].addState(state.getState(),state);
        checkWinner(play , numPlayer);
        deletPlayedCardVec(player, card);
        showStateForPlayer(player);
        setStateForWar(theMostPlayedHeroineCard(player));
        checkWinner(play , numPlayer);
        numPlayer = score[0]-1;
    }
    else
    {
        setStateForWar(FindTheLastPersonWhoPassed(player));
        deletPlayedCardVec(player, card);
        showStateForPlayer(player);
    }
}

void Control ::pass(std ::string chose, std::vector<Player> &player, int &numPlayer, int &num)
{
    if (chose == "pass")
    {
        player[numPlayer].chengePass(num);
        num++;
        std ::cout << "Player " << numPlayer + 1 << " has passed.\n";
        checkPass(play , numPlayer);
    }
}

void Control ::checkPass(std::vector<Player> &player , int &numplayer)
{
    int count = 0;
    for (int i = 0; i < player.size(); i++)
    {
        if (player[i].getPass() != 0)
        {
            count++;
        }
    }
    if (count == player.size())
    {
        preference(player);
        foundLargestScore(player);
        checkTheScoreOfPlayer(player);
        DetermineTheWinnerOfTheProvince(score, player , numplayer);
        chargeHand(player, card );
    }
}

int Control ::FindTheLastPersonWhoPassed(std::vector<Player> &player)
{
    int count = 1;
    int j = 0;
    for (int i = 0; i < player.size(); i++)
    {
        if (player[i].getPass() > count)
        {
            count = player[i].getPass();
            j = i + 1;
        }
    }
    return j;
}

void Control ::RemovalOfTheOccupiedProvince(State &s, std ::string sta)
{
    bool validInput = false;
    while (!validInput)
    {
        // Trim leading and trailing whitespace
        sta.erase(std::remove_if(sta.begin(), sta.end(), ::isspace), sta.end());
        // Check if province exists in the vector
        for (const auto &province : s.returnProvinces())
        {
            std::string trimmedProvince = province;
            trimmedProvince.erase(std::remove_if(trimmedProvince.begin(), trimmedProvince.end(), ::isspace), trimmedProvince.end());
            if (trimmedProvince == sta)
            {
                s.deletProvinces(trimmedProvince); // Call deleteProvinces to remove the province
                validInput = true;
                break;
            }
        }

        if (!validInput)
        {
            std::cout << "ERROR!!!\nProvince not found in Provinces. Please choose again:\n";
            std::cin.clear();                                                   // Clear input error flags
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore remaining input
        }
    }
    system("CLS"); // Clear screen
}

void Control ::deletPlayedCardVec(std::vector<Player> &player, Cart &cart)
{
    for (int i = player.size() - 1; i >= 0; --i)
    {
        player[i].emptyAllVectors(cart);
        player[i].setScoreOfPlayer(0);
        player[i].chengePass(0);
    }
    score.clear();
}

void Control ::showStateForPlayer(std::vector<Player> &player)
{
    for (int i = 0; i < player.size(); i++)
    {
        std ::cout << "\nplayer " << i+1 << " : ";
        player[i].printState();
    }
    std :: cout << std :: endl;
}

bool Control ::help(std ::string chose)
{
    if (chose == "help")
    {
        system("start powershell -ExecutionPolicy Bypass -File D:\\finalproject\\PowerShell\\help.ps1\"");
        return true;
    }
    else if (chose == "helpRishSefid")
    {
        system("start powershell -ExecutionPolicy Bypass -File D:\\finalproject\\PowerShell\\doyen.ps1\"");
        return true;
    }
    else if (chose == "helpMatarsak")
    {
        system("start powershell -ExecutionPolicy Bypass -File D:\\finalproject\\PowerShell\\scarecrow.ps1\"");
        return true;
    }
    else if (chose == "helpParchamDar")
    {
        system("start powershell -ExecutionPolicy Bypass -File D:\\finalproject\\PowerShell\\gonfalonier.ps1\"");
        return true;
    }
    else if (chose == "helpTablZan")
    {
        system("start powershell -ExecutionPolicy Bypass -File D:\\finalproject\\PowerShell\\drummer.ps1\"");
        return true;
    }
    else if (chose == "helpBahar")
    {
        system("start powershell -ExecutionPolicy Bypass -File D:\\finalproject\\PowerShell\\spring.ps1\"");
        return true;
    }
    else if (chose == "helpZemestan")
    {
        system("start powershell -ExecutionPolicy Bypass -File D:\\finalproject\\PowerShell\\winter.ps1\"");
        return true;
    }
    else if (chose == "helpShirZan")
    {
        system("start powershell -ExecutionPolicy Bypass -File D:\\finalproject\\PowerShell\\heroine.ps1\"");
        return true;
    }
    else if (chose == "helpShahDokht")
    {
        system("start powershell -ExecutionPolicy Bypass -File D:\\finalproject\\PowerShell\\princess.ps1\"");
        return true;
    }
    return false;
}

bool Control ::hasWinterInHand(std::vector<Player> &player)
{
    int count = 0;
    for (int i = 0; i < player.size(); i++){
        if (player[i].hasWinterInPlayedCard()){
            count++;
        }
    }
    if (count != 0)
        return true;
    return false;
}

void Control ::preference(std::vector<Player> &player)
{
    for (int i = 0; i < player.size(); i++)
    {
        player[i].calculateScore();
    }
    Winter winter;
    Drummer drummer;
    Spring spring;
    Heroine heroine;
    Princess princess;
    int j=0;
    for (int i = 0; i < player.size(); i++)
    {
        for (int j = 0; j < player[i].getPlayedCardsSize(); ++j)
        {
            if (player[i].indexPlayeCards(j) == "zemestan")
            {
                winter.use(player, 0);
            }
            else if (player[i].indexPlayeCards(j) == "tabl_zan")
            {
                if (hasWinterInHand(player))
                {
                    player[i].setScoreOfPlayer(0);
                    player[i].calculateScore();
                    drummer.use(player, i);
                }
                else{
                    drummer.use(player, i);
                }
            }
            else if(player[i].indexPlayeCards(j) == "bahar"){
                if(hasWinterInHand(player)){
                    for (int k = 0 ; k < player.size(); k++)
                    {
                        player[k].setScoreOfPlayer(0);
                        player[k].calculateScore();
                        spring.use(player, 0);
                    }
                }else{
                    spring.use(player, 0);
                }
            }
        }
    }
    for (int i = 0; i < player.size(); i++)
    {
        for (int j = 0; j < player[i].getPlayedCardsSize(); ++j)
        {
            if (player[i].indexPlayeCards(j) == "shir_zan")
            {
                Heroine heroine;
                heroine.use(player, i);
            }
            else if (player[i].indexPlayeCards(j) == "shah_dokht")
            {
                Princess princess;
                princess.use(player, i);
            }
        }
    }
}

bool Control ::hasSpringInHand(std::vector<Player> &player)
{
    int count = 0;
    for (int i = 0; i < player.size(); i++)
    {
        if (player[i].hasSpringInPlayedCard())
        {
            count++;
        }
    }
    if (count != 0)
    {
        return true;
    }
    else{
        return false;
    }
}

void Control :: gaming(std ::string choose, std::vector<Player> &player, int &numPlayer, int &num , int n){
    if(n==1){ show(player);}
   //show(player);
    if(player[numPlayer].getPass()==0){
        std :: cout << state.getState() << std :: endl ;
        player[numPlayer].showHand();
        std :: cout << "@ player" << numPlayer+1 <<" : " ;
        std :: cin >> choose;;
        bool helpExecuted = help(choose); // Call help and get the return value
        // Check if any help condition was executed
        if (helpExecuted) {
            // Request new input from the user
            std::cout << "@ player" << numPlayer+1 << " : "; 
            std :: cin >> choose ;
        }
        if(choose == "save"){
            save.saveGame(play , getNumber() , numPlayer , state.getState());
            menu();
        }
        // Check if the player chose to pass
        if (choose == "pass") {
            pass(choose, player, numPlayer, num);
        } else {
            player[numPlayer].chooseCard(choose);
            run(choose, numPlayer);
        }
    }
}

void Control :: menu(){
    int number;
    state.pushBackProvinces();
    std :: cout << "\n1 : new game\n2 : load game\n3 : exit\n\n";
    std :: cout << "Select an option: "; 
    std :: cin >> number;
    switch (number)
    {
        case 1://start new game
            getData();
            gamePlay();
            break;
        case 2:
            loadGame();
            displayAfterLoad();
            break;
        case 3: 
            exit(0);
            break;
        default:
            break;
    }
}


void Control :: loadGame(){
    save.printSavedGames();
    std :: vector < std ::string >savedGames;
    for(const auto &entry : std ::filesystem::directory_iterator(".")){
        if (entry.path().extension()==".sav")
        {
            savedGames.push_back(entry.path().filename().string());
        }
    }
    if(savedGames.empty()){
        std :: cout << "there is now game to load . ";
    }
    int gameChoice ;
    std :: cout << "select the number of the game to load : " ;
    std :: cin >> gameChoice ;

    play.clear(); // clear player vector
    score.clear(); // clear score vector
    ageOfPlayer.clear();

     // Determine the filename of the selected game to load
    std::string filename = savedGames[gameChoice - 1];
    int startingPlayerIndex ;
    std :: string province;
    if (save.loadGame( filename , play, number , startingPlayerIndex , province) ) {
        setNumber(number);
        setNumber(startingPlayerIndex);
        state.setState(province);
    } else {
        std::cout << "Failed to load game. File does not exist or is corrupted.\n";
        
    }
}

void Control ::displayAfterLoad(){
    
    std ::string choose;
    int number = 1;
    bool win = false;
    int numPlayer = getNumber() ;
    while (!win)
    {
        while (numPlayer < play.size())
        {
            gaming(choose, play, numPlayer, number , 0);
            numPlayer++;
            if (numPlayer == play.size())
            {
                numPlayer = 0;
            }
        }
    }
}

bool Control::areAllHandsEmpty(std::vector<Player> &player){
    int count=0;
    for ( auto & players : player) {
        if (players.returnHand().size()==0) {
            count ++;
        }
    }
    if(count==player.size()-1){
        return true;
    }else{
        return false;
    }
}

void Control :: chargeHand(std::vector<Player> &player , Cart &cart){
    if(areAllHandsEmpty(player)){
        for (int i = player.size() - 1; i >= 0; --i)
        {
            player[i].emptyHandVectors(cart);
            dealCardsToPlayers(10+player[i].returnSize());
        }
    }
}

int Control :: theMostPlayedHeroineCard(std::vector<Player> &player ){
    int largeHero = 0;
    int index=0;
    for (int i = 0; i < player.size(); i++)
    {
       if (player[i].getHeroine()>largeHero)
       {
            largeHero=player[i].getHeroine();
            index = i;
       }
    }
    return index;
}