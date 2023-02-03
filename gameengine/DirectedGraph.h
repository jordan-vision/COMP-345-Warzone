
#pragma once

#include <string>
#include <vector>
using namespace std;

class State;

class DirectedGraph {
private:
	State *startState, *endState, *currentState;

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