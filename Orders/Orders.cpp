#include <string>
#include <iostream>
#include "Orders.h"

OrdersList::OrdersList(OrdersList& copy){
}

ostream& operator<<(ostream &out, Order& o) { //display effect of Order
	out << getEffect(); 
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

string Deploy::getEffect() 
{
	return "Troups getting deployed";
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

ostream& operator<<(ostream &out, Negotiate& n) {
	out << ""; 
}


