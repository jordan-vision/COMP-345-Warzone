
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include "GameEngine.h"
#include "Map.h"
#include "Player.h"
#include "Cards.h"
using namespace std;

/* 
*  This source file contains the implementation of all methods from the GameEngine class declared in the GameEngine.h header file. It also contains the implementations of methods from
*  user defined classes DirectedGraph, State and Transition which all aid in the implementation of the game loop diagram.
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
		transitions.push_back(newTransition);
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
	if ((unsigned)index < transitions.size()) return transitions.at(index);
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



DirectedGraph* GameEngine::gameLoop;
bool GameEngine::isGameOver;

// GAME ENGINE CLASS
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
	State* assignReinforcement = new State("game start");
	State* issueOrders = new State("issue orders");
	State* executeOrders = new State("execute orders");
	State* win = new State("win");


	// Transitions and commands
	start->connect(mapLoaded, "loadmap");
	mapLoaded->connect(mapLoaded, "loadmap");
	mapLoaded->connect(mapValidated, "validatemap");
	mapValidated->connect(playersAdded, "addplayer");
	playersAdded->connect(playersAdded, "addplayer");
	playersAdded->connect(assignReinforcement, "gamestart");
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
// Resets static components of GameEngine without having to instatiate it again
void GameEngine::reset(){
	if (gameLoop != NULL) {
		delete gameLoop;
	}

	// Start and end states
	isGameOver = false;
	State* start = new State("start");
	State* end = new State("end");
	gameLoop = new DirectedGraph(start, end);

	// All other states
	State* mapLoaded = new State("map loaded");
	State* mapValidated = new State("map validated");
	State* playersAdded = new State("players added");
	State* assignReinforcement = new State("game start");
	State* issueOrders = new State("issue orders");
	State* executeOrders = new State("execute orders");
	State* win = new State("win");


	// Transitions and commands
	start->connect(mapLoaded, "loadmap");
	mapLoaded->connect(mapLoaded, "loadmap");
	mapLoaded->connect(mapValidated, "validatemap");
	mapValidated->connect(playersAdded, "addplayer");
	playersAdded->connect(playersAdded, "addplayer");
	playersAdded->connect(assignReinforcement, "gamestart");
	assignReinforcement->connect(issueOrders, "issueorder");
	issueOrders->connect(issueOrders, "issueorder");
	issueOrders->connect(executeOrders, "endissueorders");
	executeOrders->connect(executeOrders, "execorder");
	executeOrders->connect(assignReinforcement, "endexecorders");
	executeOrders->connect(win, "win");
	win->connect(start, "play");
	win->connect(end, "end");
}

// Executes command if valid, prints an error message otherwise. Furthermore, if the end state is achieved will delete the game engine
bool GameEngine::transition(string command) {
	bool success = gameLoop->executeCommand(command);
	if (success) {
		cout << "Command " << command << " executed." << endl;
		cout << "New current state: " << gameLoop->getCurrentState()->getLabel() << endl << endl;
		// Notify(this);
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

string GameEngine::stringToLog() {

return "Game Engine New State: ...";
};

	//										    ********************** STARTUP PHASE ********************** 

vector<Player*> players;
void GameEngine::startupPhase() {
    MapLoader* loader = new MapLoader();
    Map* map;
    int x;
    bool validMap = false;


		//while loop to check if a valid map was chosen
    	while (!validMap) {
			cout << "\n--------------" << endl;
			cout << "Startup Phase: " << endl;
			cout << "--------------\n" << endl;

		//										********************** LOAD MAP COMMAND ********************** 

			//load map selection menu
			cout << "**************************************" << endl;
			cout << "\n1. Load Map \n" << endl;
			cout << "Please select a map by entering the number on the list:  " << endl;
			cout << "1. Chrono Trigger Map" << endl;
			cout << "2. Europe Map" << endl;
			cout << "3. Solar Map" << endl;
			cin >> x;

			//loads specific map depending on which one user choses
			if (x == 1) {
				map = loader->loadMap("Chrono_Trigger.map");
			} else if (x == 2) {
				map = loader->loadMap("europe.map");
			} else if (x == 3) {
				map = loader->loadMap("solar.map");
			} else {
				cout << "\nInvalid map selection." << endl;
				//invalid command
				transition("invalid");
				// re-prompt the selection if invalid choice
				continue; 
			}

			//loadmap state 
			transition("loadmap");

		//										********************** VALIDATE MAP COMMAND ********************** 
			cout << "**************************************" << endl;
			cout << "\n2. Validate Map\n" << endl;

			//if map is valid, transition to validate map state, if not the user is prompted to chose a valid map
			map->validate();
			if (map->getIsValid()) {
				validMap = true;
				transition("validatemap");
			} else {
				validMap = false;
				transition("invalid");
				cout << "Please choose a valid map.\n" << endl;
			}
        }

		//										********************** ADD PLAYER COMMAND ********************** 
		cout << "**************************************" << endl;
 		cout << "\n3. Add Player\n" << endl;

		int numPlayers;
		do {
			//prompt user to chose how many players there are
			cout << "Please enter the number of players (2-6):  " << endl;
			cin >> numPlayers;
			//if they chose a number out of the limits they must chose again  
			if (numPlayers < 2 || numPlayers > 6) {
				cout << "\nInvalid number of players.\n" << endl;
				transition("invalid");
			}
		} while (numPlayers < 2 || numPlayers > 6);

			cout << "\nYou have selected " << numPlayers << " players." <<endl;

		//loops for the amount of players so that the user can give each player a name
		for (int i = 0; i < numPlayers; i++) {
			cout << "Please enter the name of a player: " << endl;
			string name;
			cin >> name;
			Player* player = new Player(name);
			players.push_back(player);
		}

		//transition state
		cout << "\n" << endl;
		transition("addplayer");

		//										********************** GAME START COMMAND ********************** 
		cout << "**************************************" << endl;
	    cout << "\n4. Game Start\n" << endl;

	// a) fairly distribute all the territories to the players

		// get all territories from the map and put them into the vector
		vector<Territory*> territories = map->getTerritories();

		// shuffle the vector to randomize the order of the territories
		auto randomSeed = std::mt19937(std::random_device{}());
		std::shuffle(territories.begin(), territories.end(), randomSeed);

		//distribute variable calculates how many territories to give each player
		// total number of territories divided by total number of players = how many territories each player recieves 
		int distribute = territories.size() / players.size();

		//for loop to iterate through each player
		for (int i = 0; i < players.size(); i++) {
			//the loop will add random territories evenly between the players 
			//i * distribute is the index of the first territory that the player should receive
			//(i + 1) * distribute trepresents the end index of the range of territories that will be assigned to the player.
			for (int j = i * distribute; j < (i + 1) * distribute; j++) {
				//adds territory to player
				players[i]->owned(territories[j]);
				territories[j]->setOwner(players[i]);
			}
		}
		cout << "Number of territories: " << territories.size() << endl;
		cout << "Number of Players: " << players.size() << endl;
		cout << "When equally distributing the territories, each player will have: " << distribute << " territories." << endl;

		// print each player's territories
		for (int i = 0; i < players.size(); i++) {
			cout << "\nPlayer " << i + 1 << "'s territories "  << "("<< players[i]->getName() << "): \n"<< endl;
			for (int j = 0; j < players[i]->getPlayerTerritories().size(); j++) {
				cout << j+1 << ". " << players[i]->getPlayerTerritories()[j]->getName() << endl;
			}
			cout << endl;
		}
			cout << "----------------------------------------------\n" << endl;

		    // print each player's territories to attack
			cout << "List of territories to attack: " << endl;
			for (int i = 0; i < players.size(); i++) {
			cout << "\nPlayer " << i + 1 << "'s territories "  << "("<< players[i]->getName() << "): \n"<< endl;
			for (int j = 0; j < players[i]->toAttack().size(); j++) {
				cout << j+1 << ". " << players[i]->toAttack()[j]->getName() << endl;
			}
			cout << endl;
		}
			cout << "----------------------------------------------\n" << endl;

		   // print each player's territories to defend
			cout << "List of territories to defend: " << endl;
			for (int i = 0; i < players.size(); i++) {
			cout << "\nPlayer " << i + 1 << "'s territories "  << "("<< players[i]->getName() << "): \n"<< endl;
			for (int j = 0; j < players[i]->toDefend(territories).size(); j++) {
				cout << j+1 << ". " << players[i]->toDefend(territories)[j]->getName() << endl;
			}
			cout << endl;
		}
	// b) determine randomly the order of play of the players in the games 
			cout << "----------------------------------------------\n" << endl;

			// randomize the order of the territories
			vector<Player*> order(players.size());
			// Shuffle the order of players randomly
			std::shuffle(players.begin(), players.end(), randomSeed);

			// print the player order
			cout << "Player Order: \n";
			for (int i = 0; i < players.size(); i++) {
				cout << "Player " << i+1 << ": "<< players[i]->getName() << "\n";
			}
			cout << endl;

			
	// c) give 50 initial armies to the players, which are placed in their respective reinforcement pool 
			cout << "----------------------------------------------\n" << endl;

			cout << "Initial Armies: \n";
			for (int i = 0; i < players.size(); i++) {
				players[i]->setArmy(50);
				cout << "Player " << i+1 << " ("<< players[i]->getName() << "): " << players[i]->getArmy() << "\n";
			}
			cout << "\n";


	// d) get each player draw 2 initial cards from the deck using the deck’s draw() method 
			cout << "----------------------------------------------\n" << endl;

			//set hand size to 2
			const int HAND_SIZE = 2;
			//initialize and fill deck
			Deck myDeck;
			myDeck.fillDeck(20);
		
			//for loop to iterate through player.size
			for (int i = 0; i < players.size(); i++) 
			{
				//create a new hand for each player
    			Hand* hand = new Hand();
				players[i]->myHand = hand;

			//for loop to iterate through hand.size
    			for (int j = 0; j < HAND_SIZE; j++)
				{
				//draws card from the deck and gives it to the player's hand
       			players[i]->myHand->handCards.push_back(myDeck.draw());
				}
			}
			//loop to print out player's hand
			for (int i = 0; i < players.size(); i++) 
			{
				cout << "Player " << i + 1 << "'s hand " << "("<< players[i]->getName() << "): \n" << endl;
				for (int j = 0; j < players[i]->myHand->handCards.size(); j++)
				{
					cout << players[i]->myHand->handCards[j] << endl;
				}
				cout << endl;
			}

	// e) switch the game to the play phase
			if (transition("gamestart"))
			{
			cout << "Game has switched to Play Phase." << endl;
			}
	};


void GameEngine::mainGameLoop() {
	if (transition("gamestart"))
			{
			cout << "Game has switched to Play Phase." << endl;
			}

	reinforcementPhase();
	issueOrdersPhase();
	executeOrdersPhase();
	}

void GameEngine::issueOrdersPhase(){
	for (int i = 0; i < players.size(); i++) {
		// cout << "\nPlayer " << i + 1 << "'s "  << "("<< players[i]->getName() << ") turn to issue Order."<< endl;
    	// cout << "Enter your order: " << endl; // get order from user
		// string order;
		// cin >> order;
		players[i]->issueOrder(players[i]);

	}
}

void GameEngine::executeOrdersPhase(){
	int max = 0;    // Stores highest order count among players

    // Find player with most orders
    for (int i = 0; i < players.size() - 1; i++) 
        if (players[i]->myOrders->vectorOfOrders.size() >= players[i + 1]->myOrders->vectorOfOrders.size())
            max = players[i]->myOrders->vectorOfOrders.size();
        else 
            max = players[i + 1]->myOrders->vectorOfOrders.size();
    

    // Iterate through highest order count
    for (int j = 0; j < max; j++) 
        // Iterate through player count
        for (int i = 0; i < players.size(); i++) 
            // Execute highest priority order (if not empty)
            if (players[i]->myOrders->vectorOfOrders.size() != 0) 
                players[i]->myOrders->vectorOfOrders[0]->execute(players[i]);    // WILL NEED TO BE CHANGED FOR PART 3/4

}

void GameEngine::reinforcementPhase(){
for (int i = 0; i < players.size(); i++) {
    cout << "\nPlayer " << i + 1 << "'s territories "  << "("<< players[i]->getName() << "): \n"<< endl; // output players territories

	// 
	map<string, set<Territory*>> continentTerritories;
        
        for (Territory* territory : players[i]->getPlayerTerritories()) {
            cout << territory->getName() << endl;
            
            string continentName = territory->getContinent()->getName();
            continentTerritories[continentName].insert(territory);
        }
        
        bool sameContinent = true;
        string firstContinentName;
        
     for (auto it = continentTerritories.begin(); it != continentTerritories.end(); ++it) {
            const auto& continentName = it->first;
            const auto& t = it->second;

            if (firstContinentName.empty()) {
                firstContinentName = continentName;
            } else if (continentName != firstContinentName) {
                sameContinent = false;
                break;
            }
}
		if (sameContinent) {
            cout << "All territories are in the same continent: " << firstContinentName << endl;
			//players[i]->getPlayerTerritories()->;

        } else {
            cout << "Territories are in different continents." << endl;
        }


    cout << "Player " << i + 1 <<   " (" << players[i]->getName() << ") " << "number of territories: "  << players[i]->getPlayerTerritories().size() << endl;
	int numberTerritories = players[i]->getPlayerTerritories().size(); //get number of territories
	int currentArmies = players[i]->getArmy();
	players[i]->setArmy(numberTerritories/3 + currentArmies); // assign number of armies
	cout << "Player " << i + 1 <<   " (" << players[i]->getName() << ") " << "number of armies: "  << players[i]->getArmy() << endl;


}
}


