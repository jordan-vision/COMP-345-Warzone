#include "LoggingObserver.h"
#include "CommandProcessing.h"
#include "Orders.h"
#include "GameEngine.h"
using namespace std;

int main() {
	
    Command* myCommand = new Command();
    CommandProcessor* myCommandProcessor = new CommandProcessor();
    OrdersList* myOrders = new OrdersList();
    GameEngine* myEngine = new GameEngine();

    Deploy* d = new Deploy();
    Advance* a = new Advance();
    Blockade* bl = new Blockade();
    Bomb* bo = new Bomb();
    Airlift* ar = new Airlift();
    Negotiate* n = new Negotiate();

   
    myCommand->saveEffect();
    myCommandProcessor->saveCommand();
    myOrders->add(d);
    myOrders->add(a);
    myOrders->add(bl);
    myOrders->add(bo);
    myOrders->add(ar);
    myOrders->add(n);
    
    d->execute();
    a->execute();
    bl->execute();
    bo->execute();
    ar->execute();
    n->execute();

    while (!myEngine->getIsGameOver()) {
		string input;
		cout << "Enter a command: ";
		cin >> input;
		myEngine->transition(input);
	}

	return 0;
};