#include "PlayerStrategy.h"



/************** PLAYER STRATEGY  **************/


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










/************** NEUTRAL PLAYER STRATEGY **************/
NeutralPlayerStrategy::NeutralPlayerStrategy(Player* player) {
 this->p = player;
};

void NeutralPlayerStrategy::issueOrder(vector<Player*> players) {

for (int i = 0; i < p->getPlayerTerritories().size(); i++){
    if (p->getPlayerTerritories()[i]->getIsAttacked() == true){
        cout<<"\nNeutral player has been attacked. Switching to aggressive strategy"<<endl;
        p->setStrategy(new AggressivePlayerStrategy(p));
        p->getStrategy()->issueOrder(players);
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
    // set player type to cheater
};

void CheaterPlayerStrategy::issueOrder(vector<Player*> players) {

    // loop through adjacent enemy territories
    for (int i = 0; i < this->toAttack().size(); i++) {

        // check ownership of enemy territories 
        for (int j = 0; j < players.size(); j++) {
            
            // loop through enemy player territory
            for (Territory* playerTerritory : players[j]->getPlayerTerritories()) {

                // check territory name 
                if (playerTerritory->getName() == this->toAttack()[i]->getName()) {
                    
                    // remove territory from player 
                    // add territory to cheater
                    break;
                }
            }
        }
    }
};

vector<Territory*> CheaterPlayerStrategy::toAttack() {


};

vector<Territory*> CheaterPlayerStrategy::toDefend() {


};

/************** HUMAN PLAYER STRATEGY **************/

HumanPlayerStrategy::HumanPlayerStrategy(Player* player) {

};

void HumanPlayerStrategy::issueOrder(vector<Player*> players) {

};

vector<Territory*> HumanPlayerStrategy::toAttack() {


};

vector<Territory*> HumanPlayerStrategy::toDefend() {


};

/*************** AGGRESSIVE PLAYER STRATEGY ***************/

AggressivePlayerStrategy::AggressivePlayerStrategy(Player* player) {

   
    // set player type to aggressive

};

void AggressivePlayerStrategy::issueOrder(vector<Player*> players) {
     cout << "Aggressive player issuing order..." << endl;
    cout << p->getName() << endl;
Territory* strongestTerritory = p->getStrongestCountry(p);
cout << "Strongest territory: " << strongestTerritory->getName() << endl;
       vector<Territory*> strongestAdjacentTerritories = strongestTerritory->getAdjacentTerritories();
cout << "Number of strongest adjacent territories: " << strongestAdjacentTerritories.size() << endl;

      for (int i = 0; i < strongestAdjacentTerritories.size(); i++) {
            Territory* targetTerritory = strongestAdjacentTerritories[i];

            while (strongestTerritory->getArmy() > 0) {
                cout << "Target territory " << i +1 << ": " << targetTerritory->getName() << endl;

                Advance* advanceOrder = new Advance(targetTerritory, strongestTerritory, strongestTerritory->getArmy());
                cout << "Advance order created." << endl;
                   advanceOrder->execute(p);
                cout << "Advance order executed." << endl;
            }
      }
};

vector<Territory*> AggressivePlayerStrategy::toAttack() {
Territory* strongestTerritory = p->getStrongestCountry(p);
vector<Territory*> strongestAdjacentTerritoriesAttack = strongestTerritory->getOwner()->toAttack();
return strongestAdjacentTerritoriesAttack;

};

vector<Territory*> AggressivePlayerStrategy::toDefend() {
p->toDefend(p->getPlayerTerritories());

};

Territory* getStrongestCountry(Player* player){
    Territory* strongestTerritory = nullptr;
    int highestArmyCount = 0;
    for (Territory* ter : player->getPlayerTerritories()){
        if (ter->getArmy() > highestArmyCount) {
            highestArmyCount = ter->getArmy();
            strongestTerritory = ter;
        }
    }
    return strongestTerritory;
}

/************* BENEVOLENT PLAYER STRATEGY *************/

BenevolentPlayerStrategy::BenevolentPlayerStrategy(Player* player) {

    this->p = player;
    // set player type to benevolent
};

void BenevolentPlayerStrategy::issueOrder(vector<Player*> players) {
cout << "Benevolent player issuing order..." << endl;
cout << p->getName() << endl;
Territory* weakestTerritory = p->getWeakestCountry(p);
cout << "Weakest territory: " << weakestTerritory->getName() << endl;
vector<Territory*> weakestAdjacentTerritories = weakestTerritory->getAdjacentTerritories();
cout << "Number of weakest adjacent territories: " << weakestAdjacentTerritories.size() << endl;


        for (int i = 0; i < weakestAdjacentTerritories.size(); i++)
         {
            if (weakestAdjacentTerritories[i]->getOwner()->getName() == p->getName())
            {
                Territory* targetTerritory = weakestAdjacentTerritories[i];
                while (weakestTerritory->getArmy() > 0)
                {
                    cout << "Target territory " << i +1 << ": " << targetTerritory->getName() << endl;
                    Advance* advanceOrder = new Advance(targetTerritory, weakestTerritory, weakestTerritory->getArmy());
                    cout << "Advance order created." << endl;
                    advanceOrder->execute(p);
                    cout << "Advance order executed." << endl;


                }
            }

           
        }
    
};

vector<Territory*> BenevolentPlayerStrategy::toAttack() {


};

vector<Territory*> BenevolentPlayerStrategy::toDefend() {


};

