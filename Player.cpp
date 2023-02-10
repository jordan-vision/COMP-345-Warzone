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

//Implementation of the toDefend() method
vector<Territory*> Player::toDefend() {
return territoriesDefend;
}

//Implementation of the toAttack() method
vector<Territory*> Player::toAttack() {
return territoriesAttack;
}

//Implementation of the friend insertion operator for class Territory
ostream& operator<<(ostream& output, Territory& t) {
output << t.getName();
return output;
}

//Implementation of the friend insertion operator for class Player
ostream& operator<<(ostream& output, Player& p) {
output << "Defend Territories: " << endl;
for (int i = 0; i < p.territoriesDefend.size(); i++) {
output << *p.territoriesDefend[i] << endl;
}
output << "Attack Territories: " << endl;
for (int i = 0; i < p.territoriesAttack.size(); i++) {
output << *p.territoriesAttack[i] << endl;
}
return output;
}

// //declaration of toDefend() method
// vector<Territory*> Player::toDefend() 
// {
// //defendList vector is being declared and initialized as empty. 
// vector<Territory*> defendList;
// //The loop iterates through territoriesDefend and every time it iterates, 
// //the name of the territory that the pointer is on gets added to the list
//   for (int i = 0; i < territoriesDefend.size(); i++)
//   {
//     defendList.push_back(territoriesDefend[i]);
//   }
//   return defendList;
// }

// //declaration of toAttack() method
// vector<Territory*> Player::toAttack() 
// {
// //attackList vector is being declared and initialized as empty. 
// vector<Territory*> attackList;
// //The loop iterates through territoriesAttack and every time it iterates, 
// //the name of the territory that the pointer is on gets added to the list
//   for (int i = 0; i < territoriesAttack.size(); i++)
//   {
//     attackList.push_back(territoriesAttack[i]);
//   }
//   return attackList;
// }

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
}
