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
    for (TerritoryPlayer* td : territoriesDefend) 
        delete td;    
    for (TerritoryPlayer* ta : territoriesAttack) 
        delete ta; 
   for (TerritoryPlayer* to : territoriesOwned) 
        delete to;
   
    // delete myOrders;
    
    delete myHand;
   
};

//Constructor that initializes the player's collection of territories (owned, defend, attack) and the player name
Player::Player(vector<TerritoryPlayer*> territoriesOwned, vector<TerritoryPlayer*> territoriesDefend, vector<TerritoryPlayer*> territoriesAttack, string name)
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
vector <Territory*> Player:: getPlayerTerritories(){
    return territories;
}

void Player:: setPlayerTerritories(Territory* territory){
    this->territories.push_back(territory);
}
void Player:: addPlayerTerritories(Territory* territory){
    this->territories.push_back(territory);
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


//Implementation of the friend insertion operator for class Territory
ostream& operator<<(ostream& output, TerritoryPlayer& t) {
output << t.getName();
return output;
}

//Implementation of the friend insertion operator for class Player
ostream& operator<<(ostream& output, Player& p) {
    output << p.getName();
    return output;
}

//Implementation of the toDefend() method
vector<TerritoryPlayer*> Player::owned() {
vector<TerritoryPlayer*> territoriesOwned;
    territoriesOwned.push_back(new TerritoryPlayer("Territory 1"));
    territoriesOwned.push_back(new TerritoryPlayer("Territory 2"));
    territoriesOwned.push_back(new TerritoryPlayer("Territory 3"));
    territoriesOwned.push_back(new TerritoryPlayer("Territory 4"));

    cout << "\nTerritories owned: " << endl;
    for(auto &t : territoriesOwned) 
    {
        cout << *t << endl;
    }
    return territoriesOwned;

}
//Implementation of the toDefend() method
vector<TerritoryPlayer*> Player::toDefend() {
 vector<TerritoryPlayer*> territoriesDefend;
    territoriesDefend.push_back(new TerritoryPlayer("Quebec"));
    territoriesDefend.push_back(new TerritoryPlayer("Ontario"));
    territoriesDefend.push_back(new TerritoryPlayer("Alberta"));
    territoriesDefend.push_back(new TerritoryPlayer("Alaska"));


    cout << "\nTerritories to defend: " << endl;
    for(auto &t : territoriesDefend) 
    {
        cout << *t << endl;
    }
    return territoriesDefend;

}
//Implementation of the toAttack() method 
vector<TerritoryPlayer*> Player::toAttack() {
    vector<TerritoryPlayer*> territoriesAttack;
    territoriesAttack.push_back(new TerritoryPlayer("Mexico"));
    territoriesAttack.push_back(new TerritoryPlayer("Argentina"));
    territoriesAttack.push_back(new TerritoryPlayer("Brazil"));
    territoriesAttack.push_back(new TerritoryPlayer("Venezuela"));

    cout << "\nTerritories to attack: " << endl;
    for(auto &t : territoriesAttack) 
    {
        cout << *t << endl;
    }
        return territoriesAttack;

}

//    // create an OrderList object
//    OrdersList* ol = new OrdersList();

// void Player::issueOrder(string orderType)
// { 
//    // checking the orderType and then printing the order
//    if (orderType == "Deploy") {
//       // create order 
//       Deploy* d = new Deploy();
//       cout<< "\n" <<orderType << " order has been issued:\n" << endl;
//       cout << *d << endl;
//       //add to order list
//       ol->add(d);
//    } else if (orderType == "Advance") {
//      // create order 
//      Advance* a = new Advance();
//      cout<< orderType << " order has been issued:\n" << endl;
//       cout << *a << endl;
//       //add to order list
//       ol->add(a);
//    } else if (orderType == "Blockade") {
//       // create order 
//       Blockade* bl = new Blockade();
//       cout<< orderType << " order has been issued:\n" << endl;
//       cout << *bl << endl;
//       //add to order list
//       ol->add(bl);
//    } else if (orderType == "Bomb") {
//       // create order 
//       Bomb* bo = new Bomb();
//       cout<< orderType << " order has been issued:\n" << endl;
//       cout << *bo << endl;
//       //add to order list
//       ol->add(bo);
//    } else if (orderType == "Airlift") {
//       // create order 
//       Airlift* ar = new Airlift();
//       cout<< orderType << " order has been issued:\n" << endl;
//       cout << *ar << endl;
//       //add to order list
//       ol->add(ar);
//    } else if (orderType == "Negotiate") {
//       // create order 
//       Negotiate* n = new Negotiate();
//       cout<< orderType << " order has been issued:\n" << endl;
//       cout << *n << endl;
//       //add to order list
//       ol->add(n);
//    } else {
//       cout << "Invalid order type" << endl;
//    }
//     cout << "\nOrders List: " << endl;
//     cout << *ol << endl;
// }
