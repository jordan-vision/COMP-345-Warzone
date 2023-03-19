#pragma once
#include "LoggingObserver.h"
#include "Player.h"
#include "Map.h"
#include <memory>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Order; 
class Player;
class Territory;

/* -------------------------------------------------------------------------- */
/*                              OrdersList Class                              */
/* -------------------------------------------------------------------------- */

class OrdersList : public ILoggable, public Subject {
public:
    vector<Order*> vectorOfOrders; 
    OrdersList();                                               //OrdersList constructor
    OrdersList(OrdersList& copy);                               //OrdersList copy constructor
    OrdersList& operator=(const OrdersList& ol);                //OrdersList assignment operator
    friend ostream& operator<<(ostream &out, OrdersList& ol);   //OrdersList stream insertion operator
    void add(Order* o);                                         //add(..) pushes an order object to the orderslist
    void remove(int i);                                         //remove(..) removes an order object from the orderslist
    void move(int from, int to);                                //move(..) swaps two orders places
    ~OrdersList();                                              //OrdersList destructor
    virtual string stringToLog() override; 
};

/* -------------------------------------------------------------------------- */
/*                                 Order Class                                */
/* -------------------------------------------------------------------------- */

class Order : public ILoggable, public Subject {
protected:
    virtual string getDescription() = 0;                        //getDescription() returns order description. virtual + protected = can be overriden by subclasses
    string orderEffect;                                         //order effect stored there
public:
    Order();                                                    //Order constructor
    virtual ~Order();                                           //Order destructor
    Order(Order& copy);                                         //Order copy constructor            
    string getOrderEffect();                                    //gets the effect of the order
    friend ostream& operator<<(ostream &out, Order& o);         //Order stream insertion operator
    virtual string stringToLog() override;                      
    virtual void execute(Player* player) =0;
    virtual bool validate(Player* player) =0;
};


/* -------------------------------------------------------------------------- */
/*                                Deploy Class                                */
/* -------------------------------------------------------------------------- */

class Deploy : public Order{
protected:
    virtual string getDescription() override;
public:    
    Deploy(Territory* target);
    ~Deploy();
    Deploy(Deploy& copy); // copy constructor
    Deploy& operator=(const Deploy& d); // assignment operator
    virtual bool validate(Player* player) override; // validate the order
    virtual void execute(Player* player) override; // execute the order

    Territory* target;
};


/* -------------------------------------------------------------------------- */
/*                                Advance Class                               */
/* -------------------------------------------------------------------------- */

class Advance : public Order{
protected:
    virtual string getDescription() override;
public:
    Advance(Territory* target, Territory* source);
    Advance(Advance& copy); // copy constructor
    Advance& operator=(const Advance& a); // assignment operator
    virtual bool validate(Player* player) override; // validate the order
    virtual void execute(Player* player) override; // execute the order
    ~Advance();

    Territory* target;
    Territory* source;
};


/* -------------------------------------------------------------------------- */
/*                                 Bomb Class                                 */
/* -------------------------------------------------------------------------- */

class Bomb : public Order{
protected:
    virtual string getDescription() override;
public:
    Bomb(Territory* target);
    Bomb(Bomb& copy); // copy constructor
    Bomb& operator=(const Bomb& b); // assignment operator
    virtual bool validate(Player* player) override; // validate the order
    virtual void execute(Player* player) override; // execute the order
    ~Bomb();
    
    Territory* target;
};


/* -------------------------------------------------------------------------- */
/*                               Blockade Class                               */
/* -------------------------------------------------------------------------- */

class Blockade : public Order{
protected:
    virtual string getDescription() override;
public:
    Blockade(Territory* target);
    Blockade(Blockade& copy); // copy constructor
    Blockade& operator=(const Blockade& b); // assignment operator
    virtual bool validate(Player* player) override; // validate the order
    virtual void execute(Player* player) override; // execute the order
    ~Blockade();
    Territory* target;
};

/* -------------------------------------------------------------------------- */
/*                                Airlift Class                               */
/* -------------------------------------------------------------------------- */

class Airlift : public Order{
protected:
    virtual string getDescription() override;
public:
    Airlift(Territory* target, Territory* source);
    Airlift(Airlift& copy); // copy constructor
    Airlift& operator=(const Airlift& a); // assignment operator
    virtual bool validate(Player* player) override; // validate the order
    virtual void execute(Player* player) override; // execute the order
    ~Airlift();

    Territory* target;
    Territory* source;
};


/* -------------------------------------------------------------------------- */
/*                               Negotiate Class                              */
/* -------------------------------------------------------------------------- */

class Negotiate : public Order{
protected:
    virtual string getDescription() override;
public:
    Negotiate(Territory* target);
    Negotiate(Negotiate& copy); // copy constructor
    Negotiate& operator=(const Negotiate& n); // assignment operator
    virtual bool validate(Player* player) override; // validate the order
    virtual void execute(Player* player) override; // execute the order
    ~Negotiate();

    Territory* target;
};