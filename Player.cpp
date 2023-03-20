#include "Player.h"
#include "Orders.h"
#include "Cards.h"
#include "Map.h"
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
   for (Territory* to : territoriesOwned) 
        delete to;
   
    delete myOrders;
    delete myHand;
   
};

//Constructor that initializes the player's collection of territories (owned, defend, attack) and the player name
Player::Player(vector<Territory*> territoriesOwned, vector<Territory*> territoriesDefend, vector<Territory*> territoriesAttack, string name)
: territoriesOwned(territoriesOwned), territoriesDefend(territoriesDefend), territoriesAttack(territoriesAttack)
 {
  this->myHand = new Hand();
  this->name = name;
  this->territoriesOwned = territoriesOwned;
  this->territoriesDefend = territoriesDefend;
  this->territoriesAttack = territoriesAttack;
 }

//Constructor that initializes the player's name
 Player::Player(string name)
: name(name)
{
    this->name = name;
}
string Player:: getName(){
    return name; 
}

void Player:: setName(string name){
    this->name = name; 
}
int Player:: getArmy(){
    return army; 
}

void Player:: setArmy(int army){
    this->army = army; 
}

//Copy Constructor passing parameter p
Player::Player(const Player& p)
{
  this->myHand = p.myHand;
  this->name = p.name;
  this->territoriesOwned = p.territoriesOwned;
  this->territoriesDefend = p.territoriesDefend;
  this->territoriesAttack = p.territoriesAttack;
}

//Implementation of the friend insertion operator for class Player
ostream& operator<<(ostream& output, Player& p) {
    output << p.getName();
    return output;
}

//Implementation of the owned() method
void Player::owned(Territory* t) {
    vector<Territory*> territoriesOwned;
    this->territoriesOwned.push_back(t);
    
}

//Implementation of the toDefend() method
vector<Territory*> Player::toDefend(vector<Territory*> t) {
    vector<Territory*> territoriesDefend;

    for (int i = 0; i < t.size(); i++){
        if (t[i]->getOwner() == nullptr || t[i]->getOwner()->getName() == this->getName()){
        territoriesDefend.push_back(t[i]);
        }
    }
    return territoriesDefend;  
}

// returns a list of territories that can be attecked by the player i.e. adjacent territories
vector<Territory*> Player::toAttack() {

    vector<Territory*> territoriesAttack;

    for (int j = 0; j < territoriesOwned.size(); j++)
    {
        vector<Territory*> adjacentTerritories = territoriesOwned[j]->getAdjacentTerritories();
        for (int i = 0; i < adjacentTerritories.size(); i++)
        { 
            if(!(adjacentTerritories[i]->getOwner()->getName() == this->getName()))
            {
                bool foundDuplicate = false;
                for(int k = 0; k < territoriesAttack.size(); k++)
                {
                    if(adjacentTerritories[i] == territoriesAttack[k])
                    {
                        foundDuplicate = true;
                        break;
                    }
                }
                if(!foundDuplicate)
                {
                    territoriesAttack.push_back(adjacentTerritories[i]);
                }
            }
        }
    }
    return territoriesAttack;
}

//Implementation of getPlayerTerritories() method
vector <Territory*> Player:: getPlayerTerritories(){
    return territoriesOwned;
}
   // create an OrderList object
   OrdersList* ol = new OrdersList();


void Player::issueOrder(vector<Player*> player, int index)
{ 
    cout<<player[index]->myOrders->vectorOfOrders.size() <<endl;
    bool addingOrders = true;
    int choice = 0;

    vector<Territory*> tToAttack = player[index]->toAttack(); //get list of territories to be attacked
    vector<Territory*> tToDefend = player[index]->toDefend(player[index]->getPlayerTerritories()); //get list of territories to be defended

    //  (2) a player will only issue deploy orders and no other kind of orders if they still have armies in their reinforcement pool;
    if (player[index]->getArmy()!=0){ 
        Deploy* deploy = new Deploy(getValidTarget(tToDefend));
        cout<<"Created Deploy Order"<<endl;
        deploy->orderEffect = "order deployed";
        player[index]->myOrders->add(deploy);// add deploy order to orderslist
    }
    
    while (addingOrders) { // (4) a player can play cards to issue orders;

        cout << "\n-- Orders --\n";
        cout << "1. Advance\n";
        cout << "2. Bomb\n";
        cout << "3. Blockade\n";
        cout << "4. Airlift\n";
        cout << "5. Negotiate\n";
        cout << "6. End Ordering Phase\n";

         // Prompt the user for input
        cout << "Enter a choice (1 - 6): ";

        // Read input from the user
        cin >> choice;

        if (cin.fail()) {

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nInvalid input: Please enter an integer (1-6)" << endl;
        }


        switch (choice) {

            // Advance
            // (3) a player can issue advance orders to either defend or attack, based on the toAttack() and toDefend() lists;
            case 1: // Advance


                break;
            
            // Bomb
            case 2:

                if (player[index]->myHand->containsCardType("Bomb")) {
                        
                    cout << "Enter the integer of the territory you wish to Bomb: "<<endl;
                    // validate input
                    Bomb* bomb = new Bomb(getValidTarget(tToAttack));
                    player[index]->myOrders->vectorOfOrders.push_back(bomb); // add bomb order to orderslist
                    
                 } 
            else {
                    cout << "Invalid Request: You do not have this card! Try again"<<endl;
                    continue;
                }

                break;

            // Blockade
            case 3:

                if (player[index]->myHand->containsCardType("Blockade")) {
                    // validate input
                    Blockade* blockade = new Blockade(getValidTerritory(tToDefend, "\nPlease select the territory you would like to Blockade:"));
                    player[index]->myOrders->vectorOfOrders.push_back(blockade); // add blockade order to orderslist
                    

                } else {
                    cout << "Invalid Request: You do not have this card!"<<endl;
                    continue;
                }

                break;

            // Airlift
            case 4:

                if (player[index]->myHand->containsCardType("Airlift")) {

                    Territory* source = getValidTerritory(tToDefend, "Please select the territory you would like to Airlift from:");
                    Territory* target = getValidTerritory(tToDefend, "Please select the territory you would like to Airlift to:");

                    int maxUnitAmount = source->getArmy();
                    cout << "Enter the amount of units you wish to Airlift (territory " << source->getName()<< " currently has "<< maxUnitAmount << " armies (units)):";
                    int unitAmount = 0;
                    cin >> unitAmount;
                    while (unitAmount<1 || unitAmount > maxUnitAmount){ // get valid unit amount
                        cout << "invalid units amount. Please enter a value higher than 0 and lower than " << maxUnitAmount<< endl;
                        cin >> unitAmount;
                    }
                    
                    Airlift* airlift = new Airlift(source, target, unitAmount);
                    player[index]->myOrders->vectorOfOrders.push_back(airlift); // add airlift order to orderslist

                } else {
                    cout << "Invalid Request: You do not have this card!";
                    continue;
                }

                break;

            // Negotiate
            case 5:

                if (player[index]->myHand->containsCardType("Diplomacy")) {

                    Negotiate* negotiate = new Negotiate(getValidPlayer(player, index));
                    player[index]->myOrders->vectorOfOrders.push_back(negotiate); //add new negotiate order to the orderslist

                } else {
                    cout << "Invalid Request: You do not have this card!";
                    continue;
                }

                break;

            //Exit
            case 6:
                addingOrders = false;
                break;
        }
    
 }
}


// checks if the user is trying to attack a valid territory i.e. if the entered integer corresponds to a territory id present in the vector returned by toAttack()
Territory* Player::getValidTarget(vector<Territory*>& tToAttack) { 
    cout << "\nThis is the list of available territories to attack:" << endl; // display available territories to attack
    for (auto t : tToAttack) {
        cout << t->getName() << " (" << t->getTerritoryID() << ")\n";
    }
    cout << "\nPlease select the territory you would like to attack:" << endl;
    int territoryId;
    bool validId = false;
    Territory* target = nullptr;
    while (!validId) {
        if (!(cin >> territoryId) || cin.peek() != '\n') {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter an integer.\n";
        } else { // get valid territory
            for (auto t : tToAttack) {
                if (t->getTerritoryID() == territoryId) {
                    validId = true;
                    target = t;
                    break;
                }
            }
            if (!validId) {
                cout << "Invalid territory ID. Please enter a valid ID.\n";
            }
        }
    }
    return target; //return a valid territory to attack
}

Territory* Player::getValidTerritory(vector<Territory*>& territory, string descriptiveMsg) {
    cout << "\nThis is the list of available territories:" << endl; //display the territories that can be defended
    for (auto t : territory) {
        cout << t->getName() << " (" << t->getTerritoryID() << ")\n";
    }
    cout << descriptiveMsg << endl;
    int territoryId;
    bool validId = false;
    Territory* target = nullptr;
    while (!validId) {
        if (!(cin >> territoryId) || cin.peek() != '\n') {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter an integer.\n";
        } else {
            for (auto t : territory) { // get valid territory
                if (t->getTerritoryID() == territoryId) {
                    validId = true;
                    target = t;
                    break;
                }
            }
            if (!validId) {
                cout << "Invalid territory ID. Please enter a valid ID.\n";
            }
        }
    }
    return target; //return a valid territory to be defended
}

//get valid player from this game
Player* Player::getValidPlayer(vector<Player*>players, int index){
    cout << "Here are all the players currently in the game: " << endl;
    for (auto player : players) {
        if (player != this) {
            cout << player->getName() << endl; //get valid players name
        }
    }

    string playerName;
    bool validName = false;
    Player* validPlayer = nullptr;
    while (!validName) {
        cout << "Please enter the name of the player you wish to select: ";
        if (!(cin >> playerName)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a valid player name." << endl;
        } else {
            transform(playerName.begin(), playerName.end(), playerName.begin(), ::tolower);
            for (auto p : players) {
                string name = p->getName(); //find the players name
                transform(name.begin(), name.end(), name.begin(), ::tolower);
                if (name == playerName && p != this) {
                    validName = true;
                    validPlayer = p;
                    break;
                }
            }
            if (!validName) {
                cout << "Invalid player name. Please enter a valid name." << endl;
            }
        }
    }
    return validPlayer;
}