#include "Player.h"
#include "Orders.h"
#include "Cards.h"
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

//Constructor that initializes the player's collection of territories, hand of cards, and the list of orders
Player::Player(vector<Territory*> territoriesOwned, vector<Territory*> territoriesDefend, vector<Territory*> territoriesAttack)
: territoriesOwned(territoriesOwned), territoriesDefend(territoriesDefend), territoriesAttack(territoriesAttack)
 {
  this->territoriesOwned = territoriesOwned;
  this->territoriesDefend = territoriesDefend;
  this->territoriesAttack = territoriesAttack;
 }

//Copy Constructor passing parameter p
Player::Player(const Player& p)
{
  this->territoriesOwned = territoriesOwned;
  this->territoriesDefend = p.territoriesDefend;
  this->territoriesAttack = p.territoriesAttack;
}

//Implementation of the friend insertion operator for class Territory
ostream& operator<<(ostream& output, Territory& t) {
output << t.getName();
return output;
}

//Implementation of the friend insertion operator for class Player
ostream& operator<<(ostream& output, Player& p) {

    return output;
}

//Implementation of the toDefend() method
vector<Territory*> Player::owned() {
vector<Territory*> territoriesOwned;
   territoriesDefend.push_back(new Territory("Territory 1"));
    territoriesDefend.push_back(new Territory("Territory 2"));
    territoriesDefend.push_back(new Territory("Territory 3"));
    territoriesDefend.push_back(new Territory("Territory 4"));

    cout << "\nTerritories owned: " << endl;
    for(auto &t : territoriesOwned) 
    {
        cout << *t << endl;
    }
    return territoriesOwned;

}
//Implementation of the toDefend() method
vector<Territory*> Player::toDefend() {
 vector<Territory*> territoriesDefend;
    territoriesDefend.push_back(new Territory("Quebec"));
    territoriesDefend.push_back(new Territory("Ontario"));
    territoriesDefend.push_back(new Territory("Alberta"));
    territoriesDefend.push_back(new Territory("Alaska"));


    cout << "\nTerritories to defend: " << endl;
    for(auto &t : territoriesDefend) 
    {
        cout << *t << endl;
    }
    return territoriesDefend;

}
//Implementation of the toAttack() method 
vector<Territory*> Player::toAttack() {
    vector<Territory*> territoriesAttack;
    territoriesAttack.push_back(new Territory("Mexico"));
    territoriesAttack.push_back(new Territory("Argentina"));
    territoriesAttack.push_back(new Territory("Brazil"));
    territoriesAttack.push_back(new Territory("Venezuela"));

    cout << "\nTerritories to attack: " << endl;
    for(auto &t : territoriesAttack) 
    {
        cout << *t << endl;
    }
        return territoriesAttack;

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
