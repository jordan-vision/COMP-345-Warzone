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
private:
    vector<Order*> vectorOfOrders; 
public:
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
    virtual void execute(Player* player, Territory* target) =0;
    virtual bool validate(Player* player);
};


/* -------------------------------------------------------------------------- */
/*                                Deploy Class                                */
/* -------------------------------------------------------------------------- */

class Deploy : public Order{
protected:
    virtual string getDescription() override;
public:    
    Deploy();
    ~Deploy();
    Deploy(Deploy& copy); // copy constructor
    Deploy& operator=(const Deploy& d); // assignment operator
    bool validate(Player* player, Territory* target); // validate the order
    virtual void execute(Player* player, Territory* target) override; // execute the order
};


/* -------------------------------------------------------------------------- */
/*                                Advance Class                               */
/* -------------------------------------------------------------------------- */

class Advance : public Order{
protected:
    virtual string getDescription() override;

public:
    Advance();
    Advance(Advance& copy); // copy constructor
    Advance& operator=(const Advance& a); // assignment operator
    bool validate(Player* player, Territory* target); // validate the order
    virtual void execute(Player* player, Territory* target) override; // execute the order
    ~Advance();
};


/* -------------------------------------------------------------------------- */
/*                                 Bomb Class                                 */
/* -------------------------------------------------------------------------- */

class Bomb : public Order{
protected:
    virtual string getDescription() override;
public:
    Bomb();
    Bomb(Bomb& copy); // copy constructor
    Bomb& operator=(const Bomb& b); // assignment operator
    bool validate(Player* player, Territory* target); // validate the order
    virtual void execute(Player* player, Territory* target) override; // execute the order
    ~Bomb();
};


/* -------------------------------------------------------------------------- */
/*                               Blockade Class                               */
/* -------------------------------------------------------------------------- */

class Blockade : public Order{
protected:
    virtual string getDescription() override;
public:
    Blockade();
    Blockade(Blockade& copy); // copy constructor
    Blockade& operator=(const Blockade& b); // assignment operator
    bool validate(Player* player, Territory* target); // validate the order
    virtual void execute(Player* player, Territory* target) override; // execute the order
    ~Blockade();
};

/* -------------------------------------------------------------------------- */
/*                                Airlift Class                               */
/* -------------------------------------------------------------------------- */

class Airlift : public Order{
protected:
    virtual string getDescription() override;
public:
    Airlift();
    Airlift(Airlift& copy); // copy constructor
    Airlift& operator=(const Airlift& a); // assignment operator
    bool validate(Player* player, Territory* target); // validate the order
    virtual void execute(Player* player, Territory* target) override; // execute the order
    ~Airlift();
};


/* -------------------------------------------------------------------------- */
/*                               Negotiate Class                              */
/* -------------------------------------------------------------------------- */

class Negotiate : public Order{
protected:
    virtual string getDescription() override;
public:
    Negotiate();
    Negotiate(Negotiate& copy); // copy constructor
    Negotiate& operator=(const Negotiate& n); // assignment operator
    bool validate(Player* player, Territory* target); // validate the order
    virtual void execute(Player* player, Territory* target) override; // execute the order
    ~Negotiate();
};