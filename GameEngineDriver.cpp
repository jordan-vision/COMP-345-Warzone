
#include <iostream>
#include "GameEngine.h"
#include "LoggingObserver.h"
#include "Map.h"
#include "Player.h"
#include "Cards.h"
#include "Orders.h"
using namespace std;

int main() {

	GameEngine::instance()->reset(); //reset all previous settings 
	GameEngine::instance()->startupPhase(); // start the startup phase
	GameEngine::instance()->mainGameLoop(); // start the main game loop with its three phases

};