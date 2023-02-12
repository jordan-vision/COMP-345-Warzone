#include "Player.h"
#include "Orders.h"
#include "Cards.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    Player p;
    p.toDefend();
    p.toAttack();
    //initialize order list
    OrdersList ord;
    p.myOrders = &ord;
    p.myOrders->add(new Bomb());
    // p.issueOrder("Deploy");

    return 0;
};
