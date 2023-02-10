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


//declaration of toDefend() method
vector<Territory*> Player::toDefend() 
{
//defendList vector is being declared and initialized as empty. 
vector<Territory*> defendList;
//The loop iterates through territoriesDefend and every time it iterates, 
//the name of the territory that the pointer is on gets added to the list
  for (int i = 0; i < territoriesDefend.size(); i++)
  {
    defendList.push_back(territoriesDefend[i]);
  }
  return defendList;
}

//declaration of toAttack() method
vector<Territory*> Player::toAttack() 
{
//attackList vector is being declared and initialized as empty. 
vector<Territory*> attackList;
//The loop iterates through territoriesAttack and every time it iterates, 
//the name of the territory that the pointer is on gets added to the list
  for (int i = 0; i < territoriesAttack.size(); i++)
  {
    attackList.push_back(territoriesAttack[i]);
  }
  return attackList;
}

void Player::issueOrder(string orderType)
{
int orderCount = 0; // Keep track of the number of orders
    if (orderType == "Deploy")
{
    Deploy deploy;
    myOrders->add(&deploy);
    ++orderCount;
}
else if (orderType == "Advance")
{
    Advance advance;
    myOrders->add(&advance);
    ++orderCount;
}
else if (orderType == "Bomb")
{
    Bomb bomb;
    myOrders->add(&bomb);
    ++orderCount;
}
else if (orderType == "Blockade")
{
    Blockade blockade;
    myOrders->add(&blockade);
    ++orderCount;
}
else if (orderType == "Airlift")
{
    Airlift airlift;
    myOrders->add(&airlift);
    ++orderCount;
}
else if (orderType == "Negotiate")
{
    Negotiate negotiate;
    myOrders->add(&negotiate);
    ++orderCount;
}
else
{
    cout << "Invalid order type" << endl;
    return;
}

// Print the type of the order that was just added
cout << "Order type: " << orderType << endl;

}



