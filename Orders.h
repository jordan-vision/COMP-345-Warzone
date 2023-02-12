#pragma once
#include <memory>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Order; 

/* -------------------------------------------------------------------------- */
/*                              OrdersList Class                              */
/* -------------------------------------------------------------------------- */

class OrdersList{
private:
    vector<Order*> vectorOfOrders; 
public:
    OrdersList();
    OrdersList(OrdersList& copy);
    OrdersList& operator=(const OrdersList& ol);
    friend ostream& operator<<(ostream &out, OrdersList& ol);
    void add(Order* o);
    void remove(int i);
    void move(int from, int to);
    ~OrdersList();

};

/* -------------------------------------------------------------------------- */
/*                                 Order Class                                */
/* -------------------------------------------------------------------------- */

class Order{
protected:
    virtual string getDescription() = 0; //virtual + protected = can be overriden by subclasses
    string orderEffect;
public:
    Order();
    virtual ~Order();
    Order(Order& copy); // copy constructor of Order
    string getOrderEffect();
    friend ostream& operator<<(ostream &out, Order& o);
};


/* -------------------------------------------------------------------------- */
/*                                Deploy Class                                */
/* -------------------------------------------------------------------------- */

class Deploy : public Order{
protected:
    virtual string getDescription();
public:    
    Deploy();
    ~Deploy();
    Deploy(Deploy& copy); // copy constructor
    Deploy& operator=(const Deploy& d); // assignment operator
    bool validate();
    void execute();
};


/* -------------------------------------------------------------------------- */
/*                                Advance Class                               */
/* -------------------------------------------------------------------------- */

class Advance : public Order{
protected:
    virtual string getDescription();

public:
    Advance();
    Advance(Advance& copy); // copy constructor
    Advance& operator=(const Advance& a); // assignment operator
    bool validate();
    void execute();
    ~Advance();
};


/* -------------------------------------------------------------------------- */
/*                                 Bomb Class                                 */
/* -------------------------------------------------------------------------- */

class Bomb : public Order{
protected:
    virtual string getDescription();
public:
    Bomb();
    Bomb(Bomb& copy); // copy constructor
    Bomb& operator=(const Bomb& b); // assignment operator
    bool validate();
    void execute();
    ~Bomb();
};


/* -------------------------------------------------------------------------- */
/*                               Blockade Class                               */
/* -------------------------------------------------------------------------- */

class Blockade : public Order{
protected:
    virtual string getDescription();
public:
    Blockade();
    Blockade(Blockade& copy); // copy constructor
    Blockade& operator=(const Blockade& b); // assignment operator
    bool validate();
    void execute();
    ~Blockade();
};

/* -------------------------------------------------------------------------- */
/*                                Airlift Class                               */
/* -------------------------------------------------------------------------- */

class Airlift : public Order{
protected:
    virtual string getDescription();
public:
    Airlift();
    Airlift(Airlift& copy); // copy constructor
    Airlift& operator=(const Airlift& a); // assignment operator
    bool validate();
    void execute();
    ~Airlift();
};


/* -------------------------------------------------------------------------- */
/*                               Negotiate Class                              */
/* -------------------------------------------------------------------------- */

class Negotiate : public Order{
protected:
    virtual string getDescription();
public:
    Negotiate();
    Negotiate(Negotiate& copy); // copy constructor
    Negotiate& operator=(const Negotiate& n); // assignment operator
    bool validate();
    void execute();
    ~Negotiate();
};