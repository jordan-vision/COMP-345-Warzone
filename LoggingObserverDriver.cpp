#include "LoggingObserver.h"
#include "CommandProcessing.h"
#include "Orders.h"
#include "GameEngine.h"
using namespace std;

int main() {
	
    Player player;
    Command* myCommand = new Command();
    CommandProcessor* myCommandProcessor = new CommandProcessor();
    OrdersList* myOrders = new OrdersList();
    GameEngine* myEngine = new GameEngine();
    GameEngine::instance()->reset()


    while (!GameEngine::instance()->getIsGameOver()) {
		string input;
		cout << "Enter a command: ";
		cin >> input;
		GameEngine::instance()->transition(input);
	}

	return 0;
};