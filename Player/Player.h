#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include <iostream>
#include <string>
#include "Cards.h"
#include "Orders.h"
#include "Orders.cpp"

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
    OrdersList* myOrders;

    //method named toDefend() that return a list of territories that are to be defend - const so it cannot be modified
    std::vector<Territory*> toDefend() ;
    //method named toAttack() that returns a list of territories that are to be attacked  - const so it cannot be modified
    std::vector<Territory*> toAttack() ;
    //method named issueOrder() that creates an Order object and puts it in the player’s list of orders (takes a vector of pointers)
    void issueOrder(OrdersList* order);
    //method named cards() that return a list of the hand of cards  - const so it cannot be modified
    std::vector<Hand*> handOfCards() ;

private:
    std::vector<Territory*> territoriesDefend;
    std::vector<Territory*> territoriesAttack;
    std::vector<OrdersList*> orders;
    std::vector<Hand*> cards;
};
 #endif