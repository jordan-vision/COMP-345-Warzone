// The insertion stream operator does not work for me so I am using the getName() function to print out objects in the meantime
// Will fix when I figure it out

#include "Map.h"
#include <iostream>
using std:: end;
using std:: cout;

int main () {

// Example of a valid map file 
MapLoader* loader = new MapLoader();
Map* map = loader->loadMap("solar.map");              
map->validate();

//cout<<"Fist map done"<<endl;
// Example of a map file that isn't located in the current folder
//Map* map2 = loader->loadMap("MiddleEast-Qatar.map");

// Example of a map file that is not valid
//Map* map3 = loader->loadMap("Map/france.map");
//map3->validate();




// Prints continents of map
cout<< "\nContinents : "<<endl;
for(auto it: map->getContinents()){
    cout<<it->getName()<<endl;
} 


// Prints territories of a continent
for(auto continent: map->getContinents()){
    cout<<"\nContinent "<<continent->getName()<<" has territories: "<<endl;
    for(auto territory: continent->getTerritories()){
        cout<<" "<<territory->getName();
    }
}

// The code below is just to show the adjacent territories if needed for testing purposes

/*for (auto ter : map->getTeritories()){
    cout<<"\nTerritory "<<ter->getName()<<"has these adjacent territories: "<<endl;
    for (auto adj : ter->getAdjacentTerritories()){
        cout<<adj->getName();
    }
}*/

}