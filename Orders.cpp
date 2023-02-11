#include <string>
#include <iostream>
#include <typeinfo>
#include "Orders.h"

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

OrdersList& OrdersList::operator=(const OrdersList&) {
	for (auto order = ol.vectorOfOrders.begin(); order != ol.vectorOfOrders.end(); order++) {
		vectorOfOrders.push_back(*order);
	}
	return *this;
}

void OrdersList::printOrdersList(){ // prints vector contents 
	int counter = 0;
	cout << "Printing List of Orders..." << endl;
	for (const auto o : vectorOfOrders) {
		string str = typeid(*o).name();
        cout << "The order at position " << counter << " in the list of orders is : " << str.substr(1) << " " << endl;
		counter++;
    }
	cout << endl;
}

void OrdersList::remove(int i) // removes order at position i
{ 
	cout << "Erasing order at position " << i << "..." << endl;
	cout << endl;
	vectorOfOrders.erase(vectorOfOrders.begin() + i); 
}

void OrdersList::move(int from, int to) { // moves order from position <from> to position <to>
	cout << "Moving order from position " << from << " to position " << to << endl;
	cout << endl;
	swap(vectorOfOrders[from], vectorOfOrders[to]);
}

OrdersList::~OrdersList() {
    for (Order* order : vectorOfOrders){
        delete order;    
		order = nullptr;
	}
	delete this;
};


/* -------------------------------------------------------------------------- */
/*                                 Order Class                                */
/* -------------------------------------------------------------------------- */

Order::Order() // default constructor
{
	orderEffect = "Order has been placed on order list. Nothing happened yet";
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

/* -------------------------------------------------------------------------- */
/*                                Deploy Class                                */
/* -------------------------------------------------------------------------- */

Deploy::Deploy(){ //contructor
}

Deploy::Deploy(Deploy& copy){ //copy constructor
	orderEffect = copy.orderEffect;
}

Deploy& Deploy::operator=(const Deploy& d){ //assignment operator
	orderEffect = d.orderEffect;
	return *this;
}

void Deploy::execute(){
	if (Deploy::validate()){ //validate the order
		// deploy armies
		orderEffect = "Armies have been placed on players territories"; 
	}else{
		//display error message or whatever has to happen
		orderEffect = "Unable to Deploy armies";
	}
}

bool Deploy::validate(){
	return true; // TODO: logic to be implemented, currrently returning true for testing purposes 
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

Advance::Advance(){

}

Advance::Advance(Advance& copy){ // copy constructor 
	orderEffect = copy.orderEffect;
}

Advance& Advance::operator=(const Advance& a){ //assignment operator
	orderEffect = a.orderEffect;
	return *this;
}

void Advance::execute(){
	if (Advance::validate()){ //validate the order
		//advance armies
		orderEffect = "Armies have been moved to specified territory"; 
	}else{
		//display error message or whatever has to happen
		orderEffect = "Unable to Advance armies";
	}
}

bool Advance::validate(){
	return true; // TODO: logic to be implemented, currrently returning true for testing purposes  
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

Bomb::Bomb(){

}

Bomb::Bomb(Bomb& copy){ // copy constructor
	orderEffect = copy.orderEffect;
}

Bomb& Bomb::operator=(const Bomb& b){ //assignment operator
	orderEffect = b.orderEffect;
	return *this;
}

void Bomb::execute(){
	if (Bomb::validate()){ //validate the order
		//bomb area
		orderEffect = "Destroyed half of the armies located on the opponents territory";
	}else{
		//display error message or whatever has to happen
		orderEffect = "Unable to Bomb territory";
	}
}

bool Bomb::validate(){
	return true; // TODO: logic to be implemented, currrently returning true for testing purposes 
}

string Bomb::getDescription(){
	return "The Bomb order destroys half of the armies located on an opponents territory that is adjacent to one of the current players territories.";
}

Bomb::~Bomb(){

}


/* -------------------------------------------------------------------------- */
/*                               Blockade Class                               */
/* -------------------------------------------------------------------------- */

Blockade::Blockade(){

}

Blockade::Blockade(Blockade& copy){ // copy constructor
	orderEffect = copy.orderEffect;

}

Blockade& Blockade::operator=(const Blockade& b){ //assignment operator
	orderEffect = b.orderEffect;
	return *this;
}

void Blockade::execute(){
	if (Blockade::validate()){ //validate the order
		//put up a blockade
		orderEffect = "Blockaded the territory. Territory is now a neutral zone";
	}else{
		//display error message or whatever has to happen
		orderEffect = "Unable to Blockade territory";
	}
}
bool Blockade::validate(){
	return true; // TODO: logic to be implemented, currrently returning true for testing purposes 
}

string Blockade::getDescription(){
	return "The Blockade order triples the number of armies on one of the current players territories and makes it a neutral territory.";
}

Blockade::~Blockade(){

}

/* -------------------------------------------------------------------------- */
/*                                Airlift Class                               */
/* -------------------------------------------------------------------------- */

Airlift::Airlift(){

}
Airlift::Airlift(Airlift& copy){ // copy constructor
	orderEffect = copy.orderEffect;
}

Airlift& Airlift::operator=(const Airlift& a){ //assignment operator
	orderEffect = a.orderEffect;
	return *this;
}

void Airlift::execute(){
	if (Airlift::validate()){ //validate the order
		//do an airlift
		orderEffect = "Airlifted armies from one territory to another";
	}else{
		//display error message or whatever has to happen
		orderEffect = "Unable to perform Airlift";
	}
}
bool Airlift::validate(){
	return true; // TODO: logic to be implemented, currrently returning true for testing purposes 
}

string Airlift::getDescription(){
	return "The Airflift order advances some armies from one of the current players territories to any another territory.";
}

Airlift::~Airflift()[

]

/* -------------------------------------------------------------------------- */
/*                               Negotiate Class                              */
/* -------------------------------------------------------------------------- */

Negotiate::Negotiate(){

}

Negotiate::Negotiate(Negotiate& copy){ //copy constructor 
	orderEffect = copy.orderEffect;
}

Negotiate& Negotiate::operator=(const Negotiate& n){ //assignment operator
	orderEffect = n.orderEffect;
	return *this;
}

void Negotiate::execute(){
	if (Negotiate::validate()){ //validate the order
		//negotiate with player
		orderEffect = "Negotiations performed. Attacks have been prevented until the end of turn";
	}else{
		//display error message or whatever has to happen
		orderEffect = "Unable to Negotiate";
	}
}
bool Negotiate::validate(){
	return true; // TODO: logic to be implemented, currrently returning true for testing purposes 
}

string Negotiate::getDescription(){
	return "The Negotiate order prevents attacks between the current player and another player until the end of the turn.";
}

Negotiate::~Negotiate(){
	
}
