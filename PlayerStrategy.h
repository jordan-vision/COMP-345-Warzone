#pragma once

#include "Player.h"
#include "Orders.h"
#include "Map.h"
#include "GameEngine.h"
#include <vector>
#include <iostream>
#include <iomanip>
#include <algorithm> 
#include <random>


using namespace std;

class Player;
class Terrirtory;
class Advance;


class PlayerStrategy {


    public:

        Player* p;
        virtual void issueOrder(vector<Player*> player, int index) = 0;
        virtual vector<Territory*> toAttack() = 0;
        virtual vector<Territory*> toDefend() = 0;
        vector<Territory*> strongestTerritory;
        PlayerStrategy* ps;
        string getName();   
        void setName(string name);         


    private:
        string name;


};

class NeutralPlayerStrategy : public PlayerStrategy {

    public:
        NeutralPlayerStrategy(Player* p);
        void issueOrder(vector<Player*> player, int index) override;
        vector<Territory*> toAttack() override;
        vector<Territory*> toDefend() override;
};

class CheaterPlayerStrategy : public PlayerStrategy {

    public:
        CheaterPlayerStrategy(Player* p);
        void issueOrder(vector<Player*> player, int index) override;
        vector<Territory*> toAttack() override;
        vector<Territory*> toDefend() override;
};

class HumanPlayerStrategy : public PlayerStrategy {

    public:
        HumanPlayerStrategy(Player* p);
        void issueOrder(vector<Player*> player, int index) override;
        vector<Territory*> toAttack() override;
        vector<Territory*> toDefend() override;
};

class AggressivePlayerStrategy : public PlayerStrategy {

    public:
        AggressivePlayerStrategy(Player* p);
        void issueOrder(vector<Player*> player, int index) override;
        vector<Territory*> toAttack() override;
        vector<Territory*> toDefend() override;
};

class BenevolentPlayerStrategy : public PlayerStrategy {

    public:
        BenevolentPlayerStrategy(Player* p);
        void issueOrder(vector<Player*> playe, int indexr) override;
        vector<Territory*> toAttack() override;
        vector<Territory*> toDefend() override;
};