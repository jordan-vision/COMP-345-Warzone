#include "Player.h"
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
Player::Player(vector<Territory*> territoriesOwned, vector<Territory*> territoriesDefend, vector<Territory*> territoriesAttack, string name, bool deployOrdersIssued)
: territoriesOwned(territoriesOwned), territoriesDefend(territoriesDefend), territoriesAttack(territoriesAttack), deployOrdersIssued(false)
 {
  this->myHand = new Hand();
  this->name = name;
  this->territoriesOwned = territoriesOwned;
  this->territoriesDefend = territoriesDefend;
  this->territoriesAttack = territoriesAttack;
  this->deployOrdersIssued = deployOrdersIssued;
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

bool Player:: getFlag(){
    return deployOrdersIssued; 
}

void Player::setFlag(bool deployOrdersIssued){
    this->deployOrdersIssued = deployOrdersIssued;
}

void Player::removeCardOfTypeFromHand(Player* player, CardType cardType) {
    // Find the first card in the hand that matches the specified CardType
    auto it = find_if(player->myHand->handCards.begin(), player->myHand->handCards.end(), 
                      [&](Card* card) { return *card->getCardType() == cardType; });

    // If a card of the specified type was found, remove it from the hand
    if (it != player->myHand->handCards.end()) {
        cout<<"card found in players hand"<<endl;
        player->removeCardFromHand(*it);
    }
}

void Player::removeCardFromHand(Card* cardToRemove) {
    auto& handCards = myHand->handCards; // reference to vector of hand cards
    handCards.erase(remove(handCards.begin(), handCards.end(), cardToRemove), handCards.end()); // remove card from vector
    cout<<"card deleted from players hand"<<endl;
    delete cardToRemove; // delete card from heap

//     auto element = find(player->myHand->handCards.begin(), player->myHand->handCards.end(), this);  // Finds element
//     int elementIndex = distance(player->myHand->handCards.begin(), element);                        // Gets element index
//     mainDeck->deckCards.push_back(move(this));  // Moves card pointer back to deck
//     player->myHand->handCards.erase(element);   // Erases card pointer from hand
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
    int numberOfArmies = player[index]->getArmy();
    bool deployOrdersIssued = player[index]->getFlag();

    vector<Territory*> tToAttack = player[index]->toAttack(); //get list of territories to be attacked
    vector<Territory*> tToDefend = player[index]->toDefend(player[index]->getPlayerTerritories()); //get list of territories to be defended
    
    while (addingOrders) { // (4) a player can play cards to issue orders;
        if (numberOfArmies!=0 && !deployOrdersIssued){ //  (2) a player will only issue deploy orders and no other kind of orders if they still have armies in their reinforcement pool;
            Territory* selectedTarget = getValidTarget(tToDefend);
            int reinforcementAmount = 0;
            while (true) {
                cout << "\nPlayer " << player[index]->getName() << "'s turn: " << endl;
                cout << "How many reinforcements do you wish to send ( 1 - " << numberOfArmies << " )?";

                if (!(cin >> reinforcementAmount)) {

                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input: Please try again!" << endl;

                } else if (reinforcementAmount < 1 || reinforcementAmount > numberOfArmies) 
                    cout << "Invalid Input: Please try again!" << endl;
                else 
                    
                    break;
            } // end of while loop
            numberOfArmies = numberOfArmies - reinforcementAmount;

            
            
            Deploy* deploy = new Deploy(selectedTarget, reinforcementAmount);
            
            cout<<"Created Deploy Order"<<endl;
            deploy->orderEffect = "order deployed";
            player[index]->myOrders->add(deploy);// add deploy order to orderslist
            if (numberOfArmies==0){
                deployOrdersIssued = true;
                player[index]->setFlag(deployOrdersIssued);
                addingOrders = false;
                break;
            }
        }
        else{
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

<<<<<<< Updated upstream
                player[index]->setFlag(false);
=======
                if (player[index]->myHand->containsCardType("Advance")) {

                    Territory* src = getValidTerritory(tToDefend, "Please select the territory you would like to Advance from:");
                    Territory* tgt = getValidTerritory(tToAttack, "Please select the territory you would like to Advance to:");

                    int units = src->getArmy();
                    cout << "Enter the amount of units you wish to Advance (territory " << src->getName()<< " currently has "<< units << " armies (units)):";
                    int unitUser = 0;
                    cin >> unitUser;
                    while (unitUser<1 || unitUser > units){ // get valid unit amount
                        cout << "invalid units amount. Please enter a value higher than 0 and lower than " << units<< endl;
                        cin >> unitUser;
                    }
                    
                    Advance* advance = new Advance(tgt, src, unitUser);
                    player[index]->myOrders->vectorOfOrders.push_back(advance); // add airlift order to orderslist

                } else {
                    cout << "Invalid Request: You do not have this card!";
                    continue;
                }


>>>>>>> Stashed changes
                break;
            
            // Bomb
            case 2:

                if (player[index]->myHand->containsCardType("Bomb")) {
                        
                    cout << "Enter the integer of the territory you wish to Bomb: "<<endl;
                    // validate input
                    Bomb* bomb = new Bomb(getValidTarget(tToAttack));
                    player[index]->myOrders->add(bomb); // add bomb order to orderslist
                    
                 } 
            else {
                    cout << "Invalid Request: You do not have this card! Try again"<<endl;
                    continue;
                }
                player[index]->setFlag(false);
                break;

            // Blockade
            case 3:

                if (player[index]->myHand->containsCardType("Blockade")) {
                    // validate input
                    Blockade* blockade = new Blockade(getValidTerritory(tToDefend, "\nPlease select the territory you would like to Blockade:",0));
                    player[index]->myOrders->add(blockade); // add blockade order to orderslist
                    

                } else {
                    cout << "Invalid Request: You do not have this card!"<<endl;
                    continue;
                }
                player[index]->setFlag(false);
                break;

            // Airlift
            case 4:

                if (player[index]->myHand->containsCardType("Airlift")) {

                    Territory* source = getValidTerritory(tToDefend, "Please select the territory you would like to Airlift from:", 4);
                    Territory* target = getValidTerritory(tToDefend, "Please select the territory you would like to Airlift to:", 0);

                    int maxUnitAmount = source->getArmy();
                    cout << "Enter the amount of units you wish to Airlift (territory " << source->getName()<< " currently has "<< maxUnitAmount << " armies (units)):";
                    int unitAmount = 0;
                    cin >> unitAmount;
                    cout<< "max unit amount is " << maxUnitAmount << " and the entered unit amount is " << unitAmount<<endl;
                    if (maxUnitAmount == 0){
                        cout << "There are no armies to Airlift" << endl;
                    }
                    else {
                    while (unitAmount<=0 || unitAmount > maxUnitAmount){ // get valid unit amount
                        cout << "invalid units amount. Please enter a value higher than 0 and lower than " << maxUnitAmount<< endl;
                        cin >> unitAmount;
                    }
                    }
                    
                    Airlift* airlift = new Airlift(source, target, unitAmount);
                    player[index]->myOrders->add(airlift); // add airlift order to orderslist

                } else {
                    cout << "Invalid Request: You do not have this card!";
                    continue;
                }
                player[index]->setFlag(false);
                break;

            // Negotiate
            case 5:

                if (player[index]->myHand->containsCardType("Diplomacy")) {

                    Negotiate* negotiate = new Negotiate(getValidPlayer(player, index));
                    player[index]->myOrders->add(negotiate); //add new negotiate order to the orderslist

                } else {
                    cout << "Invalid Request: You do not have this card!";
                    continue;
                }
                player[index]->setFlag(false);
                break;

            //Exit
            case 6:
                addingOrders = false;
                player[index]->setFlag(false);
                break;
        }
    }
 }
}


// checks if the user is trying to attack a valid territory i.e. if the entered integer corresponds to a territory id present in the vector returned by toAttack()
Territory* Player::getValidTarget(vector<Territory*>& tToAttack) { 
    cout << "\nThis is the list of available territories to you:" << endl; // display available territories to attack
    for (auto t : tToAttack) {
        cout << t->getName() << " (" << t->getTerritoryID() << ")\n";
    }
    cout << "\nPlease select the territory you would like to attack/deploy to:" << endl;
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

Territory* Player::getValidTerritory(vector<Territory*>& territory, string descriptiveMsg, int orderCase) {
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
                    if(orderCase != 4){
                        validId = true;
                        target = t;
                        break;
                    }
                    else{
                        if(t->getArmy()!=0){
                            validId = true;
                            target = t;
                            break;
                        }
                        cout << "There are no armies to Airlift!" << endl;
                    }

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