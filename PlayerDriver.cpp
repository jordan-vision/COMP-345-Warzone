#include "Player.h"
#include "Orders.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
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

    //create a player
    Player player(territoriesDefend, territoriesAttack);

    cout << "\nTerritories to defend: " << endl;
    vector<Territory*> defendList = player.toDefend();
    for (int i = 0; i < defendList.size(); i++)
    {
        cout << defendList[i]->getName() << endl;
    }

    cout << "\nTerritories to attack: " << endl;
    vector<Territory*> attackList = player.toAttack();
    for (int i = 0; i < attackList.size(); i++)
    {
        cout << attackList[i]->getName() << endl;
    }

    Deploy deploy;
    Advance advance;
    Bomb bomb;
    Blockade blockade;
    Airlift airlift;
    Negotiate negotiate;

    (*player.myOrders).add(&deploy);
    (*player.myOrders).add(&advance);
    (*player.myOrders).add(&bomb);
    (*player.myOrders).add(&blockade);
    (*player.myOrders).add(&airlift);
    (*player.myOrders).add(&negotiate);

    cout << "\nIssued orders: " << endl;
    player.issueOrder();
    (*player.myOrders).printOrdersList();
    

return 0;
};
