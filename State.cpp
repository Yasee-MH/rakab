#include "State.h"

bool State ::areAdjacent(const std::string &firstState , const std::string &secondState){
    return adjacencySet.count({firstState,secondState})>0;
}

void  State::readMapFromFile(const std :: string &filename){
    std ::ifstream inFile(filename);
    if(!inFile){
        std::cerr<<"UNable to open file: "<<filename<<std::endl;
        return;
    }
    std ::string  stateName[]={ "BELLA" , "CALINE" , "ENNA" , "ATELA" , "PLADACI" , "BORGE" , "DIMASE" , "MORINA"
                              "OLIVADI" , "ROLLO" , "TALMONE" , "ARMENTO" , "LIA" , "ELINIA" };
    for (int i = 0; i < 14; i++)
    {
        for (int j = 0 ; j < 14 ; j++)
        {
            int adjacency;
            inFile>>adjacency;
            if(adjacency==1)
            {
                adjacencySet.insert({stateName[i],stateName[j]}) ;
                adjacencySet.insert({stateName[i],stateName[j]}) ;
            }
        }
    }
    inFile.close();
}

bool State ::checkAdjacent(std :: vector<Player> &player ,int numPlayer){
    std :: string fileName="adjacencyMatrix.txt";
    readMapFromFile(fileName);

    std :: string s1 = player[numPlayer].indexCapturedProvinces(0);
    std :: string s2 = player[numPlayer].indexCapturedProvinces(1);
    std :: string s3 = player[numPlayer].indexCapturedProvinces(2);
    int count=0;
    if(areAdjacent(s1,s2)){
        count++;
    }
    if(areAdjacent(s1,s3))
    {
        count++;
    }
    if (areAdjacent(s2,s3))
    {
        count++;
    }
    if(count>=2){
        return true;
    }else{
        return false;
    }

}


void  State :: setState(std::string s){state=s;}

std :: string State:: getState(){return state;}

void State:: deletProvinces(std :: string &p){
    p.erase(std::remove_if(p.begin(), p.end(), ::isspace), p.end());
    auto it = std :: find( Provinces.begin() , Provinces.end() , p );
    if ( it != Provinces.end() )
    {
        Provinces.erase(it);
    }
    else{
        std::cout << "State not found in Provinces. Please choose again.\n";
        std :: cin >> state ;
        state.erase(std::remove_if(state.begin(), state.end(), ::isspace), state.end()); // Remove whitespaces
        deletProvinces(state);
    }
}

void State :: displayState(){
    for(const auto& state : Provinces){
        std :: cout << state << " , "; 
    }
    
}

std::vector< std :: string > State ::returnProvinces(){
  return Provinces;
}

void State :: pushBackProvinces(){
    Provinces.push_back("BELLA");
    Provinces.push_back("CALINE");
    Provinces.push_back("ENNA");
    Provinces.push_back("ATELA");
    Provinces.push_back("PLADACI");
    Provinces.push_back("BORGE");
    Provinces.push_back("DIMASE");
    Provinces.push_back("MORINA");
    Provinces.push_back("OLIVADI");
    Provinces.push_back("ROLLO");
    Provinces.push_back("TALMONE" );
    Provinces.push_back("ARMENTO");
    Provinces.push_back("LIA" );
    Provinces.push_back("ELINIA" );

}
