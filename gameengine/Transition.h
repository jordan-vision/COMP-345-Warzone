
#pragma once

#include <string>
using namespace std;

class State;

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