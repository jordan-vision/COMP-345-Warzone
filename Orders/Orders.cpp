#include <string>
#include <iostream>
#include <typeinfo>
#include "Orders.h"

OrdersList::OrdersList() {
	vector<Order*> vectorOfOrders;
}

OrdersList::OrdersList(OrdersList& copy){
}

//OrdersList::printOrdersList(){
	// for (const auto &vec : vec) {
    //     cout << typeid(&vec).name() << " ";
    // }
    // cout << endl;
//}

void OrdersList::printOrdersList(const vector<Order*> &vec){
	for (const auto &vec : vec) {
        cout << "the element is: " << endl;
		cout << typeid(&vec).name() << " ";
    }
    cout << endl;
}

Order::Order()
{
}

Order::Order(Order& copy){

}

string Order::getDescription(){
	return "When the turn-based main play phase begins, players are creating a set of battle orders. After all the orders have been given for all players for a turn, they are executed by the game engine: The orders are 1) deployment orders, 2) advance orders, 3) special orders resulting from using cards";
}

ostream& operator<<(ostream &out, Order& o) { //display effect of Order
	out << "~Order description:~";
	out << o.getDescription(); 
}


//==================== Deploy ======================
Deploy::Deploy(){ //contructor
}

Deploy::Deploy(Deploy& copy){ //copy constructor
}

Deploy& Deploy::operator=(const Deploy& a){ //assignment operator

}

void Deploy::execute(){
	if (Deploy::validate()){ //validate the order
		// deploy armies
	}else{
		//display error message or whatever has to happen
	}
}

bool Deploy::validate(){
	return true; 
}

string Deploy::getDescription() 
{
	return "Place some armies on one of the current players territories";
}

ostream& operator<<(ostream &out, Deploy& d) {
	out << ""; 
}


//==================== Advance ======================
Advance::Advance(){

}

Advance::Advance(Advance& copy){

}

Advance& Advance::operator=(const Advance& a){ //assignment operator

}

void Advance::execute(){
	if (Advance::validate()){ //validate the order
		//advance armies
	}else{
		//display error message or whatever has to happen
	}
}
bool Advance::validate(){
}

string Advance::getDescription()
{
	return "move some armies from one of the current players territories (source) to an adjacent territory (target). If the target territory belongs to the current player, the armies are moved to the target territory. If the target territory belongs to another player, an attack happens between the two territories.";
}

ostream& operator<<(ostream &out, Advance& a) {
	out << ""; 
}


//==================== Bomb ======================
Bomb::Bomb(){

}

Bomb::Bomb(Bomb& b){

}

Bomb& Bomb::operator=(const Bomb& a){ //assignment operator

}

void Bomb::execute(){
	if (Bomb::validate()){ //validate the order
		//bomb area
	}else{
		//display error message or whatever has to happen
	}
}
bool Bomb::validate(){
}

string Bomb::getDescription(){
	return "destroy half of the armies located on an opponents territory that is adjacent to one of the current players territories.";
}

ostream& operator<<(ostream &out, Bomb& b) {
	out << ""; 
}


//==================== Blockade ======================
Blockade::Blockade(){

}

Blockade::Blockade(Blockade& b){

}

Blockade& Blockade::operator=(const Blockade& b){ //assignment operator

}

void Blockade::execute(){
	if (Blockade::validate()){ //validate the order
		//put up a blockade
	}else{
		//display error message or whatever has to happen
	}
}
bool Blockade::validate(){
}

string Blockade::getDescription(){
	return "triple the number of armies on one of the current players territories and make it a neutral territory.";
}

ostream& operator<<(ostream &out, Blockade& bk) {
	out << ""; 
}


//==================== Airlift ======================
Airlift::Airlift(){

}
Airlift::Airlift(Airlift& a){

}

Airlift& Airlift::operator=(const Airlift& a){ //assignment operator

}

void Airlift::execute(){
	if (Airlift::validate()){ //validate the order
		//do an airlift
	}else{
		//display error message or whatever has to happen
	}
}
bool Airlift::validate(){
}

string Airlift::getDescription(){
	return "advance some armies from one of the current players territories to any another territory.";
}

ostream& operator<<(ostream &out, Airlift& ar) {
	out << ""; 
}


//==================== Negotiate ======================
Negotiate::Negotiate(){

}

Negotiate::Negotiate(Negotiate& n){

}

Negotiate& Negotiate::operator=(const Negotiate& a){ //assignment operator

}

void Negotiate::execute(){
	if (Negotiate::validate()){ //validate the order
		//negotiate with player
	}else{
		//display error message or whatever has to happen
	}
}
bool Negotiate::validate(){
}

string Negotiate::getDescription(){
	return "prevent attacks between the current player and another player until the end of the turn.";
}

ostream& operator<<(ostream &out, Negotiate& n) {
	out << ""; 
}

