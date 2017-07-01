# Factory-Stock
Assembling of components 

There is a factory dedicated to the assembling of components. Each component requires a set of parts that can either be in stock or provided from a manufacturer (with a determined delivery time).


•	Client order: the request of a finite number of components. 

•	Part: basic elements used to build components.

•	Component: describes a list of parts needed to build the component

•	Factory:  it stores the parts and deals with the client orders and the orders to the manufacturer. It has a stock list, a client order list and a list of the components that can be built. Can only manage 1 order at a time (the rest of orders go to the line).

First of all, the parts have to be defined. After, all the possible components are defined, each one requiring a determined set of parts.
The client can create an order, he can add and remove components in the order or even create a new order (he doesn’t need to know what parts are needed for each component). When he thinks the order is ready he can send it to a factory. This action will proceed only if the client hasn’t surpassed the maximum number of orders by client defined by the factory; if there is enough space in the order list of the factory and the components in the order can be built in that factory.

 The client can cancel an order. However this will only be possible if the order is not the first one in the factory’s order list because if it is the first one it means that it is being assembled by the factory.
 
The order of a client to the factory is defined in clientOrder.  A random reference number is given to it and it will be the identifier of the order. The factory gets the order and puts it on the order list; however this list is limited so if there are too many orders the send function will return a false.

There will be functions that will return the estimated delivery time of the order (taking into account the position in the list). When the factory gets the order it will analyze it and determine the parts needed. The factory will then determine if these parts are in the storage or have to be provided from a manufacturer. If this is the case, the factory will automatically create an order for these parts.  The factory can also order a determined number of parts without a need of a client order.

As I don’t know how to implement time in c++, there will be a need for functions like clientOrder finished, which will make the parts used be removed from the stock. The prices for each component are determined by the prices of the parts and a % is added (factory’s gaining).


