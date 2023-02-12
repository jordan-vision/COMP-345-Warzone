#pragma once
#include <string>
#include <vector>
using namespace std;
class Player; 
class Continent; 



 /*                                       *************  TERRITORY CLASS  *************                                       */
class Territory {
private: 
    string name;
    Continent* inContinent; 
    int continentID;           
    int territoryID;        
    Player* owner;
    int army;
    vector <Territory*> adjacentTerritories;

public: 
// GETTERS                                               
    string getName();                                    
    int getArmy();                                      
    Player* getOwner();                                   
    Continent* getContinent();                          
    int getContinentID();                                
    int getTerritoryID();     
    vector <Territory*> getAdjacentTerritories();         

// SETTERS
    void setName(string name);                                         
    void setArmy(int army);                               
    void setOwner(Player* owner);                         
    void setContinent(Continent* inContinent);              
    void setContinentID(int continentID);                   
    void setTerritoryID(int territoryID);      
    void setAdjacentTerritory(Territory* adjacentTerritory);      

// CONSTRUCTORS
    Territory();                                          
    Territory(string name);                                 
    Territory(string name, Continent* inContinent);     
    Territory(string name, int territoryID);                              

// COPY CONSTRUCTOR
    Territory(const Territory& copy);                     

// ASSIGNMENT OPERATOR
    void operator =(const Territory& rhs);                

// INSERTION OPERATOR
    friend ostream& operator<<(ostream& out, Territory& t);   

// DESTRUCTOR
    ~Territory();                     

};

 /*                                       *************  CONTINENT CLASS  *************                                       */
class Continent {
private: 
    vector <Territory*> territories; 
    string name; 
    int bonus;
    int id;

public: 
// GETTERS
    vector <Territory*> getTerritories();     
    string getName();    
    int getBonus();     
    int getID();      

// SETTERS
    void setTerritories(Territory* territory);      
    void setName(string name);          
    void setBonus(int bonus);      
    void setID(int id);   

// CONSTRUCTORS
    Continent();       
    Continent(string name, int bonus, int id);    

// COPY CONSTRUCTOR
    Continent(const Continent& copy);   

// ASSIGNMENT OPERATOR 
    void operator=(Continent& rhs);     

// DESTRUCTOR
    ~Continent();     

// INSERITON OPERATOR
    friend ostream& operator<<(ostream& output, Continent& c);     


};
 /*                                       *************  MAP CLASS  *************                                       */
class Map {
private:
    vector <Territory*> territories;
    vector <Continent*> continents;
    string name;

public: 
// FUNCTIONS
    void validate();       
    void mapTraversal(Territory* current, vector <Territory*> &visitedTerritories);          
    void mapTraversal(Territory* current, vector <Territory*> &visitedTerritories, string name); 

// GETTERS
    vector <Territory*> getTeritories();        
    vector <Continent*> getContinents();        
    string getName();     

// SETTERS
    void setTerritories(Territory* territory);      
    void setContinents(Continent* continent);        
    void setName(string name);     

// CONSTRUCTORS
    Map();          
    Map(string name);
    Map(vector <Territory*> territories, vector <Continent*> continents);      

// COPY CONSTRUCTOR
    Map(const Map& copy);      

// ASSIGNMENT OPERATOR 
    void operator= (const Map& rhs);      

// DESTRUCTOR 
    ~Map();                

// INSERTIO OPERATOR
    friend ostream& operator<< (ostream& output,  Map& m);      

};
  /*                                       *************  MAPLOADER CLASS  *************                                       */
class MapLoader{
private: 
    string name;

public: 
// FUNCTIONS
    Map* loadMap(string file);    
    vector <string> split(string readLine);   

// GETTER
    string getName();

// SETTER
    void setName();

// CONSTRUCTOR
    MapLoader();       

// COPY CONSTRUCTOR 
    MapLoader(const MapLoader& copy);   

// ASSIGNMENT OPERATOR
    void operator=(const MapLoader &rhs);    

// DESTRUCTOR
    ~MapLoader();      

// INSERITON OPERATOR 
    friend ostream& operator<<(ostream& output, MapLoader &m);       
};
