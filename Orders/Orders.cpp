#include <string>
#include <iostream>
#include <typeinfo>
#include "Orders.h"

/* -------------------------------------------------------------------------- */
/*                              OrdersList Class                              */
/* -------------------------------------------------------------------------- */

OrdersList::OrdersList() {
	vector<Order*> vectorOfOrders;
}

OrdersList::OrdersList(OrdersList& copy){
}

void OrdersList::printOrdersList(){
	int counter = 0;
	cout << "Printing List of Orders..." << endl;
	for (const auto o : vectorOfOrders) {
        cout << "The order at position " << counter << " in the list of orders is : " << typeid(*o).name() << " " << endl;
		counter++;
    }
	cout << endl;
}

void OrdersList::remove(int i) 
{ 
	cout << "Erasing order at position " << i << "..." << endl;
	cout << endl;
	vectorOfOrders.erase(vectorOfOrders.begin() + i); 
}

void OrdersList::move(int from, int to) { 
	cout << "Moving order from position " << from << " to position " << to << endl;
	cout << endl;
	swap(vectorOfOrders[from], vectorOfOrders[to]);
}


/* -------------------------------------------------------------------------- */
/*                                 Order Class                                */
/* -------------------------------------------------------------------------- */

Order::Order()
{
	orderEffect = "Order has been placed on order list. Nothing happened yet";
}

Order::Order(Order& copy){
	orderEffect = copy.orderEffect;
}

string Order::getOrderEffect(){
	return orderEffect;
}

ostream& operator<<(ostream &out, Order& o) { //display effect of Order
	cout << "Here is information for order of type " << typeid(o).name() << ":" << endl;
	out << "--- Order description: ---" << endl;
	out << o.getDescription() << endl; 
	out << "--- Order Effect: ---" << endl;
	out << o.getOrderEffect() << endl;
	return out;
}


/* -------------------------------------------------------------------------- */
/*                                Deploy Class                                */
/* -------------------------------------------------------------------------- */

Deploy::Deploy(){ //contructor
}

Deploy::Deploy(Deploy& copy){ //copy constructor
}

Deploy& Deploy::operator=(const Deploy& a){ //assignment operator
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
	return true; 
}

string Deploy::getDescription() 
{
	return "The Deploy order places some armies on one of the current players territories";
}

// ostream& operator<<(ostream &out, Deploy& d) {
// 	out << "Deploy Order"; 
// 	return out;
// }


/* -------------------------------------------------------------------------- */
/*                                Advance Class                               */
/* -------------------------------------------------------------------------- */

Advance::Advance(){

}

Advance::Advance(Advance& copy){

}

Advance& Advance::operator=(const Advance& a){ //assignment operator
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
	return true; // logic to be implemented, currrently returning true for testing purposes 
}

string Advance::getDescription()
{
	return "The Advance order moves some armies from one of the current players territories (source) to an adjacent territory (target). If the target territory belongs to the current player, the armies are moved to the target territory. If the target territory belongs to another player, an attack happens between the two territories.";
}

// ostream& operator<<(ostream &out, Advance& a) {
// 	out << "Advance Order"; 
// 	return out;
// }


/* -------------------------------------------------------------------------- */
/*                                 Bomb Class                                 */
/* -------------------------------------------------------------------------- */

Bomb::Bomb(){

}

Bomb::Bomb(Bomb& b){

}

Bomb& Bomb::operator=(const Bomb& a){ //assignment operator
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
	return true; // logic to be implemented, currrently returning true for testing purposes 
}

string Bomb::getDescription(){
	return "The Bomb order destroys half of the armies located on an opponents territory that is adjacent to one of the current players territories.";
}

// ostream& operator<<(ostream &out, Bomb& b) {
// 	out << "Bomb Order"; 
// 	return out;
// }


/* -------------------------------------------------------------------------- */
/*                               Blockade Class                               */
/* -------------------------------------------------------------------------- */

Blockade::Blockade(){

}

Blockade::Blockade(Blockade& b){

}

Blockade& Blockade::operator=(const Blockade& b){ //assignment operator
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
	return true; // logic to be implemented, currrently returning true for testing purposes 
}

string Blockade::getDescription(){
	return "The Blockade order triples the number of armies on one of the current players territories and makes it a neutral territory.";
}

// ostream& operator <<(ostream &out, const Blockade& bk) {
// 	out << static_cast <const Order&>(bk); 
// 	return out;
// }


/* -------------------------------------------------------------------------- */
/*                                Airlift Class                               */
/* -------------------------------------------------------------------------- */

Airlift::Airlift(){

}
Airlift::Airlift(Airlift& a){

}

Airlift& Airlift::operator=(const Airlift& a){ //assignment operator
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
	return true; // logic to be implemented, currrently returning true for testing purposes 
}

string Airlift::getDescription(){
	return "The Airflift order advances some armies from one of the current players territories to any another territory.";
}

// ostream& operator<<(ostream &out, Airlift& ar) {
// 	out << "Airlift Order"; 
// 	return out;
// }


/* -------------------------------------------------------------------------- */
/*                               Negotiate Class                              */
/* -------------------------------------------------------------------------- */

Negotiate::Negotiate(){

}

Negotiate::Negotiate(Negotiate& n){

}

Negotiate& Negotiate::operator=(const Negotiate& a){ //assignment operator
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
	return true; // logic to be implemented, currrently returning true for testing purposes 
}

string Negotiate::getDescription(){
	return "The Negotiate order prevents attacks between the current player and another player until the end of the turn.";
}

// ostream& operator<<(ostream &out, Negotiate& n) {
// 	out << "Negotiate Order"; 
// 	return out;
// }

