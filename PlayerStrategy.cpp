#include "PlayerStrategy.h"

/************** NEUTRAL PLAYER STRATEGY **************/

NeutralPlayerStrategy::NeutralPlayerStrategy(Player* player) {

    this->p = player;
    // set player type to neutral
};

void NeutralPlayerStrategy::issueOrder(vector<Player*> players) {

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

    this->p = player;
    // set player type to human
};

void HumanPlayerStrategy::issueOrder(vector<Player*> players) {

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

};

vector<Territory*> AggressivePlayerStrategy::toAttack() {


};

vector<Territory*> AggressivePlayerStrategy::toDefend() {


};

/************* BENEVOLENT PLAYER STRATEGY *************/

BenevolentPlayerStrategy::BenevolentPlayerStrategy(Player* player) {

    this->p = player;
    // set player type to benevolent
};

void BenevolentPlayerStrategy::issueOrder(vector<Player*> players) {

};

vector<Territory*> BenevolentPlayerStrategy::toAttack() {


};

vector<Territory*> BenevolentPlayerStrategy::toDefend() {


};

