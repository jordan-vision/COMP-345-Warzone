#include "Player.h"
#include <iostream>
#include <vector>
#include <string>

//Default constructor - initialize the player
Player::Player() 
{

}

//Constructor that initializes the player's collection of territories, hand of cards, and the list of orders
Player::Player(std::vector<Territory*> territoriesDefend, std::vector<Territory*> territoriesAttack)
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
std::vector<Territory*> Player::toDefend() 
{
//defendList vector is being declared and initialized as empty. 
std::vector<Territory*> defendList;
//The loop iterates through territoriesDefend and every time it iterates, 
//the name of the territory that the pointer is on gets added to the list
for (int i = 0; i < territoriesDefend.size(); i++)
{
  defendList.push_back(territoriesDefend[i]);
}
return defendList;
}

//declaration of toAttack() method
std::vector<Territory*> Player::toAttack() 
{
//attackList vector is being declared and initialized as empty. 
std::vector<Territory*> attackList;
//The loop iterates through territoriesAttack and every time it iterates, 
//the name of the territory that the pointer is on gets added to the list
for (int i = 0; i < territoriesAttack.size(); i++)
{
  attackList.push_back(territoriesAttack[i]);
}
return attackList;
}

void Player::issueOrder(OrdersList* order)
{
std::vector<OrdersList*> orderList;
for (int i = 0; i < orders.size(); i++)
{
  orderList.push_back(orders[i]);
}
orderList.push_back(order);
this->orders = orderList;
}

//declaration of handOfCards() method
std::vector<Hand*> Player::handOfCards()
{
std::vector<Hand*> cardList;
//The loop iterates through cards and every time it iterates, 
//the name of the card that the Hand pointer is on gets added to the list
for (int i = 0; i < cards.size(); i++)
{
  cardList.push_back(cards[i]);
}
return cards;
}
