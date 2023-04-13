
#include <iostream>
#include "GameEngine.h"
#include "LoggingObserver.h"
#include "Map.h"
#include "Player.h"
#include "Cards.h"
#include "Orders.h"
#include "PlayerStrategy.h"
#include <vector>

using namespace std;

int main() {
// Player* p = new Player("ally");
// vector<Player*> players;
// players.push_back( (p));

// AggressivePlayerStrategy* agressiveplayer = new  AggressivePlayerStrategy(p);

// agressiveplayer->issueOrder(players);

// Player* p = new Player();
// AggressivePlayerStrategy* aggressive = new AggressivePlayerStrategy(p);
// vector<Player*> players = { p };
// aggressive->issueOrder(players);

// cout << p->getStrongestCountry(p)->getName() << endl;

	GameEngine::instance()->reset(); //reset all previous settings 
	GameEngine::instance()->startupPhase(); // start the startup phase
	GameEngine::instance()->mainGameLoop(); // start the main game loop with its three phases

};