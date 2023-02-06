#pragma once
#include <string>
#include <vector>
using namespace std;

class OrdersList{
private:
    vector<Order*> vectorOfOrders;
public:
    void add(Order* o) { vectorOfOrders.push_back(o); }
    void remove(int i) { o = vectorOforders[i]; vectorOforders.erase(vectorOforders.begin() + i); delete o; }
    void move(int from, int to) { ...; }

};

class Order{
protected:
    virtual string getEffect() = 0; //cant init obj order cuz geteffect() is protected and it is not given a definition
public:
    Order();
    Order(Order& copy); // copy constructor of Order

    //ostream& operator<<(ostream &out) { out << effect; }
    friend ostream& operator<<(ostream &out, Order& o);
};


class Deploy : public Order{
private:

protected:
    virtual string getEffect();
public:    
    Deploy();
    Deploy(Order& copy); // copy constructor
    Order& operator=(const Order& o); // assignment operator
    bool validate();
    void execute();
    friend ostream& operator<<(ostream &out, Deploy& d);
};


class Advance : public Order{
protected:
    virtual string getEffect() {return "advanced the troops";}

public:
    Advance();
    Advance(Order& copy); // copy constructor
    Advance& operator=(const Advance& a); // assignment operator
    bool validate();
    void execute();
    friend ostream& operator<<(ostream &out, Advance& a);
};


class Bomb : public Order{
public:
    Bomb();
    Bomb(Order& copy); // copy constructor
    Bomb& operator=(const Bomb& b); // assignment operator
    bool validate();
    void execute();
    friend ostream& operator<<(ostream &out, Bomb& b);
};


class Blockade : public Order{
    Blockade();
    Blockade(Order& copy); // copy constructor
    Blockade& operator=(const Blockade& b); // assignment operator
    bool validate();
    void execute();
    friend ostream& operator<<(ostream &out, Blockade& bk);
};


class Airlift : public Order{
    Airlift();
    Airlift(Order& copy); // copy constructor
    Airlift& operator=(const Airlift& a); // assignment operator
    bool validate();
    void execute();
    friend ostream& operator<<(ostream &out, Airlift& ar);
};


class Negotiate : public Order{
    Negotiate();
    Negotiate(Order& copy); // copy constructor
    Negotiate& operator=(const Negotiate& n); // assignment operator
    bool validate();
    void execute();
    friend ostream& operator<<(ostream &out, Negotiate& n);
};