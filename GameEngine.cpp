
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include "GameEngine.h"
#include "Map.h"
#include "Player.h"
#include "Cards.h"
#include "CommandProcessing.h"

using namespace std;

int ALL_TERRITORIES = 24;

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



// GAME ENGINE CLASS
GameEngine* GameEngine::singletonInstance;

// Constructors and destructor
GameEngine::GameEngine() {
	isGameOver = false;
	gameLoop = NULL; // Directed Graph instantiated with GameEngine::reset()
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

void GameEngine::addPlayer(Player* player) {
	players.push_back(player);
}

GameEngine* GameEngine::instance() {
	if (!singletonInstance) {
		singletonInstance = new GameEngine();
	}
	return singletonInstance;
}

// Other methods
// Instantiates components of GameEngine and resets game loop
void GameEngine::reset(){
	if (gameLoop == NULL) {
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
		issueOrders->connect(executeOrders, "issueordersend");
		executeOrders->connect(executeOrders, "execorder");
		executeOrders->connect(assignReinforcement, "endexecorders");
		executeOrders->connect(win, "win");
		win->connect(start, "replay");
		win->connect(end, "quit");
	}
	else {
		gameLoop->setCurrentState(gameLoop->getStartState());
		isGameOver = false;
	}
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

bool GameEngine::hasGameStarted() {
	return (gameLoop->getCurrentState() != gameLoop->getStartState());
}

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


// new command processor object to call the getCommand method
CommandProcessor* cp = new CommandProcessor();

void GameEngine::startupPhase() {

			//command selection menu
			cout << "\n--------------" << endl;
			cout << "Startup Phase: " << endl;
			cout << "--------------\n" << endl;	

		MapLoader* loader = new MapLoader();
   		Map* map;
		string filename;
		string playername;


		bool isCommand = true;

		// while loop to keep asking user for commands
		while (isCommand){
			cout << "\nPick a command: \n" << endl;
			cout << "1. Load Map: enter command using the format -> loadmap <filename>" << endl;
			cout << "2. Validate Map: enter command validatemap" << endl;
			cout << "3. Add Player enter command using the format -> addplayer <playername>" << endl;
			cout << "4. Game Start: enter command gamestart\n" << endl;

			// The getCommand function will ask and read the command that the user inputs
			// It will then save it in a list of commands (vector) belonging to the command processor 
			Command* command = cp->getCommand();

			// The commandName is the entire command string the user inputs
			string commandName= command->getCommandName();

			string commandEffect =command->getCommandEffect();

			// Because the load map command is in the form of "loadmap <example.map>", We get the file name 
			// by taking only what's in the <    > brackets that are in the command name 
			string filename = commandName.substr(commandName.find("<") + 1, commandName.size() - (commandName.find(">")-9));
			

			// checks to see if the first word of the command the user inputs is "loadmap" 
			// if so, we load the map specified
			if (commandName.substr(0,7) == "loadmap")
			{
				map = loader->loadMap(filename);
				transition("loadmap");

			}

			// checks to see if the first word of the command the user inputs is "validatemap" 
			// if so, we validate the previously loaded map
			if (commandEffect == "validatemap")
			{    
				//if map is valid, transition to validate map state, if not the user is prompted to chose a valid map
				map->validate();
				if (map->getIsValid())
				 {
					transition("validatemap");
				} else {
					transition("invalid");
					cout << "Please choose a valid map.\n" << endl;
				}

			}
			
				// checks to see if the first word of the command the user inputs is "addplayer" 
				// if so, we add players to the game
				if (commandName.substr(0,9) == "addplayer")
				{
				
				// This takes only the name in the command string "addplayer <playername>"
				string newPlayerName = commandName.substr(commandName.find_first_of("<")+  1, commandName.find_last_of(">") - commandName.find_first_of("<") - 1);
				Player* player = new Player(newPlayerName);
				players.push_back(player);

				transition("addplayer");
				}
			
		
			
			if (commandEffect == "gamestart") 
			{   
				// The command gamestart can only be used if the player number is between 2 to 6
				if (players.size() >= 2 && players.size() <= 6){

				cout << "\nYou have selected " << players.size() << " players: " <<endl;
				for (int i=0; i < players.size(); i++){
		 		cout << "\nPlayer " << i + 1 << ": "<< players[i]->getName() << "\n"<< endl;
				}

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
					const int HAND_SIZE = 5;
					//initialize and fill deck
					Deck myDeck;
					myDeck.fillDeck(20);
					
					//for loop to iterate through player.size
					for (int i = 0; i < players.size(); i++) 
					{
						//create a new hand for each player
						Hand* hand = new Hand();
						OrdersList* ordersList = new OrdersList();
						players[i]->myOrders = ordersList;
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
				
				// setting the bool to false to stop the while loop
				isCommand = false;

				}


				// The condition if number of players is less than 2 or greater than 6 
				// The gamestart command will be invalid 
				else
				{					
					cout << "\nInvalid number of players.\n" << endl;
					// transition("invalid");
				}
			}
		}
}
			

void GameEngine::mainGameLoop() {
	if (transition("gamestart"))
			{
			cout << "Game has switched to Play Phase." << endl;
			}

	bool gameNotDone = true;

	while (gameNotDone){
		reinforcementPhase();
		issueOrdersPhase(false);
		executeOrdersPhase(false);
		for (auto p: players){
			if (p->getPlayerTerritories().size() >= ALL_TERRITORIES){
				cout<<"\nGAME IS DONE"<<endl;
				gameNotDone = false; 
				
			}
	}
	}
	}

void GameEngine::issueOrdersPhase(bool isTournament){

	bool gameIsNotDone = true;
	cout << "\nISSUING ORDERS PHASE" <<endl;
	transition("issueorder");
	cout << "the current state is: " << gameLoop->getCurrentState()->getLabel() << endl;

// Start game loop
for (int i = 0; i < players.size(); i++) {
	if (players[i]->getPlayerTerritories().empty()) {
		cout << players[i]->getName() << " cannot play because they have no territories!";
		continue;
	}
    // Print which player's turn it is
    cout << "\n*** " << players[i]->getName() << "'s turn! ***" << endl;
    // Debugging output to check the value of ps before setting it
	
    // cout << "ps before setting: " << players[i]->getStrategy() << endl;

    // Call the issueOrder method for the current player
    // players[i]->issueOrder(players, i);
    // Ask the user to select a strategy type for the current player

	// if (ps != nullptr) {
	// 			// Check if the player already has a strategy object
	// 			if (players[i]->getStrategy() != nullptr) {
	// 				// Delete the old strategy object
	// 				delete players[i]->getStrategy();
	// 				players[i]->setStrategy(nullptr);
	// 			}
	// 			}
	if (!isTournament) {
		PlayerStrategy* ps;
		
		cout << "\nEnter strategy type (human, aggressive, benevolent, neutral, or cheater): \n";
		cout << "Player " << i + 1 << "'s strategy " << "("<< players[i]->getName() << "): \n" << endl;
		string strategyType;
		cin >> strategyType;
	
		// Set the current player's strategy based on the user's input
		if (strategyType == "aggressive") {
			ps = new AggressivePlayerStrategy(players[i]);
			ps->setName("aggressive");
		}
		else if (strategyType == "neutral") {
			ps = new NeutralPlayerStrategy(players[i]);
			ps->setName("neutral");
		}
		else if (strategyType == "cheater") {
			ps = new CheaterPlayerStrategy(players[i]);
			ps->setName("cheater");
		}
		else if (strategyType == "benevolent") {
			ps = new BenevolentPlayerStrategy(players[i]);
			ps->setName("benevolent");
		}
		else if (strategyType == "human") {
			ps = new HumanPlayerStrategy(players[i]);
			ps->setName("human");
			players[i]->isHumanStrategy = true;
		}
		else {
			// handle invalid strategy type input
			cout << "INVALID stategy";
			continue;

		}


		players[i]->setStrategy(ps);
	}		

	
	// Print which strategy was selected for the current player
	cout << "\nPlayer " << i + 1 << "'s strategy: " << players[i]->ps->getName() << endl;
	// Call the issueOrder method for the current player's strategy
	players[i]->ps->issueOrder(players);
	// Print that the current player's turn is completed
	cout << "\n*** " << players[i]->getName() << "'s turn is complete. ***\n" << endl;
	if (!isTournament) {
		players[i]->setStrategy(nullptr);
	}
		if (players[i]->getPlayerTerritories().size() >= ALL_TERRITORIES){
			cout << players[i]->getName() << " owns all territories!\n" << endl;
				gameIsNotDone = false; 
				break;
			}

	}
// Print that the issuing phase is complete
cout<<"Finished issuing phase..." << endl;

transition("issueordersend");
cout << "the current state is: " << gameLoop->getCurrentState()->getLabel() << endl;


}

void GameEngine::executeOrdersPhase(bool isTournament){
	
	cout << "\nEXECUTING ORDERS PHASE" <<endl;
	transition("execorder");
	int max = 0;    // Stores highest order count among players

    // Iterate through highest order count
    for (int i = 0; i < players.size(); i++){ 
		if (players[i]->getPlayerTerritories().empty()) {
			cout << players[i]->getName() << " cannot play because they have no territories!";
			continue;
		}
			if (players[i]->getPlayerTerritories().size() >= ALL_TERRITORIES){
				if (isTournament) {
					transition("replay");
					return;
				}
				transition("win");
				cout << "GAME OVER. Would you like to quit or replay?" << endl;
				string answer;
				cin >> answer;
				if (answer == "quit"){
				transition("quit");
				}
				else if (answer == "replay"){
				transition("replay");
				}
				else{
				cout << "Invalid choice." << endl;
				}
				return;

			} else {
				if (players[i]->isHumanStrategy){
					// Iterate through player count
					int sizeOrders = players[i]->myOrders->vectorOfOrders.size();
						while (sizeOrders > 0) {
							// Execute highest priority order (if not empty)
							cout << players[i]->myOrders->vectorOfOrders[0]->getOrderEffect();
							players[i]->myOrders->vectorOfOrders[0]->execute(players[i]);    
							cout << players[i]->myOrders->vectorOfOrders[0]->getOrderEffect() << endl;
							sizeOrders = players[i]->myOrders->vectorOfOrders.size();
							//cout<<players[i]->myOrders->vectorOfOrders.size();
							players[i]->myOrders->remove(0); //remove order
							break;

							}
					}
			}
				

	}
		 transition("endexecorders");

}

void GameEngine::reinforcementPhase(){ // reinforcment phase implementation
cout << "\nREINFORCEMENT PHASE" <<endl;
for (int i = 0; i < players.size(); i++) {
	if (players[i]->getPlayerTerritories().empty()) {
		cout << players[i]->getName() << " cannot play because they have no territories!";
		continue;
	}
    cout << "\nPlayer " << i + 1 << "'s territories "  << "("<< players[i]->getName() << "): \n"<< endl; // output players territories

	// 
	map<string, set<Territory*>> continentTerritories;
        
        for (Territory* territory : players[i]->getPlayerTerritories()) { //get players territories
            cout << territory->getName() << " (" << territory->getArmy() << " armies)"<< endl;
            
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
            } else if (continentName != firstContinentName) { //breaks at the first occurance of a different continent
                sameContinent = false;
                break;
            }
}
		if (sameContinent) {
            cout << "All territories are in the same continent: " << firstContinentName << endl;

        } else {
            cout << "Territories are in different continents." << endl;
        }


    cout << "Player " << i + 1 <<   " (" << players[i]->getName() << ") " << "number of territories: "  << players[i]->getPlayerTerritories().size() << endl;
	int numberTerritories = players[i]->getPlayerTerritories().size(); //get number of territories
	int currentArmies = players[i]->getArmy();
	cout << "current player armies " << currentArmies << endl;
	players[i]->setArmy(numberTerritories/3 + currentArmies); // assign number of armies
	cout << "Player " << i + 1 <<   " (" << players[i]->getName() << ") " << "number of armies: "  << players[i]->getArmy() << endl;
}
}

// TOURNAMENT CLASS
// Singleton implementation

Tournament *Tournament::singletonInstance;

Tournament::Tournament() {}
Tournament::Tournament(Map** maps, Player** players, int games, int turns) {
	copy(maps, maps + 5, this->maps);
	copy(players, players + 4, this->players);

	numberOfMaps = 0;
	for (int i = 0; i < 5; i++) {
		if (this->maps[i] != NULL) {
			numberOfMaps++;
		}
	}

	numberOfPlayers = 0;
	for (int i = 0; i < 4; i++) {
		if (this->players[i] != NULL) {
			numberOfPlayers++;
		}
	}

	results = new string*[numberOfMaps];
	for (int i = 0; i < numberOfMaps; i++) {
		results[i] = new string[games];
	}

	this->games = games;
	this->turns = turns;

	delete[] maps;
	delete[] players;
}

Tournament::~Tournament() {
	for (Player* player : players) {
		delete player;
	}
	for (int i = 0; i < numberOfMaps; i++) {
		delete[] results[i];
	}
	delete[] results;
}

bool Tournament::newTournament(string* mapStrings, Player** players, int games, int turns) {
	Map** maps = new Map*[5]();
	MapLoader* mapLoader = new MapLoader();

	// Turn strings into maps. Return error if a map doesn't exist or is invalid
	for (int i = 0; i < 5; i++) {
		if (mapStrings[i] != "") {
			Map* newMap = mapLoader->loadMap(mapStrings[i]);
			newMap->validate();
			if (!newMap->getIsValid()) {
				delete[] mapStrings;
				delete[] maps;
				delete[] players;
				return false;
			}
			maps[i] = newMap;
		}
	}
	delete[] mapStrings;

	// Instantiate singleton
	delete singletonInstance;
	singletonInstance = new Tournament(maps, players, games, turns);
	cout << *singletonInstance << endl;
	return true;
}

Tournament* Tournament::instance() {
	return singletonInstance;
}

void Tournament::runTournament() {
	// Add all players to game engine
	for (int i = 0; i < numberOfPlayers; i++) {
		if (players[i] != NULL) {
			GameEngine::instance()->addPlayer(players[i]);
		}
	}

	// Run every game
	for (int i = 0; i < numberOfMaps; i++) { // On every map
		for (int j = 0; j < games; j++) { // -G times
			cout << "MAP " << *maps[i] << " -- GAME " << j + 1 << endl;
			tournamentStartupPhase(i);
			tournamentGameLoop(i, j);
		}
	}

	// Print results
	printResults();
}

void Tournament::tournamentStartupPhase(int mapNumber) {
	// Game engine and map setup
	maps[mapNumber]->reset();
	for (int i = 0; i < numberOfPlayers; i++) {
		players[i]->clearPlayerTerritories();
	}
	GameEngine::instance()->reset();
	GameEngine::instance()->transition("loadmap");
	GameEngine::instance()->transition("validatemap");
	GameEngine::instance()->transition("addplayer");
	
	cout << "\nYou have selected " << numberOfPlayers << " players: " << endl;
	for (int i = 0; i < numberOfPlayers; i++) {
		cout << "\nPlayer " << i + 1 << ": " << players[i]->getName() << "\n" << endl;
	}

	// a) fairly distribute all the territories to the players

	// get all territories from the map and put them into the vector
	vector<Territory*> territories = maps[mapNumber]->getTerritories();

	// shuffle the vector to randomize the order of the territories
	auto randomSeed = std::mt19937(std::random_device{}());
	std::shuffle(territories.begin(), territories.end(), randomSeed);

	//distribute variable calculates how many territories to give each player
	// total number of territories divided by total number of players = how many territories each player recieves 
	int distribute = territories.size() / numberOfPlayers;

	//for loop to iterate through each player
	for (int i = 0; i < numberOfPlayers; i++) {
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
	cout << "Number of Players: " << numberOfPlayers << endl;
	cout << "When equally distributing the territories, each player will have: " << distribute << " territories." << endl;

	// print each player's territories
	for (int i = 0; i < numberOfPlayers; i++) {
		cout << "\nPlayer " << i + 1 << "'s territories " << "(" << players[i]->getName() << "): \n" << endl;
		for (int j = 0; j < players[i]->getPlayerTerritories().size(); j++) {
			cout << j + 1 << ". " << players[i]->getPlayerTerritories()[j]->getName() << endl;
		}
		cout << endl;
	}
	cout << "----------------------------------------------\n" << endl;

	// b) determine randomly the order of play of the players in the games 
	cout << "----------------------------------------------\n" << endl;

	// randomize the order of the territories
	vector<Player*> order(numberOfPlayers);
	// Shuffle the order of players randomly
	//std::shuffle(players.begin(), players.end(), randomSeed);


	// print the player order
	cout << "Player Order: \n";
	for (int i = 0; i < numberOfPlayers; i++) {
		cout << "Player " << i + 1 << ": " << players[i]->getName() << "\n";
	}
	cout << endl;


	// c) give 50 initial armies to the players, which are placed in their respective reinforcement pool 
	cout << "----------------------------------------------\n" << endl;

	cout << "Initial Armies: \n";
	for (int i = 0; i < numberOfPlayers; i++) {
		players[i]->setArmy(50);
		cout << "Player " << i + 1 << " (" << players[i]->getName() << "): " << players[i]->getArmy() << "\n";
	}
	cout << "\n";


	// d) get each player draw 2 initial cards from the deck using the deck’s draw() method 
	cout << "----------------------------------------------\n" << endl;

	//set hand size to 2
	const int HAND_SIZE = 5;
	//initialize and fill deck
	Deck myDeck;
	myDeck.fillDeck(20);

	//for loop to iterate through player.size
	for (int i = 0; i < numberOfPlayers; i++)
	{
		//create a new hand for each player
		Hand* hand = new Hand();
		OrdersList* ordersList = new OrdersList();
		players[i]->myOrders = ordersList;
		players[i]->myHand = hand;

		//for loop to iterate through hand.size
		for (int j = 0; j < HAND_SIZE; j++)
		{
			//draws card from the deck and gives it to the player's hand
			players[i]->myHand->handCards.push_back(myDeck.draw());
		}
	}
	//loop to print out player's hand
	for (int i = 0; i < numberOfPlayers; i++)
	{
		cout << "Player " << i + 1 << "'s hand " << "(" << players[i]->getName() << "): \n" << endl;
		for (int j = 0; j < players[i]->myHand->handCards.size(); j++)
		{
			cout << players[i]->myHand->handCards[j] << endl;
		}
		cout << endl;
	}

	// e) switch the game to the play phase
	if (GameEngine::instance()->transition("gamestart"))
	{
		cout << "Game has switched to Play Phase." << endl;
	}
}

void Tournament::tournamentGameLoop(int mapNumber, int gameNumber) {
	int i = 0;
	bool gameNotDone = true;

	while (i < turns && gameNotDone) {
		cout << "TURN " << i + 1 << endl;
		GameEngine::instance()->reinforcementPhase();
		GameEngine::instance()->issueOrdersPhase(true);
		GameEngine::instance()->executeOrdersPhase(true);
		
		for (auto p : players) {
			if (p != NULL && p->getPlayerTerritories().size() >= ALL_TERRITORIES) {
				results[mapNumber][gameNumber] = p->getStrategy()->getName();
				gameNotDone = false;
			}
		}
		i++;
	}

	if (results[mapNumber][gameNumber] == "") {
		results[mapNumber][gameNumber] = "Draw";
	}
}

void Tournament::printResults() {
	cout << "\t\t";
	for (int j = 0; j < games; j++) {
		cout << "Game " << j << "\t\t";
	}
	cout << endl;
	for (int i = 0; i < numberOfMaps; i++) {
		cout << maps[i]->getName();
		int tabs = 2 - (int)(maps[i]->getName().length() / 8);
		for (int k = 0; k < tabs; k++) {
			cout << "\t";
		}

		for (int j = 0; j < games; j++) {
			cout << results[i][j];
			tabs = 2 - (int)(results[i][j].length() / 8);
			for (int k = 0; k < tabs; k++) {
				cout << "\t";
			}
		}

		cout << endl;
	}
}

ostream& operator<<(ostream& out, Tournament& tournament) {
	out << "Tournament Mode:" << endl;
	out << "M: " << *tournament.maps[0];
	for (int i = 1; i < 5; i++) {
		if (tournament.maps[i] != NULL) {
			out << ", " << *tournament.maps[i] << endl;
		}
	}
	out << endl << "P: " << tournament.players[0]->getStrategy()->getName();
	for (int i = 1; i < 4; i++) {
		if (tournament.players[i] != NULL) {
			out << ", " << tournament.players[i]->getStrategy()->getName();
		}
	}
	out << endl << "G: " << tournament.games << endl;
	out << "D: " << tournament.turns << endl;
	return out;
}