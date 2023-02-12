#include "Player.h"
#include "Orders.h"
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
    delete myOrders;
};

//Constructor that initializes the player's collection of territories, hand of cards, and the list of orders
Player::Player(vector<Territory*> territoriesDefend, vector<Territory*> territoriesAttack)
: territoriesDefend(territoriesDefend), territoriesAttack(territoriesAttack)
 {
  this->territoriesDefend = territoriesDefend;
  this->territoriesAttack = territoriesAttack;
 }

//Copy Constructor passing parameter p
Player::Player(const Player& p)
{
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

//Implementation of the issueOrder() method
void Player::issueOrder(string orderType)
{
    if (orderType == "Deploy")
    {
        myOrders->add(new Deploy());
    }
    else if (orderType == "Advance")
    {
        myOrders->add(new Advance());
    }
    else if (orderType == "Bomb")
    {
        myOrders->add(new Bomb());
    }
    else if (orderType == "Blockade")
    {
        myOrders->add(new Blockade());
    }
    else if (orderType == "Airlift")
    {
        myOrders->add(new Airlift());
    }
    else if (orderType == "Negotiate")
    {
        myOrders->add(new Negotiate());
    }
    else
    {
        cout << "Invalid order type!" << endl;
    }
    
        cout << "\nIssued orders: " << endl;

}
