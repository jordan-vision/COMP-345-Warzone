
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include "GameEngine.h"
using namespace std;

/* 
*  This source file contains the implementation of all methods from the GameEngine class declared in the GameEngine.h header file.
*/


// DIRECTEDGRAPH CLASS
// Constructors and destructor
DirectedGraph::DirectedGraph(State* theStart, State* theEnd) : startState(theStart), endState(theEnd) {
	currentState = startState;
};
// Copy constructor: all states and their transitions must be copied one-to-one
DirectedGraph::DirectedGraph(DirectedGraph& toCopy) {
	// Copying start state and current state if it is the same as the start state
	State* copyStart = toCopy.startState;
	startState = new State(copyStart->getLabel());
	endState = new State();
	currentState = new State();
	if (toCopy.startState == toCopy.currentState) {
		delete currentState;
		currentState = startState;
	}

	vector<State*> copiedStates = { copyStart }; // Vector of all copied states in the old object
	vector<State*> newlyCopiedStates = { copyStart }; // Vector of all states in the old object that have been copied in the previous iteraton of while
	vector<State*> newStates = { startState }; // Vector of all copied states in the new object

	while (!newlyCopiedStates.empty()) {
		vector<State*> nextNew; // Will replace the newlyCopiedStates vector at the end of the iteration

		for (State* state : newlyCopiedStates) {
			for (Transition* trans : state->getAllTransitions()) {
				State* arrivalState = trans->getArrivalState();
				State* newState;

				if (!count(copiedStates.begin(), copiedStates.end(), arrivalState)) { // Case 1: State has not yet been copied
					// Keeping track of copied states in both the old and new objects
					newState = new State(arrivalState->getLabel());
					copiedStates.push_back(arrivalState);
					newStates.push_back(newState);
					nextNew.push_back(arrivalState);

					// Checking if copied state is end state
					if (arrivalState == toCopy.getEndState()) {
						delete endState;
						endState = newState;
					}

					// Checking if copied state is current state
					if (arrivalState == toCopy.getCurrentState()) {
						delete currentState;
						currentState = newState;
					}
				}
				else { // Case 2: State has already been copied
					newState = newStates.at(indexOfState(copiedStates, arrivalState));
				}

				// Connecting states in new object
				newStates.at(indexOfState(copiedStates, state))->connect(newState, trans->getLabel());
			}
		}

		newlyCopiedStates = nextNew;
	}
};
// Destructor: all states and their transitions must be deleted
DirectedGraph::~DirectedGraph() {
	vector<State*> markedForDeletion = { startState }; // Vector of all states that will be deleted
	vector<State*> newlyMarked = { startState }; // Vector of all states that have been marked for deletion in the previous iteration of while

	while (!newlyMarked.empty()) {
		vector<State*> nextNew; // Will replace the newlyMarked vector at the end of the iteration

		for (State* state : newlyMarked) {
			for (Transition* trans : state->getAllTransitions()) {
				State* arrivalState = trans->getArrivalState();

				if (!count(markedForDeletion.begin(), markedForDeletion.end(), arrivalState)) {
					// Keeping tracked of all states that are marked for deletion
					markedForDeletion.push_back(arrivalState);
					nextNew.push_back(arrivalState);
				}
			}
		}

		newlyMarked = nextNew;
	}

	// Deleting all states
	for (State* toDelete : markedForDeletion) {
		delete toDelete;
	}
};

// Assignment operator
void DirectedGraph::operator=(DirectedGraph& rhs) {
	startState = rhs.startState;
	endState = rhs.endState;
	currentState = rhs.currentState;
};

// Getters and setters
State* DirectedGraph::getStartState() { return startState; };
State* DirectedGraph::getEndState() { return endState; };
State* DirectedGraph::getCurrentState() { return currentState; };
void DirectedGraph::setStartState(State* theStart) { startState = theStart; };
void DirectedGraph::setEndState(State* theEnd) { endState = theEnd; };
void DirectedGraph::setCurrentState(State* theState) { currentState = theState; };

// Other methods
// Returns true if the command is valid, false otherwise
bool DirectedGraph::executeCommand(string command) {
	State* tempState = currentState->executeCommand(command);
	if (tempState != NULL) {
		currentState = tempState;
		return true;
	}
	return false;
};


// STATE CLASS
// Constructors and destructror
State::State() : State("unnamed") {};
State::State(string theLabel) : label(theLabel) {};
// Copy constructor: transitions are copied, but still connect to the same destination states
State::State(State& toCopy) {
	label = toCopy.label;
	for (Transition* trans : toCopy.transitions) {
		Transition* newTransition = new Transition(*trans);
		transitions.push_back(trans);
	}
};
// Destructor: all transitions deleted one to one
State::~State() {
	for (Transition* trans : transitions) {
		delete trans;
	}
	transitions.clear();
};

// Assignment operator
void State::operator=(State& rhs) {
	label = rhs.label;
	transitions = rhs.transitions;
};

// Getters and setters
string State::getLabel() { return label; };
vector<Transition*> State::getAllTransitions() { return transitions; }
Transition* State::getTransition(int index) {
	if (index < transitions.size()) return transitions.at(index);
	else return NULL;
};
void State::setLabel(string theLabel) { label = theLabel; };

// Other methods
// Creates new transition between this state and another
void State::connect(State* arrivalState, string transitionLabel) {
	Transition* newTransition = new Transition(transitionLabel);
	newTransition->setArrivalState(arrivalState);
	transitions.push_back(newTransition);
};
// Returns the following state if the command is valid, NULL otherwise
State* State::executeCommand(string command) {
	for (Transition* trans : transitions) {
		if (trans->getLabel().compare(command) == 0) {
			return trans->getArrivalState();
		}
	}
	return NULL;
};


// TRANSITION CLASS
// Constructors
Transition::Transition(string theLabel) : label(theLabel) {
	arrivalState = NULL;
};
Transition::Transition(Transition& toCopy) {
	label = toCopy.label;
	arrivalState = toCopy.arrivalState;
};

// Assignment operator
void Transition::operator=(Transition& rhs) {
	label = rhs.label;
	arrivalState = rhs.arrivalState;
};

// Getters and setters
string Transition::getLabel() { return label; };
State* Transition::getArrivalState() { return arrivalState; };
void Transition::setLabel(string theLabel) { label = theLabel; };
void Transition::setArrivalState(State* theArrival) { arrivalState = theArrival; };


// FREE FUNCTIONS

// Stream isertion operators
ostream& operator<<(ostream& out, State& state) {
	out << state.getLabel();
	for (Transition* trans : state.getAllTransitions()) {
		out << endl << "\t" << *trans;
	}
	return out;
};
ostream& operator<<(ostream& out, Transition& transition) {
	out << transition.getLabel();
	out << " -> " << transition.getArrivalState()->getLabel();
	return out;
};
ostream& operator<<(ostream& out, DirectedGraph& graph) {
	out << "DIRECTED GRAPH" << endl << endl;
	out << "START: " << *graph.getStartState() << endl << endl;
	vector<State*> allPrinted = { graph.getStartState() };
	vector<State*> newlyPrinted = { graph.getStartState() };

	while (!newlyPrinted.empty()) {
		vector<State*> nextNew;

		for (State* state : newlyPrinted) {
			for (Transition* trans : state->getAllTransitions()) {
				State* arrivalState = trans->getArrivalState();

				if (!count(allPrinted.begin(), allPrinted.end(), arrivalState)) {
					if (arrivalState == graph.getEndState()) {
						out << "END: ";
					}
					out << *arrivalState << endl << endl;
					allPrinted.push_back(arrivalState);
					nextNew.push_back(arrivalState);
				}
			}
		}

		newlyPrinted = nextNew;
	}
	return out;
};

// Returns first position of specific state in vector, if said state is in said vector
int indexOfState(vector<State*> vec, State* element) {
	vector<State*>::iterator itr = find(vec.begin(), vec.end(), element);
	if (itr != vec.cend()) {
		return distance(vec.begin(), itr);
	}
	return -1;
};

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