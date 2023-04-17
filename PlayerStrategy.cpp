#include "PlayerStrategy.h"



ostream& operator<<(ostream& output, PlayerStrategy& ps) {
    output << ps.getName();
    return output;
}

// PlayerStrategy:: PlayerStrategy(const PlayerStrategy& copy){
//     this->p = copy.p; 
// }

// PlayerStrategy& PlayerStrategy:: operator =(const PlayerStrategy& rhs){
//     this->p = rhs.p;
//     return *this;
// }


string PlayerStrategy:: getName(){
    return name; 
}

void PlayerStrategy:: setName(string name){
    this->name = name; 
}

PlayerStrategy:: ~PlayerStrategy(){
    delete p;
}




/************** HUMAN PLAYER STRATEGY **************/

HumanPlayerStrategy::HumanPlayerStrategy(Player* player) {

    this->p = player;
    // set player type to human
};


ostream& operator<<(ostream& output, HumanPlayerStrategy& ps) {
    output << ps.getName();
    return output;
}

HumanPlayerStrategy:: ~HumanPlayerStrategy(){
    delete p;
}

HumanPlayerStrategy:: HumanPlayerStrategy(const HumanPlayerStrategy& copy){
    this->p = copy.p; 
}

HumanPlayerStrategy& HumanPlayerStrategy:: operator =(const HumanPlayerStrategy& rhs){
    this->p = rhs.p;
    return *this;
}

void HumanPlayerStrategy::issueOrder(vector<Player*> players) {
    int index = 0;
for (int i = 0; i < players.size(); i++){
    if (players[i] == p){
        index = i;
    }
}
p->issueOrder(players, index);

};

vector<Territory*> HumanPlayerStrategy::toAttack() {


};

vector<Territory*> HumanPlayerStrategy::toDefend() {


};

/*************** AGGRESSIVE PLAYER STRATEGY ***************/


AggressivePlayerStrategy::AggressivePlayerStrategy(Player* player) {

    this->p = player;
    // set player type to aggressive

};


ostream& operator<<(ostream& output, AggressivePlayerStrategy& ps) {
    output << ps.getName();
    return output;
}

AggressivePlayerStrategy:: AggressivePlayerStrategy(const AggressivePlayerStrategy& copy){
    this->p = copy.p; 
}

AggressivePlayerStrategy& AggressivePlayerStrategy:: operator =(const AggressivePlayerStrategy& rhs){
    this->p = rhs.p;
    return *this;
}

AggressivePlayerStrategy:: ~AggressivePlayerStrategy(){
    delete p;
}

void AggressivePlayerStrategy::issueOrder(vector<Player*> players) {

cout << "\n-- Aggressive player issuing order --" << endl;
// cout << p->getName() << endl;
Territory* strongestTerritory = p->getStrongestCountry(p);
int numberOfArmies = p->getArmy();
cout << "Player has " << p->getArmy() << " armies to deploy." <<endl;
// cout << p->getPlayerTerritories()[0] << endl;

        if (strongestTerritory != nullptr) 
        {
            cout << "Strongest territory: " << *strongestTerritory << endl;
            
             if ( p->getArmy() !=0 ){ 
            Deploy* deploy = new Deploy(strongestTerritory, numberOfArmies);
            cout<<"\nCreated Deploy Order\n"<<endl;
            int currentArmy = strongestTerritory->getArmy();
            strongestTerritory->setArmy(numberOfArmies + currentArmy);
            cout << *strongestTerritory << " now has " << strongestTerritory->getArmy() << " armies." <<endl;
            // deploy->orderEffect = "order deployed";
            p->myOrders->add(deploy);// add deploy order to orderslist
             }
            vector<Territory*> strongestAdjacentTerritories = strongestTerritory->getAdjacentTerritories();
            cout << *strongestTerritory << " has: " << strongestAdjacentTerritories.size() << " adjacent territories." <<endl; 
            Territory* targetTerritory = strongestAdjacentTerritories[0];
             cout << "Target territory: " << targetTerritory->getName() << "\n" << endl;
             Advance* advanceOrder = new Advance(targetTerritory, strongestTerritory, strongestTerritory->getArmy());
            cout<<"Created Advance Order"<<endl;
             advanceOrder->execute(p);

             
         
        } else
        {
            if ( p->getArmy() !=0 ){ 
            Deploy* deploy = new Deploy( p->getPlayerTerritories()[0], numberOfArmies);
            p->getPlayerTerritories()[0]->setArmy(numberOfArmies);
            cout<<"Created Deploy Order"<<endl;
            cout << "All armies have been deployed to " << p->getPlayerTerritories()[0]->getName() << " which has now become the strongest territory. " << p->getPlayerTerritories()[0]->getName()  << " now has " << p->getPlayerTerritories()[0]->getArmy() << " armies\n" <<endl;
            // deploy->orderEffect = "order deployed";
             p->myOrders->add(deploy);// add deploy order to orderslist
            }
            cout << "\nThe target territory which " << p->getName() << " will attempt to attack is: " << p->getPlayerTerritories()[0]->getAdjacentTerritories()[0]->getName() << endl;
            Territory* targetTerritory =  p->getPlayerTerritories()[0]->getAdjacentTerritories()[0];
            Advance* advanceOrder = new Advance(targetTerritory, p->getPlayerTerritories()[0], p->getPlayerTerritories()[0]->getArmy());
            cout<<"Created Advance Order"<<endl;
            advanceOrder->execute(p);
        }
    }


vector<Territory*> AggressivePlayerStrategy::toAttack() {

Territory* strongestTerritory = p->getStrongestCountry(p);

vector<Territory*> strongestAdjacentTerritoriesAttack = strongestTerritory->getOwner()->toAttack();

return strongestAdjacentTerritoriesAttack;

};

vector<Territory*> AggressivePlayerStrategy::toDefend() {

p->toDefend(p->getPlayerTerritories());

};


// /************* BENEVOLENT PLAYER STRATEGY *************/

BenevolentPlayerStrategy::BenevolentPlayerStrategy(Player* player) {

    this->p = player;
    // set player type to benevolent
};

BenevolentPlayerStrategy:: BenevolentPlayerStrategy(const BenevolentPlayerStrategy& copy){
    this->p = copy.p; 
}

ostream& operator<<(ostream& output, BenevolentPlayerStrategy& ps) {
    output << ps.getName();
    return output;
}

BenevolentPlayerStrategy& BenevolentPlayerStrategy:: operator =(const BenevolentPlayerStrategy& rhs){
    this->p = rhs.p;
    return *this;
}

BenevolentPlayerStrategy:: ~BenevolentPlayerStrategy(){
    delete p;
}

void BenevolentPlayerStrategy::issueOrder(vector<Player*> players) {
cout << "\n-- Benevolent player issuing order --" << endl;
// cout << p->getName() << endl;
Territory* weakestTerritory = p->getWeakestCountry(p);
int numberOfArmies = p->getArmy();
cout << "Player has " << p->getArmy() << " armies to deploy." <<endl;
// deploy all player's armies to the first territory in the list
int highestArmyCount =0;

            if (weakestTerritory != nullptr){
                Deploy* deploy = new Deploy(weakestTerritory, numberOfArmies);
                int currentArmy = weakestTerritory->getArmy();
                weakestTerritory->setArmy(numberOfArmies + currentArmy);
                cout << "Current weakest territory is " << *weakestTerritory << endl;
                cout << *weakestTerritory << " now has " << weakestTerritory->getArmy() << " armies" <<endl;
                cout<<"\nCreated Deploy Order"<<endl;
                // deploy->orderEffect = "order deployed";
                p->myOrders->add(deploy);// add deploy order to orderslist

                weakestTerritory = p->getWeakestCountry(p); // get weakest territory again after deploying armies
                cout << "New weakest territory is " << *weakestTerritory << endl;
                vector<Territory*> weakestAdjacentTerritories = weakestTerritory->getAdjacentTerritories();
                cout << "Number of weakest territory's adjacent territories: " << weakestAdjacentTerritories.size() << endl;
                vector<Territory*> sourceTerritories;
                Territory* sourceTerritory;

                for (int i=0; i< weakestAdjacentTerritories.size(); i++ ){
                    if (weakestAdjacentTerritories[i]->getArmy() != 0){
                        sourceTerritories.push_back(weakestAdjacentTerritories[i]);
                    }            
                 }

                if (sourceTerritories.size() != 0){
                    for (int i=0; i< sourceTerritories.size(); i++ ){
                        if (sourceTerritories[i]->getArmy() >= highestArmyCount) {
                        highestArmyCount =sourceTerritories[i]->getArmy();
                        sourceTerritory = sourceTerritories[i];
                        }
                        cout << "Territory that we will be taking armies from: " << sourceTerritory->getName() << endl;
<<<<<<< Updated upstream
                        Advance* advanceOrder = new Advance(weakestTerritory, sourceTerritory, sourceTerritory->getArmy());
                        advanceOrder->execute(p);
=======
                       Advance* advanceOrder = new Advance(weakestTerritory, sourceTerritory, sourceTerritory->getArmy());
                        //advanceOrder->execute(p); 
                        p->myOrders->add(advanceOrder);
                        // Advance* advanceOrder = new Advance(weakestTerritory, sourceTerritory, sourceTerritory->getArmy());
                        advanceOrder->execute(p); 
>>>>>>> Stashed changes
                        }   
                 }
                 else{
                    cout << "All adjacent territories for the weakest territory (" << *weakestTerritory << ") have 0 armies. Cannot advance\n" << endl;
                 }
                
            }   
  }      
        



vector<Territory*> BenevolentPlayerStrategy::toAttack() {


};

vector<Territory*> BenevolentPlayerStrategy::toDefend() {



};

/************** NEUTRAL PLAYER STRATEGY **************/

NeutralPlayerStrategy::NeutralPlayerStrategy(Player* player) {

    this->p = player;
    // set player type to neutral
};

NeutralPlayerStrategy:: ~NeutralPlayerStrategy(){
    delete p;
}

ostream& operator<<(ostream& output, NeutralPlayerStrategy& ps) {
    output << ps.getName();
    return output;
}

NeutralPlayerStrategy:: NeutralPlayerStrategy(const NeutralPlayerStrategy& copy){
    this->p = copy.p; 
}

NeutralPlayerStrategy& NeutralPlayerStrategy:: operator =(const NeutralPlayerStrategy& rhs){
    this->p = rhs.p;
    return *this;
}


void NeutralPlayerStrategy::issueOrder(vector<Player*> players) {

    
    if (p->getIsAttacked() == true){
        cout<<"\nNeutral player has been attacked. Switching to aggressive strategy"<<endl;
        p->setStrategy(new AggressivePlayerStrategy(p));
        p->getStrategy()->issueOrder(players);
        p->setIsAttacked(false);

    } else {
         cout<<"\nNeutral player has not been attacked. Remaining neutral"<<endl;
    }

}


vector<Territory*> NeutralPlayerStrategy::toAttack() {


};

vector<Territory*> NeutralPlayerStrategy::toDefend() {


};

/************** CHEATER PLAYER STRATEGY **************/
CheaterPlayerStrategy::CheaterPlayerStrategy(Player* player) {

    this->p = player;
};

CheaterPlayerStrategy:: CheaterPlayerStrategy(const CheaterPlayerStrategy& copy){
    this->p = copy.p; 
}

CheaterPlayerStrategy& CheaterPlayerStrategy:: operator =(const CheaterPlayerStrategy& rhs){
    this->p = rhs.p;
    return *this;
}

CheaterPlayerStrategy:: ~CheaterPlayerStrategy(){
    delete p;
}


ostream& operator<<(ostream& output, CheaterPlayerStrategy& ps) {
    output << ps.getName();
    return output;
}

void CheaterPlayerStrategy::issueOrder(vector<Player*> players) {

    // cout << "PLAYER: " << this->p->getName() << "  STRATEGY: CHEATER" << endl;

    cout << "-- CHEATER STRATEGY WILL BE CONQUERING THE FOLLOWING TERRITORIES --" << endl;
    for (Territory* ter : this->toAttack()) {
        cout << "NAME: " << ter->getName() << " OWNER: " << ter->getOwner()->getName() << endl;
    }
   
    vector<Territory*> terToAttack = this->toAttack();
    for (int i = 0; i < terToAttack.size(); i++) {

        for (Player* player : players) {

            vector<Territory*> playerTer = player->getPlayerTerritories();
            for (int j = 0; j < playerTer.size(); j++) {

                if (playerTer[j]->getName() == terToAttack[i]->getName()) {
                    player->removeTerritory(j);
                    this->p->addTerritory(playerTer[j]);
                    playerTer[j]->setOwner(this->p);
                    
                }
            }
        }
    }

    cout << "-- UPDATED LIST OF PLAYER " << this->p->getName() << " OWNED TERRITORIES --" << endl;
    for (Territory* ter : this->p->getPlayerTerritories()) {
        cout << "NAME: " << ter->getName() << " OWNER: " << ter->getOwner()->getName() << endl;
    }


};

vector<Territory*> CheaterPlayerStrategy::toAttack() {

    vector<Territory*> territoriesToAttack;

    for (Territory* playerTerritory : this->p->getPlayerTerritories()) {
        
        for (Territory* adjTerritory : playerTerritory->getAdjacentTerritories()) {

            if (adjTerritory->getOwner()->getName() != this->p->getName()) {
                
                if (find(territoriesToAttack.begin(), territoriesToAttack.end(), adjTerritory) == territoriesToAttack.end()) {  // check if this works properly

                    territoriesToAttack.push_back(adjTerritory);
                }   
            }
        } 
    }
    return territoriesToAttack;
};

vector<Territory*> CheaterPlayerStrategy::toDefend() {

    vector<Territory*> territoriesToDefend;

    for (Territory* playerTerritory : this->p->getPlayerTerritories()) {

        for (Territory* adjTerritory : playerTerritory->getAdjacentTerritories()) {

            if (adjTerritory->getOwner()->getName() != this->p->getName()) {

                if (find(territoriesToDefend.begin(), territoriesToDefend.end(), adjTerritory) == territoriesToDefend.end()) {  // check if this works properly

                    territoriesToDefend.push_back(playerTerritory);
                    break;
                }  
            }
        }
    }
    return territoriesToDefend;
};
