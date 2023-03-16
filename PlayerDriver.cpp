#include "Player.h"
#include "Orders.h"
#include "Cards.h"
#include "Cards.h"

#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    //creating player p
    Player p;
    //calling methods'
    p.owned();
    p.toDefend();
    p.toAttack();
    p.issueOrder("Deploy");
    p.issueOrder("Advance");

    return 0;
};
