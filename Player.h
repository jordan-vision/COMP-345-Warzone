#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
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

//Territory class with getName() function 
class Territory 
{
    public:
        Territory(string territoryName) : name(territoryName) {}
        string getName() const { return name; }
        //insertion operator
        friend ostream& operator<<(ostream& output, Territory&  t);  
    private:
        string name;
};

class Player
{
    public: 
        //Default constructor - initialize the player
        Player();
        //Destructor
        ~Player();
        //Constructor that initializes the player's collection of territories
        Player(vector<Territory*> territoriesOwned, vector<Territory*> territoriesDefend, vector<Territory*> territoriesAttack);
        //Copy Constructor passing parameter p
        Player(const Player& p); 
         //insertion operator
        friend ostream& operator<<(ostream& output, Player&);  
        //method named toDefend() that return a list of territories that are to be defend 
        vector<Territory*> toDefend() ;
        //method named toAttack() that returns a list of territories that are to be attacked 
        vector<Territory*> toAttack() ;
         //method named toAttack() that returns a list of territories that are to be attacked 
        vector<Territory*> owned() ;
        //creating an order object called myOrders
        OrdersList* myOrders;
        //method named issueOrder() 
        void issueOrder(string orderType);
        //creating a hand of cards called myHand
        Hand* myHand;
       

    private:
        vector<Territory*> territoriesOwned;
        vector<Territory*> territoriesDefend;
        vector<Territory*> territoriesAttack;
        string name;

};
 #endif