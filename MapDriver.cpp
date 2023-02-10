// The insertion stream operator does not work for me so I am using the getName() function to print out objects in the meantime
// Will fix when I figure it out

#include "Map.h"
#include <iostream>
using std:: end;
using std:: cout;

int main () {


cout<<"**** MAP SECTION ****"<<endl;

MapLoader* loader = new MapLoader();

// Example of a map file that doesn't exist
Map* map1 = loader->loadMap("house.map");

// Examples of both valid/invalid map files
Map* map2 = loader->loadMap("Chrono_Trigger.map");        
map2->validate();
Map* map3 = loader->loadMap("periodict.map");         
map3->validate();
Map* map4 = loader->loadMap("solar.map");      
map4->validate();
Map* map5 = loader->loadMap("europe.map");      
map5->validate();



// Prints continents of map 5 - europe.map
// I'm trying to print out the continent object but I get its address instead of its name 
cout<< "\nContinents in map [europe.map]:"<<endl;
for(auto it: map5->getContinents()){
    cout<<it<<endl;
} 


// Prints territories of a continent in map 5 - europe.map
for(auto continent: map5->getContinents()){
    cout<<"\nContinent "<<continent->getName()<<" has territories: "<<endl;
    for(auto territory: continent->getTerritories()){
        cout<<territory->getName()<<endl;
    }
}

// Prints adjacent territories of some territories in map 5 - europe.map

for (int i = 0; i <= 3 ; i++){
    cout<<"\nTerritory "<<map5->getTeritories()[i]->getName()<<" has these adjacent territories: "<<endl;
    for(int j = 0; j < map5->getTeritories()[i]->getAdjacentTerritories().size(); j++){
        cout<<map5->getTeritories()[i]->getAdjacentTerritories()[j]->getName()<<endl;
    }
}

cout<<"\n**** MAP END ****"<<endl;

}