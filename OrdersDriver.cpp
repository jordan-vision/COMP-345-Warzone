#include <iostream>
#include "Orders.h"
#include <string>

main()
{
   cout << "You can now enter your orders. The orders you can use are deploy, advance, bomb, blockade, airlift, negotiate." << endl;

   // create an OrderList object
   OrdersList* ol = new OrdersList();


   // create orders of all types
   Deploy* d = new Deploy();
   Advance* a = new Advance();
   Blockade* bl = new Blockade();
   Bomb* bo = new Bomb();
   Airlift* ar = new Airlift();
   Negotiate* n = new Negotiate();

   // add those orders to the OrderList object ol
   ol->add(d);
   ol->add(a);
   ol->add(bl);
   ol->add(bo);
   ol->add(ar);
   ol->add(n);
   cout << *ol << endl;

//    // demonstrate use of remove order
   cout << "***************** Remove Order demo *****************" << endl;
   ol->remove(1); 

   cout << *ol << endl;

   //demonstrate use of move order
   cout << "***************** Move Orders demo *****************" << endl;
   ol->move(0, 3);

   cout << *ol << endl;

   // Demonstrate use of stream insertion operator of class Order, as well as changed effect when order is executed (and validated) 
   cout << *bl << endl;
   bl->execute();
   cout << *bl << endl;

   // Demonstrate use of copy constructor
   cout << "***************** Copy Constructor demo *****************" << endl;
   Negotiate* n2 = new Negotiate();
   n2->execute();
   Negotiate* n1 = n2;
   cout << *n1 << endl;

   // Demonstrate use of assignment operator
   cout << "***************** Assignment operator demo *****************" << endl;
   Blockade* operatorDemoBlockade = new Blockade();
   cout << *operatorDemoBlockade << endl;
   operatorDemoBlockade = bl;
   cout << *operatorDemoBlockade << endl;
   

 }



