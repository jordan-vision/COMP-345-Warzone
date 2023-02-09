#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include <iostream>
#include <string>
#include "Cards.h"
#include "Orders.h"

//Territory class with getName() function in order to take the name from the vector
class Territory {
public:
    Territory(std::string territoryName) : name(territoryName) {}
    std::string getName() const { return name; }

private:
    std::string name;
};


class Player
{
public: 
    //Default constructor - initialize the player
    Player();
    //Constructor that initializes the player's collection of territories, hand of cards, and the list of orders
    Player(std::vector<Territory*> territoriesDefend, std::vector<Territory*> territoriesAttack);
    //Copy Constructor passing parameter p
    Player(const Player& p);
    //method named toDefend() that return a list of territories that are to be defend - const so it cannot be modified
    std::vector<Territory*> toDefend() ;
    //method named toAttack() that returns a list of territories that are to be attacked  - const so it cannot be modified
    std::vector<Territory*> toAttack() ;
    //creating an order object called myOrders
    OrdersList* myOrders;
    //method named issueOrder() 
    void issueOrder(OrdersList* order);
    //creating a hand of cards called myHand
    Hand* myHand;
    

private:
    std::vector<Territory*> territoriesDefend;
    std::vector<Territory*> territoriesAttack;
    std::vector<OrdersList*> orders;
    
};
 #endif