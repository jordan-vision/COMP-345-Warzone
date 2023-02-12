#include "Player.h"
#include "Orders.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    // vector<Territory*> territoriesDefend;
    // territoriesDefend.push_back(new Territory("Quebec"));
    // territoriesDefend.push_back(new Territory("Ontario"));
    // territoriesDefend.push_back(new Territory("Alberta"));
    // territoriesDefend.push_back(new Territory("Alaska"));

    // vector<Territory*> territoriesAttack;
    // territoriesAttack.push_back(new Territory("Mexico"));
    // territoriesAttack.push_back(new Territory("Argentina"));
    // territoriesAttack.push_back(new Territory("Brazil"));
    // territoriesAttack.push_back(new Territory("Venezuela"));


    //create a player
    // Player player(territoriesDefend, territoriesAttack);

    // cout << "\nTerritories to defend: " << endl;
    // vector<Territory*> defendList = player.toDefend();
    // for (int i = 0; i < defendList.size(); i++)
    // {
    //     cout << defendList[i]->getName() << endl;
    // }

    // cout << "\nTerritories to attack: " << endl;
    // vector<Territory*> attackList = player.toAttack();
    // for (int i = 0; i < attackList.size(); i++)
    // {
    //     cout << attackList[i]->getName() << endl;
    // }

    // OrdersList ordersList;

    // Deploy deploy;
    // Advance advance;
    // Bomb bomb;
    // Blockade blockade;
    // Airlift airlift;
    // Negotiate negotiate;

    // ordersList.add(&deploy);
    // ordersList.add(&advance);
    // ordersList.add(&bomb);
    // ordersList.add(&blockade);
    // ordersList.add(&airlift);
    // ordersList.add(&negotiate);
    Player player;

    vector<Territory*> territoriesDefend;
    territoriesDefend.push_back(new Territory("Quebec"));
    territoriesDefend.push_back(new Territory("Ontario"));
    territoriesDefend.push_back(new Territory("Alberta"));
    territoriesDefend.push_back(new Territory("Alaska"));

    vector<Territory*> territoriesAttack;
    territoriesAttack.push_back(new Territory("Mexico"));
    territoriesAttack.push_back(new Territory("Argentina"));
    territoriesAttack.push_back(new Territory("Brazil"));
    territoriesAttack.push_back(new Territory("Venezuela"));

    cout << "\nTerritories to defend: " << endl;
    for(auto &t : territoriesDefend) 
    {
        cout << *t << endl;
    }

    cout << "\nTerritories to attack: " << endl;
    for(auto &t : territoriesAttack) 
    {
        cout << *t << endl;
    }
    cout << "\nIssued orders: " << endl;
    
//     player.issueOrder("Deploy");
//     player.issueOrder("Advance");
//     player.issueOrder("Bomb");
//     player.issueOrder("Blockade");
//     player.issueOrder("Airlift");
//     player.issueOrder("Negotiate");
//     OrdersList* orders = player.getOrders();


   OrdersList ordersList;

    Deploy deploy;
    Advance advance;
    Bomb bomb;
    Blockade blockade;
    Airlift airlift;
    Negotiate negotiate;

    ordersList.add(&deploy);
    ordersList.add(&advance);
    ordersList.add(&bomb);
    ordersList.add(&blockade);
    ordersList.add(&airlift);
    ordersList.add(&negotiate);
    cout << ordersList << endl;


return 0;
};
