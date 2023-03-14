
#include <iostream>
#include "GameEngine.h"
using namespace std;

int main() {
	GameEngine* engine = new GameEngine();
	cout << "Game engine created!" << endl << endl;
	cout << *engine << endl;

	while (!engine->getIsGameOver()) {
		string input;
		cout << "Enter a command: ";
		cin >> input;
		engine->transition(input);
	}

	delete engine;
	cout << "Game over!" << endl;
	return 0;
};