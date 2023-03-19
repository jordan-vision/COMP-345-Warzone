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
    // GameEngine* myEngine = new GameEngine();
    GameEngine::reset()

    MapLoader* loader = new MapLoader();
    Map* map5 = loader->loadMap("europe.map");      
    map5->validate();

    // Prints territories of a continent in map 5 - europe.map
    for(auto continent: map5->getContinents()){
        cout<<"\nContinent "<<*continent<<" has territories: "<<endl;
        for(auto territory: continent->getTerritories()){
            cout<<*territory<<endl;
        }
    }


    // Deploy* d = new Deploy();
    // Advance* a = new Advance();
    // Blockade* bl = new Blockade();
    // Bomb* bo = new Bomb();
    // Airlift* ar = new Airlift();
    // Negotiate* n = new Negotiate();

   
    // myCommand->saveEffect();
    // myCommandProcessor->saveCommand();
    // myOrders->add(d);
    // myOrders->add(a);
    // myOrders->add(bl);
    // myOrders->add(bo);
    // myOrders->add(ar);
    // myOrders->add(n);
    
    // d->execute();
    // a->execute();
    // bl->execute();
    // bo->execute();
    // ar->execute();
    // n->execute();

    while (!GameEngine::getIsGameOver()) {
		string input;
		cout << "Enter a command: ";
		cin >> input;
		GameEngine::transition(input);
	}

	return 0;
};