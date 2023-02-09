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
   Advance a;
   Blockade bl;
   Bomb bo;
   Bomb bo2;

   // add those orders to the OrderList object ol
   ol.add(&d);
   ol.add(&a);
   ol.add(&bl);
   ol.add(&bo);
   ol.add(&bo2);
   ol.printOrdersList();

   // demonstrate use of remove order
   ol.remove(1); 

   ol.printOrdersList();

   //demonstrate use of move order
   ol.move(0, 3);

   ol.printOrdersList();

   // Demonstrate use of stream insertion operator of class Order, as well as changed effect when order is executed (and validated) 
   cout << bl << endl;
   bl.execute();
   cout << bl << endl;

   // Demonstrate use of copy constructor
   Negotiate n2;
   Negotiate n1 = n2;

   // Demonstrate use of assignment operator
   Negotiate n3;
   n3 = n1;

   

}



