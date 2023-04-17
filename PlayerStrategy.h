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
        virtual void issueOrder(vector<Player*> player) = 0;
        virtual vector<Territory*> toAttack() = 0;
        virtual vector<Territory*> toDefend() = 0;
        vector<Territory*> strongestTerritory;
       // PlayerStrategy& operator =(const PlayerStrategy& rhs);
      //  PlayerStrategy(const PlayerStrategy& copy);
        PlayerStrategy* ps;
        string getName();   
        void setName(string name);   
        ~PlayerStrategy();      
        friend ostream& operator<<(ostream& output, PlayerStrategy& c);     



    private:
        string name;


};

class NeutralPlayerStrategy : public PlayerStrategy {

    public:
        ~NeutralPlayerStrategy();  
        NeutralPlayerStrategy(Player* p);
        NeutralPlayerStrategy& operator =(const NeutralPlayerStrategy& rhs);
        NeutralPlayerStrategy(const NeutralPlayerStrategy& copy);
        friend ostream& operator<<(ostream& output, NeutralPlayerStrategy& c);  
 
        void issueOrder(vector<Player*> player) override;
        vector<Territory*> toAttack() override;
        vector<Territory*> toDefend() override;
};

class CheaterPlayerStrategy : public PlayerStrategy {

    public:
        ~CheaterPlayerStrategy(); 
        CheaterPlayerStrategy(Player* p);
        CheaterPlayerStrategy& operator =(const CheaterPlayerStrategy& rhs);
        CheaterPlayerStrategy(const CheaterPlayerStrategy& copy);
        friend ostream& operator<<(ostream& output, CheaterPlayerStrategy& c);
        void issueOrder(vector<Player*> player) override;
        vector<Territory*> toAttack() override;
        vector<Territory*> toDefend() override;
};

class HumanPlayerStrategy : public PlayerStrategy {

    public:
        ~HumanPlayerStrategy();
        HumanPlayerStrategy(Player* p);
        HumanPlayerStrategy& operator =(const HumanPlayerStrategy& rhs);
        HumanPlayerStrategy(const HumanPlayerStrategy& copy);
        friend ostream& operator<<(ostream& output, HumanPlayerStrategy& c);
        void issueOrder(vector<Player*> player) override;
        vector<Territory*> toAttack() override;
        vector<Territory*> toDefend() override;
};

class AggressivePlayerStrategy : public PlayerStrategy {

    public:
        ~AggressivePlayerStrategy();
        AggressivePlayerStrategy(Player* p);
        AggressivePlayerStrategy& operator =(const AggressivePlayerStrategy& rhs);
        AggressivePlayerStrategy(const AggressivePlayerStrategy& copy);
        friend ostream& operator<<(ostream& output, AggressivePlayerStrategy& c);
        void issueOrder(vector<Player*> player) override;
        vector<Territory*> toAttack() override;
        vector<Territory*> toDefend() override;
};

class BenevolentPlayerStrategy : public PlayerStrategy {

    public:
        ~BenevolentPlayerStrategy();
        BenevolentPlayerStrategy(Player* p);
        BenevolentPlayerStrategy& operator =(const BenevolentPlayerStrategy& rhs);
        BenevolentPlayerStrategy(const BenevolentPlayerStrategy& copy);
        friend ostream& operator<<(ostream& output, BenevolentPlayerStrategy& c);
        void issueOrder(vector<Player*> player) override;
        vector<Territory*> toAttack() override;
        vector<Territory*> toDefend() override;
};