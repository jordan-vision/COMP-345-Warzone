#include <iostream>
#include "Orders.h"
#include <string>

main()
{
   cout << "You can now enter your orders. The orders you can use are deploy, advance, bomb, blockade, airlift, negotiate." << endl;

   // create an OrderList object
   OrdersList ol;

   // create orders of all types
   Deploy d;
   Blockade bl;
   Bomb bo;
   Bomb bo2;

   // add those orders to the OrderList object ol
   ol.add(&d);
   ol.add(&bl);
   ol.add(&bo);
   ol.add(&bo2);
   ol.printOrdersList();

   // Demonstrate use of stream insertion operator of class Order, as well as changed effect when order is executed (and validated) 
   cout << bl << endl;
   d.execute();
   cout << bl << endl;

   // Demonstrate use of copy constructor


   // Demonstrate use of assignment operator

   

}



