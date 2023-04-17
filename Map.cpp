#include "Map.h"
#include <iostream>
using std:: endl;
using std:: cout; 
#include <fstream>
using std::ifstream;
#include <sstream>









//                                                  **************** TERRITORY CLASS SECTION   ****************

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

Territory:: Territory(string name){
    this->army = 0;
    this->name = name; 
    this->owner = nullptr;

}

Territory:: Territory(string name, Continent* inContinent){
    this->name = name; 
    this->inContinent = inContinent;
    this->army = 0;
    this->owner = nullptr;

}

Territory:: Territory(string name, int territoryID){
    this->name = name; 
    this->territoryID = territoryID;
    this->owner = nullptr;
    this->army = 0;
}

Territory:: Territory(const Territory& copy){
    this->army = copy.army; 
    this->name = copy.name;
    this->owner = copy.owner;
}

Territory& Territory:: operator =(const Territory& rhs){
    this->army = rhs.army;
    this->name = rhs.name;
    this->owner = rhs.owner;
    return *this;
}

ostream& operator <<(ostream& output,  Territory& t){
    output << t.getName();
    return output; 
}

Territory:: ~Territory(){}


//                                              **************** CONTINENT CLASS SECTION   ****************



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
    territories = vector <Territory*> ();
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

Continent& Continent:: operator=(Continent& rhs){
    this->name = rhs.name; 
    this->territories = rhs.territories;
    return *this;
}

Continent:: ~Continent(){}


ostream& operator<<(ostream& output,  Continent& c){
    output << c.getName();
    return output;
}


//                                                **************** MAP CLASS SECTION  ****************

vector <Territory*> Map:: getTerritories(){
    return territories;
}

vector <Continent*> Map:: getContinents(){
    return continents;
}

string Map:: getName(){
    return name;
}

bool Map:: getIsValid(){
    return isValid; 
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

void Map:: setIsValid(bool isValid){
    this->isValid = isValid; 
}

Map :: Map(){
    name = "";
    vector <Territory*> territories;
    vector <Continent*> continents;
}

Map:: Map(string name){
    this->name = name;
    vector <Territory*> territories;
    vector <Continent*> continents;
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

Map& Map:: operator=(const Map& rhs){
    this->name = rhs.name;
    this->territories = rhs.territories;
    this->continents = rhs.continents;
    return *this;
}



/* This function traverses the map as a whole from one territory as a starting point
   The map is connected if all nodes (territories) can be reached from that starting point
*/
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



/* The mapTraversal method with 3 arguments checks if the map is connected as a subgraph
   to verify that, we isolate each continent and iterate through its territories to see 
   if we can reach the other territories that belong to the same continent
*/


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
                isValid = false; 
                return;
            }
        }
    }
  
    vector <Territory*> visitedTerritories; 
    mapTraversal(this->territories[0], visitedTerritories);
    if (visitedTerritories.size() != this->territories.size()) {
        cout<<"This map is not connected: Invalid map. "<<endl;
        isValid = false; 
        return;
    } 

    visitedTerritories.clear();
    for (auto it: continents) {
        mapTraversal(it->getTerritories()[0], visitedTerritories, it->getName());
        if (visitedTerritories.size() != it->getTerritories().size()){
            cout<<"This map is not a connected subgraph: Invalid map. "<<endl;
            isValid = false; 
            return;
        }
        visitedTerritories.clear();
    }
    isValid = true; 
    cout<<"The map is connected and is a subgraph, with no duplicate territories: Valid map. "<<endl;
}

void Map::reset() {
    for (int i = 0; i < territories.size(); i++) {
        territories[i]->setArmy(0);
        if (territories[i]->getOwner()) {
            // territories[i]->getOwner()->clearPlayerTeritories();
            territories[i]->setOwner(NULL);
        }
    }
}

Map:: ~Map(){

   for (auto it : continents){
        delete it;
        it = nullptr;
    }
  
    for (auto it : territories){
        delete it; 
        it = nullptr;
    }
    
}

ostream& operator << (ostream& output,  Map& m){
    output<<m.getName();
    return output;
}


//                                                     ****************  MAPLOADER CLASS SECTION   ****************


void MapLoader:: setName(string name){
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

MapLoader& MapLoader:: operator=(const MapLoader & rhs) {
    this-> name = rhs.name;
    return *this;
}

ostream& operator <<(ostream& output,  MapLoader & map){
    output<<map.getName()<<endl;
    return output;
}

MapLoader:: ~MapLoader() {}


// This function takes a line read from the .map file (readLine) and splits it by the " " delimiter,
// Which then gets stored in the tokens vector for easy access 

vector <string> MapLoader:: split(string readLine){
    vector <string> tokens;
    string token; 
    stringstream ss(readLine);
    while(getline(ss, token, ' ')){
        tokens.push_back(token);
    }
    return tokens; 
}


// The below function is responsible for reading map files and creating territory/continent objects 
// While also adding a list of adjacent territories to a certain territory


Map* MapLoader:: loadMap(string file){
    cout<<"\nLoading map: "<<file<<endl;
    Map* map = new Map(file);
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
    


// First, we search for the continents section in the .map file 

    bool continentsExist = false; 
    bool territoriesExist = false;
    string readLine;
    while (getline(inputStream, readLine)){
        if (readLine == "[continents]"){
            continentsExist = true;
            break;
        }
    }

// Map is invalid if continents do not exist 
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


// Here is where I create the continent objects.
// I keep track of the continent index for future use (so I can set the territories that belong to it)
// The continent ID is just the order of appearance of the continent in the .map file 

// Split is used to split the read string in order to separate the continent name and continent bonus 
        ++continentID;
        vector <string> splitVector = split(readLine);
        string continentName = splitVector[0];
        int continentBonus = stoi(splitVector[1]);

        Continent* continent = new Continent(continentName, continentBonus, continentID);
        map->setContinents(continent);
      
    }


// We skip to the countries (or territories) section in the block below

    int territoryID = 0; 
    while (getline(inputStream, readLine)){
        if (readLine == "[countries]"){
            territoriesExist = true; 
            break;
        }
    }

// Map is invalid if no territories/countries exist

    if(!territoriesExist){
        cout<<"Map file is invalid. The Countries section does not exist."<<endl;  
        return map;
    }


    while(getline(inputStream, readLine)){
        if (readLine == ""){
            break;
        }

// Creating the territory objects: 

/* The format of the .map file is this:
 first number is the index of the territory, second is the name of the territory, 
 third is the index of the continent it belongs to, and the rest are the coordiantes, which are unnecessary for my implementation 
*/

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

// The borders section is responsible for setting the adjacent territories for a territory 
// The format of this section in the map file is: first number is the territory index, and the rest are indexes of the adjacent territories to it

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
            for(auto it : map->getTerritories()){
                if (stoi(splitvector[i]) == it->getTerritoryID()){
                    map->getTerritories()[currentTerritoryID - 1]->setAdjacentTerritory(it);
                }
            }
        }
    }
return map; 
}


