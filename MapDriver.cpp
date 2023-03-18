
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

/*  Solar map was modified by adding a new continent containing one territory 
    which has no adjacent territories to showcase a case where the map is not connected as a whole.
    Explanation: having no adjacent territories means that it cannot be reached from the starting territor/node
    therefore, map is not connected
*/
Map* map4 = loader->loadMap("solar.map");      
map4->validate();

Map* map5 = loader->loadMap("europe.map");      
map5->validate();



// Prints continents of map 5 - europe.map
// I'm trying to print out the continent object but I get its address instead of its name 
cout<< "\nContinents in map [europe.map]:"<<endl;
for(auto it: map5->getContinents()){
    cout<<*it<<endl;
} 


// Prints territories of a continent in map 5 - europe.map
for(auto continent: map5->getContinents()){
    cout<<"\nContinent "<<*continent<<" has territories: "<<endl;
    for(auto territory: continent->getTerritories()){
        cout<<*territory<<endl;
    }
}

// Prints adjacent territories of some territories in map 5 - europe.map

for (int i = 0; i <= 3 ; i++){
    cout<<"\nTerritory "<<*map5->getTerritories()[i]<<" has these adjacent territories: "<<endl;
    for(int j = 0; j < map5->getTerritories()[i]->getAdjacentTerritories().size(); j++){
        cout<<*map5->getTerritories()[i]->getAdjacentTerritories()[j]<<endl;
    }
}

// Calling the map destructor becuase the maps have been dynamically allocated 

cout<<"\nDeleting maps: "<<endl;
vector <Map*> maps {map1, map2, map3, map4, map5};
for (auto mapObject : maps){
    delete(mapObject);
}

cout<< "Maps deleted. "<<endl;

cout<<"\n**** MAP END ****"<<endl;

}