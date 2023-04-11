#pragma once

#include "Player.h"
#include <vector>
#include <iostream>
#include <iomanip>
#include <algorithm> 
#include <random>


using namespace std;

class Player;
class Terrirtory;


class PlayerStrategy {


    public:

        Player* p;
        virtual void issueOrder(vector<Player*> player) = 0;
        virtual vector<Territory*> toAttack() = 0;
        virtual vector<Territory*> toDefend() = 0;
    private:


};

class NeutralPlayerStrategy : public PlayerStrategy {

    public:
        NeutralPlayerStrategy(Player* p);
        void issueOrder(vector<Player*> player) override;
        vector<Territory*> toAttack() override;
        vector<Territory*> toDefend() override;
};

class CheaterPlayerStrategy : public PlayerStrategy {

    public:
        CheaterPlayerStrategy(Player* p);
        void issueOrder(vector<Player*> player) override;
        vector<Territory*> toAttack() override;
        vector<Territory*> toDefend() override;
};

class HumanPlayerStrategy : public PlayerStrategy {

    public:
        HumanPlayerStrategy(Player* p);
        void issueOrder(vector<Player*> player) override;
        vector<Territory*> toAttack() override;
        vector<Territory*> toDefend() override;
};

class AggressivePlayerStrategy : public PlayerStrategy {

    public:
        AggressivePlayerStrategy(Player* p);
        void issueOrder(vector<Player*> player) override;
        vector<Territory*> toAttack() override;
        vector<Territory*> toDefend() override;
};

class BenevolentPlayerStrategy : public PlayerStrategy {

    public:
        BenevolentPlayerStrategy(Player* p);
        void issueOrder(vector<Player*> player) override;
        vector<Territory*> toAttack() override;
        vector<Territory*> toDefend() override;
};