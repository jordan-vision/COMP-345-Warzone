#include "Player.h"
#include "Cards.h"
#include "Orders.h"
#include <iostream>
#include <vector>
#include <string>

int main()
{
    std::vector<Territory*> territoriesDefend;
    territoriesDefend.push_back(new Territory("Quebec"));
    territoriesDefend.push_back(new Territory("Ontario"));
    territoriesDefend.push_back(new Territory("Alberta"));
    territoriesDefend.push_back(new Territory("Alaska"));

    std::vector<Territory*> territoriesAttack;
    territoriesAttack.push_back(new Territory("Mexico"));
    territoriesAttack.push_back(new Territory("Argentina"));
    territoriesAttack.push_back(new Territory("Brazil"));
    territoriesAttack.push_back(new Territory("Venezuela"));

    //create a player
    Player player(territoriesDefend, territoriesAttack);

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



    std::cout << "\nTerritories to defend: " << std::endl;
    std::vector<Territory*> defendList = player.toDefend();
    for (int i = 0; i < defendList.size(); i++)
    {
        std::cout << defendList[i]->getName() << std::endl;
    }

    std::cout << "\nTerritories to attack: " << std::endl;
    std::vector<Territory*> attackList = player.toAttack();
    for (int i = 0; i < attackList.size(); i++)
    {
        std::cout << attackList[i]->getName() << std::endl;
    }

    std::cout << "\nIssued orders: " << std::endl;
    (*player.myOrders).printOrdersList();

}
