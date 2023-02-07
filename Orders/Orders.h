#pragma once
#include <string>
#include <vector>
using namespace std;

class OrdersList{
private:
    vector<Order*> vectorOfOrders;
public:
    OrdersList();
    OrdersList(OrdersList& copy); // copy constructor of Order
    void add(Order* o) { vectorOfOrders.push_back(o); }
    void printOrdersList(const vector<Order*> &vec); // const and &: the reference to the vector cannot be used to modify the original vector.
    //void remove(int i) { o = vectorOforders[i]; vectorOforders.erase(vectorOforders.begin() + i); delete o; }
    //void move(int from, int to) { ...; }

};

class Order{
protected:
    virtual string getDescription(); //cant init obj order cuz getDescription() is protected and it is not given a definition
    string *effect;
public:
    Order();
    Order(Order& copy); // copy constructor of Order

    //ostream& operator<<(ostream &out) { out << effect; }
    friend ostream& operator<<(ostream &out, Order& o);
};


class Deploy : public Order{
private:

protected:
    virtual string getDescription();
public:    
    Deploy();
    Deploy(Deploy& copy); // copy constructor
    Deploy& operator=(const Deploy& d); // assignment operator
    bool validate();
    void execute();
    friend ostream& operator<<(ostream &out, Deploy& d);
};


class Advance : public Order{
protected:
    virtual string getDescription();

public:
    Advance();
    Advance(Advance& copy); // copy constructor
    Advance& operator=(const Advance& a); // assignment operator
    bool validate();
    void execute();
    friend ostream& operator<<(ostream &out, Advance& a);
};


class Bomb : public Order{
protected:
    virtual string getDescription();
public:
    Bomb();
    Bomb(Bomb& copy); // copy constructor
    Bomb& operator=(const Bomb& b); // assignment operator
    bool validate();
    void execute();
    friend ostream& operator<<(ostream &out, Bomb& b);
};


class Blockade : public Order{
protected:
    virtual string getDescription();
public:
    Blockade();
    Blockade(Blockade& copy); // copy constructor
    Blockade& operator=(const Blockade& b); // assignment operator
    bool validate();
    void execute();
    friend ostream& operator<<(ostream &out, Blockade& bk);
};


class Airlift : public Order{
protected:
    virtual string getDescription();
public:
    Airlift();
    Airlift(Airlift& copy); // copy constructor
    Airlift& operator=(const Airlift& a); // assignment operator
    bool validate();
    void execute();
    friend ostream& operator<<(ostream &out, Airlift& ar);
};


class Negotiate : public Order{
protected:
    virtual string getDescription();
public:
    Negotiate();
    Negotiate(Negotiate& copy); // copy constructor
    Negotiate& operator=(const Negotiate& n); // assignment operator
    bool validate();
    void execute();
    friend ostream& operator<<(ostream &out, Negotiate& n);
};