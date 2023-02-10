#include "Map.h"
#include <iostream>
using std:: endl;
using std:: cout; 
#include <fstream>
using std::ifstream;
#include <sstream>






// The player.h file should be included in order to create a new player in the copy constructor for the territory class. 
// #include <Player.h>


//////////// TERRITORY CLASS SECTION  /////////////

string Territory:: getName(){
    return name; 
}

int Territory:: getArmy(){
    return army; 
}

Player* Territory:: getOwner(){
    return owner;
}

Continent* Territory:: getContinent(){
    return inContinent;
}

int Territory:: getContinentID(){
    return continentID;
}

int Territory:: getTerritoryID(){
    return territoryID;
}

vector <Territory*> Territory:: getAdjacentTerritories(){
    return adjacentTerritories;
}

void Territory:: setName(string name){
    this->name = name; 
}

void Territory:: setArmy(int army){
    this->army = army;
}

void Territory:: setOwner(Player* owner){
    this->owner = owner; 
}

void Territory:: setContinent(Continent* inContinent){
    this->inContinent = inContinent;
}

void Territory:: setContinentID(int continentID){
    this->continentID = continentID;
}

void Territory:: setTerritoryID(int territoryID){
    this->territoryID = territoryID;
}

void Territory:: setAdjacentTerritory(Territory* adjacentTerritory){
    this->adjacentTerritories.push_back(adjacentTerritory);
}

Territory:: Territory(){
    this->army = 0;
    this->owner = nullptr;
    this->name = "";
}

Territory:: Territory(string name, Continent* inContinent){
    this->name = name; 
    this->inContinent = inContinent;
}

Territory:: Territory(string name, int territoryID){
    this->name = name; 
    this->territoryID = territoryID;
}

Territory:: Territory(const Territory& copy){
    this->army = copy.army; 
    this->name = copy.name;
    // this->owner = new Player(*oldTerritory.owner);       remove the comment once the player.h file is included 
}

void Territory:: operator =(const Territory& rhs){
    this->army = rhs.army;
    this->name = rhs.name;
    // this->owner = new Player(*rhs.owner);       remove the comment once the player.h file is included 
}

ostream& operator <<(ostream& output,  Territory& t){
    output << t.getName();
    return output; 
}

Territory:: ~Territory(){
    //delete owner;         I need to include the player class first to use its destructor 
    owner = nullptr;
    delete this; 
}


/////////////// CONTINENT CLASS SECTION  ///////////////



vector <Territory*> Continent:: getTerritories(){
    return territories;
}

string Continent:: getName(){
    return name; 
}

int Continent:: getBonus(){
    return bonus;
}

int Continent:: getID(){
    return id;
}

void Continent:: setTerritories(Territory* territory){
    this->territories.push_back(territory);
}

void Continent:: setName(string name){
    this->name = name; 
}

void Continent:: setBonus(int bonus){
    this->bonus = bonus;
}

void Continent:: setID(int id){
    this->id = id; 
}

Continent:: Continent(){
    territories = vector <Territory*> ();
    name = "";
}

Continent:: Continent(string name, int bonus, int id){
   // territories = vector <Territory*> ();
    this->name = name; 
    this->bonus = bonus;
    this->id = id; 
}

Continent:: Continent(const Continent& copy){
    this->name = copy.name;
    this->territories = vector <Territory*> ();
    for(auto it : copy.territories){
        this->territories.push_back(new Territory (*it));
    }
}

void Continent:: operator=(Continent& rhs){
    this->name = rhs.name; 
    if (territories.size() > 0){
        for(auto it: territories){
            delete it;
            it = nullptr;
        }
    }
    this->territories = vector <Territory*> ();
    for (auto it: rhs.territories){
        this->territories.push_back(new Territory(*it));
    }
}

Continent:: ~Continent(){
    for (auto it: territories){
        delete it;
        it = nullptr;
    }
    delete this;
}

ostream& operator<<(ostream& output,  Continent& c){
    output << c.getName();
    return output;
}


//////////////// MAP CLASS SECTION ///////////////

vector <Territory*> Map:: getTeritories(){
    return territories;
}

vector <Continent*> Map:: getContinents(){
    return continents;
}

string Map:: getName(){
    return name;
}

void Map:: setTerritories(Territory* territory){
    this->territories.push_back(territory);
}

void Map:: setContinents(Continent* continent){
    this->continents.push_back(continent);
}

void Map:: setName(string name){
    this->name = name;
}

Map :: Map(){
    name = "";
    vector <Territory*> territories ();
    vector <Continent*> continents ();
}

Map:: Map(vector <Territory*> territories, vector <Continent*> continents){
    name = "";
    this->territories = territories;
    this->continents = continents;
}

Map:: Map(const Map &copy){
    this->name = copy.name;
    this->territories = vector <Territory*> ();
    for (auto it : copy.territories){
        territories.push_back(new Territory(*it));
    }

    this->continents = vector <Continent*> ();
    for (auto it: copy.continents){
        continents.push_back(new Continent(*it));
    }
}

void Map:: operator=(const Map& rhs){
    this->name = rhs.name;
    if (territories.size() > 0){
        for(auto it : territories){
            delete it; 
            it = nullptr;
        }
    }
    this->territories = vector <Territory*> ();
    for (auto it : rhs.territories){
        this->territories.push_back(new Territory(*it));
    }
    if (continents.size() > 0){
        for (auto it : continents){
            delete it;
            it = nullptr;
        }
    }
    this->continents = vector <Continent*> ();
    for (auto it: rhs.continents){
        this->continents.push_back(new Continent(*it));
    }
}

int count = 0;
void Map:: mapTraversal(Territory* current, vector <Territory*> &visitedTerritories){
    for(auto territory: visitedTerritories){
        if(territory == current){
            return;
        }
    }
    
    visitedTerritories.push_back(current);
    for(auto adjTerritory: current->getAdjacentTerritories()){
        mapTraversal(adjTerritory, visitedTerritories);
    }
}

void Map:: mapTraversal(Territory* current, vector <Territory*> &visitedTerritories, string currentContinent){
      for(auto territory: visitedTerritories){
        if(territory == current || (currentContinent != current->getContinent()->getName())){
            return;
        }
    }
  
    visitedTerritories.push_back(current);
 
    for(auto adjTerritory: current->getAdjacentTerritories()){
        if(currentContinent == adjTerritory->getContinent()->getName()){
              mapTraversal(adjTerritory, visitedTerritories,currentContinent);
        } else {
            continue;
        }
    }
}

// The validate method checks three things: 
// 1) if no territory duplicates are present
// 2) if the map is connected 
// 3) if the map is a connected subgraph 

void Map:: validate(){

// This block checks if a territory belongs to only one continent, no duplicates are allowed
    for(int i = 0; i < territories.size(); i++){
        for (int j = 1 + i; j < territories.size(); j++){
            if (territories[i]->getName() == territories[j]->getName()){
                cout<<"Error. Duplicate territory ["<<territories[i]->getName()<<"] "<<"was found. Invalid map."<<endl;
                return;
            }
        }
    }


// The mapTraversal method with 2 arguments checks if the map is connected as a whole
// this method checks if all territories in the map can be reached from one territory (starting point)
    
  
    vector <Territory*> visitedTerritories; 
    mapTraversal(this->territories[0], visitedTerritories);
    if (visitedTerritories.size() != this->territories.size()) {
        cout<<"This map is not connected: Invalid map. "<<endl;
        return;
    } 

// The mapTraversal method with 3 arguments checks if the map is connected as a subgraph
// to verify that, we isolate each continent and iterate through its territories to see 
// if we can reach the other territories that belong to the same continent

    visitedTerritories.clear();
    for (auto it: continents) {
        mapTraversal(it->getTerritories()[0], visitedTerritories, it->getName());
        if (visitedTerritories.size() != it->getTerritories().size()){
            cout<<"This map is not a connected subgraph: Invalid map. "<<endl;
            return;
        }
        visitedTerritories.clear();
    }
    cout<<"The map is connected and is a subgraph: Valid map. "<<endl;
}

Map:: ~Map(){
    for (auto it : territories){
        delete it; 
        it = nullptr;
    }
    for (auto it : continents){
        delete it;
        it = nullptr;
    }
    delete this; 
}

ostream& operator << (ostream& output,  Map& m){
    output<<m.getName();
    return output;
}


////////////  MAPLOADER CLASS SECTION  /////////////


void MapLoader:: setName(){
    this->name = name;
}

string MapLoader:: getName(){
    return name;
}
MapLoader:: MapLoader(){
    name = "";
}

MapLoader :: MapLoader(const MapLoader& copy){
    this->name = copy.name;
}

void MapLoader:: operator=(const MapLoader & rhs) {
    this-> name = rhs.name;
}

ostream& operator <<(ostream& output,  MapLoader & map){
    output<<map.getName()<<endl;
    return output;
}

MapLoader:: ~MapLoader() {delete this;}

vector <string> MapLoader:: split(string readLine){
    vector <string> tokens;
    string token; 
    stringstream ss(readLine);
    while(getline(ss, token, ' ')){
        tokens.push_back(token);
    }
    return tokens; 
}

Map* MapLoader:: loadMap(string file){
    cout<<"\nLoading map: "<<file<<endl;
    Map* map = new Map();
    ifstream inputStream;
    string extension = file.substr(file.find("."), file.length());
    inputStream.open(file);
    if(!inputStream){
        cout<<"Error. map file does not exist."<<endl;
        return map;
    } else if (extension != ".map"){
        cout<<"Error. Input file is using an invalid extension."<<endl;
        return map; 
    }
    cout<<"Map file found. Generating map: "<<endl;
    

    bool continentsExist = false; 
    bool territoriesExist = false;
    string readLine;
    while (getline(inputStream, readLine)){
        if (readLine == "[continents]"){
            continentsExist = true;
            break;
        }
    }

    if (!continentsExist){
        cout<<"Map file is invalid. The Continents section does not exist."<<endl;  
        return map; 
    }

    int continentID = 0;
    while(getline(inputStream, readLine)){
        //marking the end of the continents section
        if (readLine == ""){
            break;
        }

        ++continentID;
        vector <string> splitVector = split(readLine);
        string continentName = splitVector[0];
        int continentBonus = stoi(splitVector[1]);

        Continent* continent = new Continent(continentName, continentBonus, continentID);
        map->setContinents(continent);
        // I'm not sure if I should delete the continent pointer here after it has been added to the list of continents belonging to the map already
        // ^ will review this :))
    }

    int territoryID = 0; 
    while (getline(inputStream, readLine)){
        if (readLine == "[countries]"){
            territoriesExist = true; 
            break;
        }
    }

    if(!territoriesExist){
        cout<<"Map file is invalid. The Countries section does not exist."<<endl;  
        return map;
    }


    while(getline(inputStream, readLine)){
        if (readLine == ""){
            break;
        }
        ++territoryID;
        vector <string> splitvector = split(readLine);
        string territoryName = splitvector[1];
        int conID = stoi(splitvector[2]);
        Territory* territory = new Territory(territoryName, territoryID);
        for(auto it: map->getContinents()){
            if (it->getID() == conID){
                territory->setContinent(it);
                it->setTerritories(territory);
            }
        }
        map->setTerritories(territory);
    }

    while(getline(inputStream, readLine)){
        if(readLine == "[borders]"){
            break;
        }
    }

    while(getline(inputStream, readLine)){
        if (readLine == ""){
            break;
        }
        vector <string> splitvector = split(readLine);
        int currentTerritoryID = stoi(splitvector[0]);
        for(int i = 1; i < splitvector.size(); i++){
            for(auto it : map->getTeritories()){
                if (stoi(splitvector[i]) == it->getTerritoryID()){
                    map->getTeritories()[currentTerritoryID - 1]->setAdjacentTerritory(it);
                }
            }
        }
    }
return map; 
}


