
#include <iostream>
#include "GameEngine.h"
#include "LoggingObserver.h"
#include "Map.h"
#include "Player.h"
#include "Cards.h"
#include "Orders.h"
using namespace std;

int main() {
	// GameEngine* engine = new GameEngine();
	// cout << "Game engine created!" << endl << endl;
	// cout << *engine << endl;

	GameEngine e;
	e.startupPhase();


	// while (!engine->getIsGameOver()) {
	// 	string input;
	// 	cout << "Enter a command: ";
	// 	cin >> input;
	// 	engine->transition(input);
	// }

	// delete engine;
	// cout << "Game over!" << endl;
	// return 0;

	e.reinforcementPhase();
};