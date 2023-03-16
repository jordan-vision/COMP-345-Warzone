
#pragma once
// #include "LoggingObserver.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;

class State;
class Transition;
class DirectedGraph;

class DirectedGraph {
private:
	State* startState, * endState, * currentState;

public:
	DirectedGraph(State* theStart, State* theEnd);
	DirectedGraph(DirectedGraph& toCopy);
	~DirectedGraph();

	void operator=(DirectedGraph& rhs);

	State* getStartState();
	State* getEndState();
	State* getCurrentState();
	void setStartState(State* theStart);
	void setEndState(State* theEnd);
	void setCurrentState(State* theState);

	bool executeCommand(string command);
};

ostream& operator<<(ostream& out, DirectedGraph& graph);

int indexOfState(vector<State*> vec, State* element);


class State {
private:
	string label;
	vector<Transition*> transitions;

public:
	State();
	State(string theLabel);
	State(State& toCopy);
	~State();

	void operator=(State& rhs);

	string getLabel();
	vector<Transition*> getAllTransitions();
	Transition* getTransition(int index);
	void setLabel(string theLabel);

	void connect(State* arrivalState, string transitionLabel);
	State* executeCommand(string command);
};

ostream& operator<<(ostream& out, State& state);


class Transition {
private:
	string label;
	State* arrivalState;

public:
	Transition(string theLabel);
	Transition(Transition& toCopy);

	void operator=(Transition& rhs);

	string getLabel();
	State* getArrivalState();
	void setLabel(string theLabel);
	void setArrivalState(State* theArrival);
};

ostream& operator<<(ostream& out, Transition& transition);


class GameEngine 
// : public ILoggable, public Subject 
{
private:
	bool isGameOver;
	DirectedGraph* gameLoop;
	string fileName;
	string playerName;

public:
	GameEngine();
	GameEngine(GameEngine& toCopy);
	~GameEngine();

	void operator=(GameEngine& rhs);

	bool getIsGameOver();
	DirectedGraph* getGameLoop();
	void setIsGameOver(bool isTheGameOver);

	bool transition(string command);

	// virtual string stringToLog() override;

	//startup phase method implements a command-based user interaction mechanism 
	//to start the game by allowing the user to proceed with the game startup phase:
	void startupPhase();
	//load map method: select a map from a list of map files as stored in a directory, which results in the map being loaded in the game
	void loadMap(string fileName);
	//validate map
    void validateMap();
	//add players
    void addPlayer(string playerName);
	//starts the game
	void gameStart();
	//fairly distribute all the territories to the players
	void distributeTerritories();
	//determine randomly the order of play of the players in the game
	void playerOrder();
	//give 50 initial armies to the players, which are placed in their respective reinforcement pool
    void assignInitialArmies();
	//let each player draw 2 initial cards from the deck using the deck’s draw() method
    void drawInitialCards();
	//switch the game to the play phase
    void switchToPlayPhase();


};

ostream& operator<<(ostream& out, GameEngine& engine);