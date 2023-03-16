
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
};

ostream& operator<<(ostream& out, GameEngine& engine);