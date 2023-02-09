#include "Player.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

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
  this->myOrders = new OrdersList();
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

//issurOrder() method
void Player::issueOrder()  
{
  // Deploy *newOrder = new Deploy;
  // Advance *newOrder = new Advance;
  // Bomb *newOrder = new Bomb;
  // Blockade *newOrder = new Blockade;
  // Airlift *newOrder = new Airlift;
  // Negotiate *newOrder = new Negotiate;
  myOrders->add(new Bomb());
}



