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
    p.issueOrder("Deploy");

    return 0;
};
