#pragma once
#include <string>
#include <vector>
using namespace std;
class Player; 
class Continent; 


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
    string getName();                                    
    int getArmy();                                      
    Player* getOwner();                                   
    Continent* getContinent();                          
    int getContinentID();                                
    int getTerritoryID();     
    vector <Territory*> getAdjacentTerritories();         


    void setName(string name);                           
    void setArmy(int army);                               
    void setOwner(Player* owner);                         
    void setContinent(Continent* inContinent);              
    void setContinentID(int continentID);                   
    void setTerritoryID(int territoryID);      
    void setAdjacentTerritory(Territory* adjacentTerritory);      

    Territory();                                      
    Territory(string name, Continent* inContinent);     
    Territory(string name, int territoryID);                              
    //Territory(string name, int army, Player* owner);   

    // copy constructor 
    Territory(const Territory& copy);                     

    // assignment constructor 
    void operator =(const Territory& rhs);                

    //insertion operator 
    friend ostream& operator<<(ostream& out, const Territory& t);   

    // destructor 
    ~Territory();                     




};

class Continent {
private: 
    vector <Territory*> territories; 
    string name; 
    int bonus;
    int id;

public: 
    vector <Territory*> getTerritories();     
    string getName();    
    int getBonus();     
    int getID();      

    void setTerritories(Territory* territory);      
    void setName(string name);          
    void setBonus(int bonus);      
    void setID(int id);   

    Continent();       
    Continent(string name, int bonus, int id);    

    //copy constructor 
    Continent(const Continent& copy);   

    // assignment constructor 
    void operator=(Continent& rhs);     

    ~Continent();     

    //insertion operator 
    friend ostream& operator<<(ostream& output, const Continent& c);     


};

class Map {
private:
    vector <Territory*> territories;
    vector <Continent*> continents;
    string name;

public: 
    void validate();       
    void mapTraversal(Territory* current, vector <Territory*> &visitedTerritories);          
    void mapTraversal(Territory* current, vector <Territory*> &visitedTerritories, string name); 

    vector <Territory*> getTeritories();        
    vector <Continent*> getContinents();        
    string getName();     

    void setTerritories(Territory* territory);      
    void setContinents(Continent* continent);        
    void setName(string name);     

    Map();          
    Map(vector <Territory*> territories, vector <Continent*> continents);      

    //copy constructor 
    Map(const Map& copy);      

    //assignment constructor 
    void operator= (const Map& rhs);      

    //destructor 
    ~Map();                

    //insertion operator 
    friend ostream& operator<< (ostream& output,  const Map& m);      

};

class MapLoader{
public: 

    MapLoader();       

    MapLoader(const MapLoader& copy);   

    void operator=(const MapLoader &rhs);      

    Map* loadMap(string file);    

    vector <string> split(string readLine);     

    ~MapLoader();      

    friend ostream& operator<<(ostream& output, const MapLoader &m);       
};
