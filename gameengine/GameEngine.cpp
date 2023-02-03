
#include <iostream>
#include "GameEngine.h"
#include "State.h"
using namespace std;

/* 
*  This source file contains the implementation of all methods from the GameEngine class declared in the GameEngine.h header file.
*/

// Constructors and destructor
GameEngine::GameEngine() {
	// Start and end states
	isGameOver = false;
	State* start = new State("start");
	State* end = new State("end");
	gameLoop = new DirectedGraph(start, end);

	// All other states
	State* mapLoaded = new State("map loaded");
	State* mapValidated = new State("map validated");
	State* playersAdded = new State("players added");
	State* assignReinforcement = new State("assign reinforcements");
	State* issueOrders = new State("issue orders");
	State* executeOrders = new State("execute orders");
	State* win = new State("win");

	// Transitions and commands
	start->connect(mapLoaded, "loadmap");
	mapLoaded->connect(mapLoaded, "loadmap");
	mapLoaded->connect(mapValidated, "validatemap");
	mapValidated->connect(playersAdded, "addplayer");
	playersAdded->connect(playersAdded, "addplayer");
	playersAdded->connect(assignReinforcement, "assigncountries");
	assignReinforcement->connect(issueOrders, "issueorder");
	issueOrders->connect(issueOrders, "issueorder");
	issueOrders->connect(executeOrders, "endissueorders");
	executeOrders->connect(executeOrders, "execorder");
	executeOrders->connect(assignReinforcement, "endexecorders");
	executeOrders->connect(win, "win");
	win->connect(start, "play");
	win->connect(end, "end");
};
GameEngine::GameEngine(GameEngine& toCopy) {
	isGameOver = false;
	gameLoop = new DirectedGraph(*toCopy.gameLoop);
};
// Destructor: all states will be deleted along with the graph
GameEngine::~GameEngine() {
	delete gameLoop;
};

// Assignment operator
void GameEngine::operator=(GameEngine& rhs) {
	gameLoop = rhs.gameLoop;
};

// Getters and setters
bool GameEngine::getIsGameOver() { return isGameOver; };
DirectedGraph* GameEngine::getGameLoop() { return gameLoop; };
void GameEngine::setIsGameOver(bool isTheGameOver) { isGameOver = isTheGameOver; };

// Other methods
// Executes command if valid, prints an error message otherwise. Furthermore, if the end state is achieved will delete the game engine
bool GameEngine::acceptCommand(string command) {
	bool success = gameLoop->executeCommand(command);
	if (success) {
		cout << "Command " << command << " executed." << endl;
		cout << "New current state: " << gameLoop->getCurrentState()->getLabel() << endl << endl;
		if (gameLoop->getCurrentState() == gameLoop->getEndState()) {
			isGameOver = true;
		}
	}
	else {
		cout << "Invalid command" << endl << endl;
	}
	return success;
};

// Stream insertion operator
ostream& operator<<(ostream& out, GameEngine& engine) {
	out << "GAME ENGINE -- ";
	out << *engine.getGameLoop();
	return out;
}