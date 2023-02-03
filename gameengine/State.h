
#pragma once

#include <string>
#include <vector>
using namespace std;

class Transition;

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