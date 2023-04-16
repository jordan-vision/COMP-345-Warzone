
#pragma once
#include "LoggingObserver.h"
#include "Map.h"
#include "Player.h"
#include "Cards.h"
#include "Orders.h"
#include "PlayerStrategy.h"
#include <string>
#include <vector>
#include <map>
#include <set>
#include <iostream>
using namespace std;

class State;
class Transition;
class DirectedGraph;
class PlayerStrategy;

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


class GameEngine : public ILoggable, public Subject 
{
private:
	bool isGameOver;
	DirectedGraph* gameLoop;

	static GameEngine* singletonInstance;
	GameEngine();
	GameEngine(GameEngine& toCopy);
	~GameEngine();

	void operator=(GameEngine& rhs);

public:
	bool getIsGameOver();
	DirectedGraph* getGameLoop();
	void setIsGameOver(bool isTheGameOver);

	static GameEngine* instance();

	void reset();
	bool transition(string command);
	bool hasGameStarted();

	virtual string stringToLog() override;

	//startup phase method implements a command-based user interaction mechanism 
	//to start the game by allowing the user to proceed with the game startup phase:
	void startupPhase();
	void mainGameLoop();
	void reinforcementPhase();
	void executeOrdersPhase();
	void issueOrdersPhase();
};

ostream& operator<<(ostream& out, GameEngine& engine);


class Tournament {
private:
	Map* maps[5];
	Player* players[4];
	int games, turns;

	static Tournament* singletonInstance;
	Tournament();
	Tournament(Map** maps, Player** players, int games, int turns);
	~Tournament();

public:
	static bool newTournament(string* mapStrings, Player** players, int games, int turns);
	static Tournament* instance();

	friend ostream& operator<<(ostream& out, Tournament& tournament);
};