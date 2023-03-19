#include "Player.h"
#include "Orders.h"
#include "Cards.h"
#include "Map.h"
#include <iostream>
#include <vector>
#include <string>


//Default constructor - initialize the player
Player::Player() 
{

}

//Destructor
Player::~Player() {
    for (Territory* td : territoriesDefend) 
        delete td;    
    for (Territory* ta : territoriesAttack) 
        delete ta; 
   for (Territory* to : territoriesOwned) 
        delete to;
   
    delete myOrders;
    delete myHand;
   
};

//Constructor that initializes the player's collection of territories (owned, defend, attack) and the player name
Player::Player(vector<Territory*> territoriesOwned, vector<Territory*> territoriesDefend, vector<Territory*> territoriesAttack, string name)
: territoriesOwned(territoriesOwned), territoriesDefend(territoriesDefend), territoriesAttack(territoriesAttack)
 {
  this->myHand = new Hand();
  this->name = name;
  this->territoriesOwned = territoriesOwned;
  this->territoriesDefend = territoriesDefend;
  this->territoriesAttack = territoriesAttack;
 }

//Constructor that initializes the player's name
 Player::Player(string name)
: name(name)
{
  this->name = name;
}
string Player:: getName(){
    return name; 
}

void Player:: setName(string name){
    this->name = name; 
}
int Player:: getArmy(){
    return army; 
}

void Player:: setArmy(int army){
    this->army = army; 
}

//Copy Constructor passing parameter p
Player::Player(const Player& p)
{
  this->myHand = p.myHand;
  this->name = p.name;
  this->territoriesOwned = p.territoriesOwned;
  this->territoriesDefend = p.territoriesDefend;
  this->territoriesAttack = p.territoriesAttack;
}

//Implementation of the friend insertion operator for class Player
ostream& operator<<(ostream& output, Player& p) {
    output << p.getName();
    return output;
}

//Implementation of the owned() method
void Player::owned(Territory* t) {
    vector<Territory*> territoriesOwned;
    this->territoriesOwned.push_back(t);
    
}

//Implementation of the toDefend() method
vector<Territory*> Player::toDefend(vector<Territory*> t) {
    vector<Territory*> territoriesDefend;

    for (int i = 0; i < t.size(); i++){
        if (t[i]->getOwner() == nullptr || t[i]->getOwner()->getName() == this->getName()){
        territoriesDefend.push_back(t[i]);
        }
    }
    return territoriesDefend;  
}



//Implementation of the toAttack() method 
// vector<Territory*> Player::toAttack() {

//    //bool push = false; 
//     vector<Territory*> territoriesAttack;
//     for (int j = 0; j < territoriesOwned.size(); j++){
//     vector<Territory*> adjacentTerritories = territoriesOwned[j]->getAdjacentTerritories();
//     for (int i = 0; i < adjacentTerritories.size(); i++)
//      {
//         if (adjacentTerritories[i] != )
       
//          for(int k = 0; k < territoriesAttack.size(); k++){
//              for(int z; z < )
//         if((adjacentTerritories[i]->getOwner()->getName() != this->getName()) && (adjacentTerritories[i] != territoriesAttack[k])){
//            territoriesAttack.push_back(adjacentTerritories[i]);
//         }   
//         }
     
//      }
//     }
//      return territoriesAttack;
// }





vector<Territory*> Player::toAttack() {

    vector<Territory*> territoriesAttack;

    for (int j = 0; j < territoriesOwned.size(); j++)
    {
        vector<Territory*> adjacentTerritories = territoriesOwned[j]->getAdjacentTerritories();
        for (int i = 0; i < adjacentTerritories.size(); i++)
        { 
            if(!(adjacentTerritories[i]->getOwner()->getName() == this->getName()))
            {
                bool foundDuplicate = false;
                for(int k = 0; k < territoriesAttack.size(); k++)
                {
                    if(adjacentTerritories[i] == territoriesAttack[k])
                    {
                        foundDuplicate = true;
                        break;
                    }
                }
                if(!foundDuplicate)
                {
                    territoriesAttack.push_back(adjacentTerritories[i]);
                }
            }
        }
    }
    return territoriesAttack;
}

//Implementation of getPlayerTerritories() method
vector <Territory*> Player:: getPlayerTerritories(){
    return territoriesOwned;
}
   // create an OrderList object
   OrdersList* ol = new OrdersList();

void Player::issueOrder(Player* player)
{ 
//     bool addingOrders = true;
//     int choice = 0;

//     while (addingOrders) {

//         cout << "-- Orders --\n";
//         cout << "1. Advance\n";
//         cout << "2. Bomb\n";
//         cout << "3. Blockade\n";
//         cout << "4. Airlift\n";
//         cout << "5. Negotiate\n";
//         cout << "6. End Ordering Phase\n";

//          // Prompt the user for input
//         cout << "Enter a choice (1 - 6): ";

//         // Read input from the user
//         cin >> choice;

//         if (cin.fail()) {

//             cin.clear();
//             cin.ignore(numeric_limits<streamsize>::max(), '\n');
//             cout << "\nInvalid input: Please enter an integer (1-6)" << endl;
//         }


//         switch (choice) {

//             // Advance
//             case 1:

//                 // move form source to target (adj)



//                 break;
            
//             // Bomb
//             case 2:

//                 if (player->myHand->containsCardType("Bomb")) {

//                     // Display adjacent enemy territories
//                     player->toAttack();
                    
//                     cout << "Enter the integer of the territory you wish to Bomb: ";
//                     // validate input

//                     Bomb* bomb = new Bomb(/* enter territory to be bombed */);
//                     player->myOrders->vectorOfOrders.push_back(bomb);

//                 } else {
//                     cout << "Invalid Request: You do not have this card!";
//                     continue;
//                 }

//                 break;

//             // Blockade
//             case 3:

//                 if (player->myHand->containsCardType("Blockade")) {
                    
//                     // Display owned territories
//                     cout << "Enter the integer of the territory you wish to Blockade: ";
//                     // validate input

//                     Blockade* blockade = new Blockade(/* enter owned territory */);
//                     player->myOrders->vectorOfOrders.push_back(blockade);
                    

//                 } else {
//                     cout << "Invalid Request: You do not have this card!";
//                     continue;
//                 }

//                 break;

//             // Airlift
//             case 4:

//                 if (player->myHand->containsCardType("Airlift")) {

//                     // Display owned territories and armies in each

//                     cout << "Enter the integer of the territory you wish to Airlift: ";
//                     // validate input

//                     cout << "Enter the amount of units you wish to Airlift: ";
                    
//                     int unitAmount = 0;
//                     cin >> unitAmount;

//                     Airlift* airlift = new Airlift(/* source, target */);
//                     player->myOrders->vectorOfOrders.push_back(airlift);

//                 } else {
//                     cout << "Invalid Request: You do not have this card!";
//                     continue;
//                 }

//                 break;

//             // Negotiate
//             case 5:

//                 if (player->myHand->containsCardType("Diplomacy")) {

//                     // Display enemy players

//                     cout << "Enter the integer of the enemy player you wish to Negotiate with: ";
//                     // validate input

//                     Negotiate* negotiate = new Negotiate(/* target player */);
//                     player->myOrders->vectorOfOrders.push_back(negotiate);

//                 } else {
//                     cout << "Invalid Request: You do not have this card!";
//                     continue;
//                 }

//                 break;

//             // Exit
//             case 6:
//                 addingOrders = false;
//                 break;
//         }
//     }
 }
