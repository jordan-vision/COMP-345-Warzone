#include "PlayerStrategy.h"



ostream& operator<<(ostream& output, PlayerStrategy& ps) {
    output << ps.getName();
    return output;
}

string PlayerStrategy:: getName(){
    return name; 
}

void PlayerStrategy:: setName(string name){
    this->name = name; 
}


/************** HUMAN PLAYER STRATEGY **************/

HumanPlayerStrategy::HumanPlayerStrategy(Player* player) {

    this->p = player;
    // set player type to human
};

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


void AggressivePlayerStrategy::issueOrder(vector<Player*> players) {

cout << "Aggressive player issuing order..." << endl;
// cout << p->getName() << endl;
Territory* strongestTerritory = p->getStrongestCountry(p);
int numberOfArmies = p->getArmy();
cout << "Player has " << p->getArmy() << " armies" <<endl;
// cout << p->getPlayerTerritories()[0] << endl;

        if (strongestTerritory != nullptr) 
        {
            cout << "Strongest territory: " << *strongestTerritory<< endl;
             if ( p->getArmy() !=0 ){ //  (2) a player will only issue deploy orders and no other kind of orders if they still have armies in their reinforcement pool;
            Deploy* deploy = new Deploy(strongestTerritory, numberOfArmies);
            int currentArmy = strongestTerritory->getArmy();
            strongestTerritory->setArmy(numberOfArmies + currentArmy);
            cout << "strongest has " << strongestTerritory->getArmy() << " armies" <<endl;
            cout<<"Created Deploy Order"<<endl;
            deploy->orderEffect = "order deployed";
            p->myOrders->add(deploy);// add deploy order to orderslist
             }
            vector<Territory*> strongestAdjacentTerritories = strongestTerritory->getAdjacentTerritories();
            cout << "Number of strongest adjacent territories: " << strongestAdjacentTerritories.size() << endl; 
            Territory* targetTerritory = strongestAdjacentTerritories[0];
             cout << "Target territory : " << targetTerritory->getName() << "\n" << endl;
             Advance* advanceOrder = new Advance(targetTerritory, strongestTerritory, strongestTerritory->getArmy());
            advanceOrder->execute(p);
             cout << "Aggressive Advance order executed.\n" << endl;
             
         
        } else
        {
            if ( p->getArmy() !=0 ){ //  (2) a player will only issue deploy orders and no other kind of orders if they still have armies in their reinforcement pool;
            Deploy* deploy = new Deploy( p->getPlayerTerritories()[0], numberOfArmies);
            p->getPlayerTerritories()[0]->setArmy(numberOfArmies);
            cout << p->getPlayerTerritories()[0]->getName() << " now has " << p->getPlayerTerritories()[0]->getArmy() << " armies" <<endl;
            cout<<"Created Deploy Order"<<endl;
            deploy->orderEffect = "order deployed";
             p->myOrders->add(deploy);// add deploy order to orderslist
            }
            cout << "Target Territory: " << p->getPlayerTerritories()[0]->getAdjacentTerritories()[0]->getName() << endl;
            Territory* targetTerritory =  p->getPlayerTerritories()[0]->getAdjacentTerritories()[0];
            Advance* advanceOrder = new Advance(targetTerritory, p->getPlayerTerritories()[0], p->getPlayerTerritories()[0]->getArmy());
              //  cout << "Advance order created.\n" << endl;
                advanceOrder->execute(p);
                cout << "Aggressive Advance order executed.\n" << endl;
        
            // cout<<"\nCannot advance with 0 armies"<<endl;

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

void BenevolentPlayerStrategy::issueOrder(vector<Player*> players) {
cout << "Benevolent player issuing order..." << endl;
Territory* weakestTerritory = p->getWeakestCountry(p);

//create new Deploy order to assign armies
// deploy all player's armies to the first territory in the list
Deploy* deploy = new Deploy(weakestTerritory, p->getArmy());
//p->myOrders->add(deploy);
deploy->execute(p);

cout << p->getName() << endl;

weakestTerritory = p->getWeakestCountry(p); // get weakest territory again after deploying armies

Territory* strongestTerritory = p->getStrongestCountry(p);
cout << "Weakest territory: " << weakestTerritory->getName() << endl;
cout << "Strongest territory: " << strongestTerritory->getName() << endl;

vector<Territory*> weakestAdjacentTerritories = weakestTerritory->getAdjacentTerritories();
cout << "Number of weakest adjacent territories: " << weakestAdjacentTerritories.size() << endl;

        for (int i = 0; i < weakestAdjacentTerritories.size(); i++)
         {
            if (weakestAdjacentTerritories[i]->getOwner()->getName() == p->getName())
            {
                cout << "found a weak adjacent territory belonging to " << p->getName() << endl;
                Territory* targetTerritory = weakestAdjacentTerritories[i];
                //while (weakestTerritory->getArmy() > 0)
                //{
                    cout << "Target territory " << i +1 << ": " << targetTerritory->getName() << endl;
                    Advance* advanceOrder = new Advance(targetTerritory, strongestTerritory, std::round(weakestTerritory->getArmy()));
                    cout << "Advance order created." << endl;
                    advanceOrder->execute(p);
                    cout << "Advance order executed." << endl;
                //}
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

void NeutralPlayerStrategy::issueOrder(vector<Player*> players) {

for (int i = 0; i < p->getPlayerTerritories().size(); i++){
    if (p->getPlayerTerritories()[i]->getIsAttacked() == true){
        cout<<"\nNeutral player has been attacked. Switching to aggressive strategy"<<endl;
        p->setStrategy(new AggressivePlayerStrategy(p));
        p->getStrategy()->issueOrder(players);
    } else {
         cout<<"\nNeutral player has not been attacked. Remaining neutral"<<endl;
    }

}
};

vector<Territory*> NeutralPlayerStrategy::toAttack() {


};

vector<Territory*> NeutralPlayerStrategy::toDefend() {


};

/************** CHEATER PLAYER STRATEGY **************/
CheaterPlayerStrategy::CheaterPlayerStrategy(Player* player) {

    this->p = player;
    // set player type to neutral
};

void CheaterPlayerStrategy::issueOrder(vector<Player*> players) {


    cout << this->p->getName();
    int index = 0;

    // loop through adjacent enemy territories
    for (int i = 0; i < this->toAttack().size(); i++) {

        // check ownership of enemy territories 
        for (int j = 0; j < players.size(); j++) {
            
            // loop through enemy player territory
            for (Territory* playerTerritory : players[j]->getPlayerTerritories()) {

                // check territory name 
                if (playerTerritory->getName() == this->toAttack()[i]->getName()) {
                    
                    this->p->getPlayerTerritories().erase(this->p->getPlayerTerritories().begin() + index);
				    playerTerritory->setOwner(this->p);
				    this->p->getPlayerTerritories().push_back(playerTerritory);
                    break;
                }
                index++;
            }
        }
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
