#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include "Cards.h"
#include "Orders.h"
#include "Map.h"
#include "PlayerStrategy.h"
#include <iostream>
#include <string>
using std:: endl;
using std:: cout; 
using std:: vector;
using std:: string; 
using std:: ostream;

//defining class
class OrdersList;
class Hand;
class Territory;
class PlayerStrategy;

class Player
{
    public: 
        //Default constructor - initialize the player
        Player();
        //Destructor
        ~Player();
        //Constructor that initializes the player's collection of territories
        Player(vector<Territory*> territoriesOwned, vector<Territory*> territoriesDefend, vector<Territory*> territoriesAttack, string name, bool deployOrdersIssued);
        //Copy Constructor passing parameter p
        Player(const Player& p); 
        //constructor for name
        Player(string name);
         //insertion operator
        friend ostream& operator<<(ostream& output, Player&);  
        //method named toDefend() that return a list of territories that are to be defend 
        vector<Territory*> toDefend(vector<Territory*> t);
        //method named toAttack() that returns a list of territories that are to be attacked 
        vector<Territory*> toAttack();
         //method named toAttack() that returns a list of territories that are to be attacked 
        void owned(Territory* t);   
        //method named toAttack() that returns the strongest country 
        Territory* getStrongestCountry(Player* player);
        //method to get player territories
        vector <Territory*> getPlayerTerritories();        
        //creating an order object called myOrderss
        OrdersList* myOrders;
        //method named issueOrder() 
        void issueOrder(vector <Player*> player, int index);
        //creating a hand of cards called myHand
        Hand* myHand;
        //army
         int getArmy();            
         void setArmy(int army);
        //name
         string getName();            
         void setName(string name);
        //deployOrdersIssued
        bool getFlag();
        void setFlag(bool deployOrdersIssued);
        // Player's Hand manipulation functions
        void removeCardOfTypeFromHand(Player* player, CardType cardType);
        void removeCardFromHand(Card* cardToRemove);
       
        Territory* getValidTarget(vector<Territory*>& tToAttack); //validate target inputted by user
        Territory* getValidTerritory(vector<Territory*>& territory, string msg, int orderCase);//validate territory inputted by user
        Player* getValidPlayer(vector<Player*>players, int index); // validates the player inputted by user
        PlayerStrategy* ps;
        string* playerType;
        void setStrategy(PlayerStrategy* ps);
        PlayerStrategy* getStrategy();

    private:
        vector <Territory*> territories; 
        vector<Territory*> territoriesOwned;
        vector<Territory*> territoriesDefend;
        vector<Territory*> territoriesAttack;
        int army;
        bool deployOrdersIssued;
        string name;
        int reinforcements;

};
 #endif