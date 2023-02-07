#include <iostream>
#include "Orders.h"
#include <string>

main()
{
   // to be linked with Player part!!
   OrdersList ol();

   cout << "You can now enter your orders. The orders you can use are deploy, advance, bomb, blockade, airlift, negotiate." << endl;
   // while (cin >> order && order != "0"){
   //    if (order == "deploy"){
   //       ol.add(new Deploy());
   //    }
   // }

   Deploy d;
   ol.add(&d);


}



