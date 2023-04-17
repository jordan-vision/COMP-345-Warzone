#include <string>
#include <iostream>
#include <typeinfo>
#include "Orders.h"
#include <limits>
/* -------------------------------------------------------------------------- */
/*                              OrdersList Class                              */
/* -------------------------------------------------------------------------- */

OrdersList::OrdersList() { // default constructor  
}

OrdersList::OrdersList(OrdersList& copy){ // copy constructor
    this->vectorOfOrders = vector <Order*> ();
	for (auto order = copy.vectorOfOrders.begin(); order != copy.vectorOfOrders.end(); order++) {
		vectorOfOrders.push_back(*order);
	}
}

OrdersList& OrdersList::operator=(const OrdersList& ol) { // assignment operator
	for (auto order = ol.vectorOfOrders.begin(); order != ol.vectorOfOrders.end(); order++) {
		vectorOfOrders.push_back(*order);
	}
	return *this;
}

ostream& operator<<(ostream &out, OrdersList& o) { //displays description and effect of Order
	int counter = 0;
	cout << "Printing List of Orders..." << endl;
	for (const auto o : o.vectorOfOrders) {
		string str = typeid(*o).name();
        cout << "The order at position " << counter << " in the list of orders is : " << str.substr(1) << " " << endl;
		counter++;
    }
	cout << endl;
	return out;
}

void OrdersList::add(Order* o) { 
	cout<< "Order added"<<endl;
	vectorOfOrders.push_back(o); 
	//Notify(o);
}

void OrdersList::remove(int i) // removes order at position i
{ 
	cout << "Erasing order at position" << i << "..." << endl;
	cout << endl;
	delete vectorOfOrders[i];
	vectorOfOrders.erase(vectorOfOrders.begin() + i); 
	
}

void OrdersList::move(int from, int to) { // moves order from position <from> to position <to>
	cout << "Moving order from position " << from << " to position " << to << endl;
	cout << endl;
	swap(vectorOfOrders[from], vectorOfOrders[to]);
}

OrdersList::~OrdersList() { // destructor
    for (Order* order : vectorOfOrders){
        delete order;    
		order = nullptr;
	}
	delete this;
};

string OrdersList::stringToLog() {

	return "Order Issued: ...";
};


/* -------------------------------------------------------------------------- */
/*                                 Order Class                                */
/* -------------------------------------------------------------------------- */

Order::Order() // default constructor
{
	orderEffect = "Order has been placed on order list. Nothing happened yet\n";
}

Order::Order(Order& copy){ // copy constructor
	orderEffect = copy.orderEffect;
}

string Order::getOrderEffect(){ // getter for orderEffect 
	return orderEffect;
}

ostream& operator<<(ostream &out, Order& o) { //displays description and effect of Order
	string str = typeid(o).name();
	cout << "Here is information for order of type " << str.substr(1) << ":" << endl;
	out << "--- Order description: ---" << endl;
	out << o.getDescription() << endl; 
	out << "--- Order Effect: ---" << endl;
	out << o.getOrderEffect() << endl;
	return out;
}

Order::~Order() // default constructor
{
	delete this;
}

string Order::stringToLog() {

	return "Order Executed: ...";
};

void Order::execute(Player* player) {

    Notify(this);

}

/* -------------------------------------------------------------------------- */
/*                                Deploy Class                                */
/* -------------------------------------------------------------------------- */

Deploy::Deploy(Territory* target, int numberOfArmies){ //contructor
	this->target = target;
	this->numberOfArmies = numberOfArmies;
}

Deploy::Deploy(Deploy& copy){ //copy constructor
	orderEffect = copy.orderEffect;
}

Deploy& Deploy::operator=(const Deploy& d){ //assignment operator
	orderEffect = d.orderEffect;
	return *this;
}

void Deploy::execute(Player* player){
	if (Deploy::validate(player)) { 
		// int reinforcementAmount = 0;
    	// while (true) {
		// 	cout << "\nPlayer " << player->getName() << "'s turn: " << endl;
    	//     cout << "How many reinforcements do you wish to send ( 1 - " << player->getArmy() << " )?";

    	//     if (!(cin >> reinforcementAmount)) {

    	//         cin.clear();
    	//         cin.ignore(numeric_limits<streamsize>::max(), '\n');
    	//         cout << "Invalid input: Please try again!" << endl;

    	//     } else if (reinforcementAmount < 1 || reinforcementAmount > player->getArmy()) 
    	//         cout << "Invalid Input: Please try again!" << endl;
    	//     else 
				
    	//         break;
    	// } // end of while loop
		
		this->target->setArmy(this->target->getArmy() + numberOfArmies);
		player->setArmy(player->getArmy()-numberOfArmies);
		orderEffect = "Armies have been placed on players territories"; 


    } else 
		orderEffect = "Unable to Deploy armies";
	
}

bool Deploy::validate(Player* player){
	
	// Check ownership of target territory
	if (this->target->getOwner()->getName() == player->getName()) {
		
		if (player->getArmy() != 0) // Check if reinforcement pool is empty
			return true;
		else 
			cout << "There are no reinforcements available!";
	} else 
		cout << "Invalid Order: Player does not own target territory!";
	
	return false;
}

string Deploy::getDescription() 
{
	return "The Deploy order places some armies on one of the current players territories";
}

Deploy::~Deploy(){
}

/* -------------------------------------------------------------------------- */
/*                                Advance Class                               */
/* -------------------------------------------------------------------------- */

Advance::Advance(Territory* target, Territory* source, int units){
	this->target = target;
	this->source = source; 
	this->units = units; 
}

Advance::Advance(Advance& copy){ // copy constructor 
	orderEffect = copy.orderEffect;
}

Advance& Advance::operator=(const Advance& a){ //assignment operator
	orderEffect = a.orderEffect;
	return *this;
}

void Advance::execute(Player* player){

	if (Advance::validate(player)) { //validate the order
		Player* enemy = target->getOwner();

		        if (player->getStrategy()->getName() == "human"){
					player->removeCardOfTypeFromHand(player, CardType::Reinforcement);
				}

		if (this->target->getOwner()->getName() == player->getName()){
			source->setArmy(source->getArmy() - units);
			target->setArmy(target->getArmy() + units);
			cout<< "Target territory belongs to you." << endl;
			cout<< *source << " is now advancing "<<units<<" units to territory "<<*target<<endl;
			orderEffect = "Advanced armies from one owned territory to another";
			cout << *source << " now has " << source->getArmy() << " armies." << endl;
			cout << *target << " now has " << target->getArmy() << " armies.\n" << endl;


			Notify(this);
		}
		else if (this->target->getOwner()->getName() != player->getName()){

			int attacking = units;
			int defending = target->getArmy();
			enemy->setIsAttacked(true);

			cout<<"\nTarget territory belongs to another player.";
			cout<<"\n" << *source << " has " <<units << " armies and is commencing attack on " << *target << " which has " << target->getArmy() << " armies."<<endl;


			// for each unit in the attacking army, there is a 60 percent chance of victory over
			// each unit in the defending army. Similarly, each defending unit has a 70 percent chance of victory 
			while (attacking != 0 && defending != 0){


				// If the attacking unit defeats the defending unit
				if (rand() % 100 < 60){
					defending = defending-1;
				}

				// If the defending unit defeats the attacking unit 
				if (rand() % 100 < 70 ){
					attacking = attacking-1;
				}

			}

			// If the player conquers this target territory: 
			// Set the new number of army units in the target territory after it has been conquered
			// Erase its previous owner by removing it from their list of territories owned
			// Set it to its new owner (the conqueror)
			if (defending == 0){
			
				// Deleting territory from previous owner's list 
				int indexToDelete = -1;
				for (int i = 0; i < enemy->getPlayerTerritories().size(); i++) {
    				if (enemy->getPlayerTerritories()[i] == target) {
       					 indexToDelete = i;
       					 break;
					}
				}
				vector<Territory*> enemyTerritories = enemy->getPlayerTerritories();


				// Erase the territory pointer from the vector
				enemy->removeTerritory(indexToDelete);
				player->addTerritory(target);
				target->setOwner(player);
				
				cout<<"\n" << player->getName() << ":"<< endl;
				cout << source->getName() << " has defeated " << target->getName()<< ". Target territory conquered. You won the battles.\n";
				target->setArmy(attacking);
				source->setArmy(this->source->getArmy() - units);
				cout << "Ownership of " << target->getName() << " has been changed to " << player->getName() <<  "." << endl;
				cout << "You now own " << target->getName() << " with " << target->getArmy() <<  " armies on it.\n" << endl;

				// give the player a card since they conquered a territory
				//player->myHand->handCards.push_back(myDeck->draw());
				
			// If the attacking army is defeated. Meaning, the target territory has not been conquered
			} else { 


					// Deleting territory from previous owner's list 
				int indexToDelete = -1;
				for (int i = 0; i < player->getPlayerTerritories().size(); i++) {
    				if (player->getPlayerTerritories()[i] == target) {
       					 indexToDelete = i;
       					 break;
					}
				}
				vector<Territory*> playerTerritories = player->getPlayerTerritories();


				// Erase the territory pointer from the vector
				player->removeTerritory(indexToDelete);
				enemy->addTerritory(target);
				target->setOwner(enemy);

				cout <<"\n" << player->getName() << ":" << endl;
				cout << target->getName() << " has defeated " << source->getName()<< ". Source territory conquered. You lost the battle.\n";
				this->source->setArmy(this->source->getArmy() - this->units);
				this->target->setArmy(defending);
				cout << "You no longer own " << source->getName() << "." << endl;
				cout << "Ownership of  " << source->getName() << " has been changed to " << enemy->getName() <<  "." << endl;
				cout << enemy->getName() << " now owns: " <<source->getName() << " with " << source->getArmy() <<  " armies on it.\n" << endl;
			}

			orderEffect = "Attacked with armies from owned territory to enemy territory";
			Notify(this);
		}
		
	}else{
		//display error message or whatever has to happen
		orderEffect = "Unable to Advance armies";
	}
}

bool Advance::validate(Player* player){

	if (this->source->getOwner()->getName() != player->getName()){
		cout<<"\nTerritory does not belong to player"<<endl;
		return false; 

	} else {
		for (auto it: this->source->getAdjacentTerritories()){
			if (it->getName() == target->getName()){
				return true;
			} 
		}
		cout<<"\nTarget territory is not adjacent"<<endl;
		return false; 
	}
}

string Advance::getDescription()
{
	return "The Advance order moves some armies from one of the current players territories (source) to an adjacent territory (target). If the target territory belongs to the current player, the armies are moved to the target territory. If the target territory belongs to another player, an attack happens between the two territories.";
}

Advance::~Advance(){
}


/* -------------------------------------------------------------------------- */
/*                                 Bomb Class                                 */
/* -------------------------------------------------------------------------- */

Bomb::Bomb(Territory* target){
	this->target = target;
}

Bomb::Bomb(Bomb& copy){ // copy constructor
	orderEffect = copy.orderEffect;
}

Bomb& Bomb::operator=(const Bomb& b){ //assignment operator
	orderEffect = b.orderEffect;
	return *this;
}

void Bomb::execute(Player* player){

	if (Bomb::validate(player)){ //validate the order

		this->target->setArmy(this->target->getArmy() / 2);
		cout << "The target territory has been bombed (half the army is gone)"; 
		//bomb area
		orderEffect = "Destroyed half of the armies located on the opponents territory";
		player->removeCardOfTypeFromHand(player, CardType::Bomb);
		Notify(this);

	} else 
		orderEffect = "Invalid Order: Player owns target territory!";
	
}

bool Bomb::validate(Player* player) {

	// Check ownership of target territory
	if (this->target->getOwner()->getName() != player->getName()) 
		// Iterate through owned territories
		for (Territory* pTerritory : player->getPlayerTerritories()) 
			// Iterate through adjacent territories 
			for (Territory* adjTerritory : pTerritory->getAdjacentTerritories()) 
				// Check target territory is adjacent
				if (adjTerritory->getName() == this->target->getName()) 
					return true;
	return false;
}

string Bomb::getDescription(){
	return "The Bomb order destroys half of the armies located on an opponents territory that is adjacent to one of the current players territories.";
}

Bomb::~Bomb(){

}


/* -------------------------------------------------------------------------- */
/*                               Blockade Class                               */
/* -------------------------------------------------------------------------- */

Blockade::Blockade(Territory* target){
	this->target=target;
}

Blockade::Blockade(Blockade& copy){ // copy constructor
	orderEffect = copy.orderEffect;

}

Blockade& Blockade::operator=(const Blockade& b){ //assignment operator
	orderEffect = b.orderEffect;
	return *this;
}

void Blockade::execute(Player* player){

	if (Blockade::validate(player)) { 

		this->target->setArmy(this->target->getArmy() * 2);


		// IMPLEMENT: give ownership to neutralPlayer
		//target->setOwner(); 

		orderEffect = "Blockaded the territory. Territory is now a neutral zone";
		player->removeCardOfTypeFromHand(player, CardType::Blockade);
		Notify(this);



	} else
		orderEffect = "Invalid Order: Player does not own target territory!";
	
}
bool Blockade::validate(Player* player){

	if (this->target->getOwner()->getName() == player->getName()) 
		return true;
	
	return false; 
}

string Blockade::getDescription(){
	return "The Blockade order triples the number of armies on one of the current players territories and makes it a neutral territory.";
}

Blockade::~Blockade(){

}

/* -------------------------------------------------------------------------- */
/*                                Airlift Class                               */
/* -------------------------------------------------------------------------- */

Airlift::Airlift(Territory* target, Territory* source, int units){
	this->target = target;
	this->source = source;
	this->units = units;
}
Airlift::Airlift(Airlift& copy){ // copy constructor
	orderEffect = copy.orderEffect;
}

Airlift& Airlift::operator=(const Airlift& a){ //assignment operator
	orderEffect = a.orderEffect;
	return *this;
}

void Airlift::execute(Player* player) {
	
	if (Airlift::validate(player)){ 
		
		this->source->setArmy(this->source->getArmy() - this->units);
		this->target->setArmy(this->target->getArmy() + this->units);

		orderEffect = "Airlifted armies from one territory to another";
		player->removeCardOfTypeFromHand(player, CardType::Airlift);
		Notify(this);

	}else{
		//display error message or whatever has to happen
		orderEffect = "Unable to perform Airlift";
	}
}
bool Airlift::validate(Player* player){

	if (this->target->getOwner()->getName() == player->getName())
		if (this->source->getOwner()->getName() == player->getName())
			return true; 
	return false;
}

string Airlift::getDescription(){
	return "The Airflift order advances some armies from one of the current players territories to any another territory.";
}

Airlift::~Airlift(){

}

/* -------------------------------------------------------------------------- */
/*                               Negotiate Class                              */
/* -------------------------------------------------------------------------- */

Negotiate::Negotiate(Player* player){
	this->target = target;
}

Negotiate::Negotiate(Negotiate& copy){ //copy constructor 
	orderEffect = copy.orderEffect;
}

Negotiate& Negotiate::operator=(const Negotiate& n){ //assignment operator
	orderEffect = n.orderEffect;
	return *this;
}

void Negotiate::execute(Player* player){

	if (Negotiate::validate(player)){ //validate the order
	
		// CREATE TRUCE VARIABLE FOR PLAYERS
		orderEffect = "Negotiations performed. Attacks have been prevented until the end of turn";
		player->removeCardOfTypeFromHand(player, CardType::Diplomacy);
		Notify(this);
	}else{
		//display error message or whatever has to happen
		orderEffect = "Unable to Negotiate";
	}
}
bool Negotiate::validate(Player* player){

	if (this->target->getOwner()->getName() != player->getName())
		return true;
	return false; 
}

string Negotiate::getDescription(){
	return "The Negotiate order prevents attacks between the current player and another player until the end of the turn.";
}

Negotiate::~Negotiate(){

}
