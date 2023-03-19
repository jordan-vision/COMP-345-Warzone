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
vector<Territory*> Player::toAttack() {
    vector<Territory*> territoriesAttack;

    for (int j = 0; j < territoriesOwned.size(); j++){
    vector<Territory*> adjacentTerritories = territoriesOwned[j]->getAdjacentTerritories();
    for (int i = 0; i < adjacentTerritories.size(); i++)
     {
        territoriesAttack.push_back(adjacentTerritories[i]);
     }
        return territoriesAttack;
    }
}

//Implementation of getPlayerTerritories() method
vector <Territory*> Player:: getPlayerTerritories(){
    return territoriesOwned;
}
   // create an OrderList object
   OrdersList* ol = new OrdersList();

void Player::issueOrder(string orderType)
{ 
   // checking the orderType and then printing the order
   if (orderType == "Deploy") {
      // create order 
      Deploy* d = new Deploy();
      cout<< "\n" <<orderType << " order has been issued:\n" << endl;
      cout << *d << endl;
      //add to order list
      ol->add(d);
   } else if (orderType == "Advance") {
     // create order 
     Advance* a = new Advance();
     cout<< orderType << " order has been issued:\n" << endl;
      cout << *a << endl;
      //add to order list
      ol->add(a);
   } else if (orderType == "Blockade") {
      // create order 
      Blockade* bl = new Blockade();
      cout<< orderType << " order has been issued:\n" << endl;
      cout << *bl << endl;
      //add to order list
      ol->add(bl);
   } else if (orderType == "Bomb") {
      // create order 
      Bomb* bo = new Bomb();
      cout<< orderType << " order has been issued:\n" << endl;
      cout << *bo << endl;
      //add to order list
      ol->add(bo);
   } else if (orderType == "Airlift") {
      // create order 
      Airlift* ar = new Airlift();
      cout<< orderType << " order has been issued:\n" << endl;
      cout << *ar << endl;
      //add to order list
      ol->add(ar);
   } else if (orderType == "Negotiate") {
      // create order 
      Negotiate* n = new Negotiate();
      cout<< orderType << " order has been issued:\n" << endl;
      cout << *n << endl;
      //add to order list
      ol->add(n);
   } else {
      cout << "Invalid order type" << endl;
   }
    cout << "\nOrders List: " << endl;
    cout << *ol << endl;
}
