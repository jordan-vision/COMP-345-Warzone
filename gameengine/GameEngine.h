
#pragma once

#include "DirectedGraph.h"

class GameEngine {
private:
	bool isGameOver;
	DirectedGraph* gameLoop;

public:
	GameEngine();
	GameEngine(GameEngine& toCopy);
	~GameEngine();

	void operator=(GameEngine& rhs);

	bool getIsGameOver();
	DirectedGraph* getGameLoop();
	void setIsGameOver(bool isTheGameOver);

	bool acceptCommand(string command);
};

ostream& operator<<(ostream& out, GameEngine& engine);