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
class Territory;

//Territory class with getName() function 
class TerritoryPlayer 
{
    public:
        TerritoryPlayer(string territoryName) : name(territoryName) {}
        string getName() const { return name; }
        //insertion operator
        friend ostream& operator<<(ostream& output, TerritoryPlayer&  t);  
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
        Player(vector<TerritoryPlayer*> territoriesOwned, vector<TerritoryPlayer*> territoriesDefend, vector<TerritoryPlayer*> territoriesAttack, string name);
        //Copy Constructor passing parameter p
        Player(const Player& p); 
        //constructor for name
        Player(string name);
         //insertion operator
        friend ostream& operator<<(ostream& output, Player&);  
        //method named toDefend() that return a list of territories that are to be defend 
        vector<TerritoryPlayer*> toDefend() ;
        //method named toAttack() that returns a list of territories that are to be attacked 
        vector<TerritoryPlayer*> toAttack() ;
         //method named toAttack() that returns a list of territories that are to be attacked 
        vector<TerritoryPlayer*> owned() ;
        // //creating an order object called myOrders
        OrdersList* myOrders;
        //method named issueOrder() 
        void issueOrder(string orderType);
        //creating a hand of cards called myHand
        Hand* myHand;
        //getter and setter
         string getName();            
         void setName(string name);
         vector <Territory*> getPlayerTerritories();     
         void setPlayerTerritories(Territory* territory);   
         void addPlayerTerritories(Territory* territory);   
         int getArmy();            
         void setArmy(int army);
       

    private:
        vector <Territory*> territories; 
        vector<TerritoryPlayer*> territoriesOwned;
        vector<TerritoryPlayer*> territoriesDefend;
        vector<TerritoryPlayer*> territoriesAttack;
        int army;
        string name;

};
 #endif