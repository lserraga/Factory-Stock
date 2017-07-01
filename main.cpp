#include <iostream>
#include <fstream>
#include <vector>
#include "Part.h"
#include "Component.h"
#include "ClientOrder.h"
#include "Factory.h"

using namespace std;
using namespace Chrono;



void manager_functionallity(Factory* testF,Date current){
    int aux=1,a,b,c;
    float d;
    while(true){
        cout<<"\n**********Possible actions:**********\n\n";
        cout << "1- Define Parts"<<endl;
        cout << "2- Add or remove parts from stock"<<endl;
        cout << "3- Define Component"<<endl;
        cout << "4- Show orders in the waiting list"<<endl;
        cout << "5- Show stock"<<endl;
        cout << "6- Process Order"<<endl;
        cout << "7- Show Orders waiting for Parts"<<endl;
        cout << "- Exit"<<endl;
        cin >> aux;
        switch (aux){
            case 1 :
                cout<<"\n**********Modifying stock:**********\n\n";
                cout << "Enter the reference number: " << endl;
                cin >> a;
                cout << "Enter the delivery time:" << endl;
                cin >> c;
                cout << endl;
                testF->add_stock(a,0,c);
                break;
            case 2 :
                cout<<"\n**********Adding/removing stock:**********\n\n";
                cout << "Enter the reference number: " << endl;
                cin >> a;
                if(testF->is_part_defined(a)){
                    cout << "Enter the quantity: " << endl;
                    cin >> b;
                    cout << endl;
                    testF->add_stock(a,b);
                }
                else
                    cout << "Part o reference number="<<a<<" has not been defined yet\n";
                break;
            case 3 :
                cout<<"\n**********Defining a component:**********\n\n";
                cout << "Enter the reference number: " << endl;
                cin >> a;
                cout << "Enter the price of the component" << endl;
                cin >> d;
                testF->addComponentToList(a,d);
                break;
            case 4 :
                testF->printOrderList();
                break;
            case 5:
                testF->printStotck();
                break;
            case 6:
                a=testF->process_order(current);
                if(!a)
                    cout <<"Order shipped succesfully\n";
                else if (a>0)
                    cout <<" Estimated number of days to deliver: "<<a<<endl;
                else
                    cout <<" There are not any more orders in the waiting list "<<endl;
                break;
            case 7:
                testF->showOrdersWParts();
                break;
            default: return;
        }
    }
}

void user_functionallity(Factory* testF){
    int aux,a,b;
    char name[20];

    Date daux;
    Date daux2;

    cout<< "Introduce your name: ";
    cin.getline(name, 500, '.' );
    cout << "\nHello "<<name<<endl;
    ClientOrder neworder(name);
    while(true){
        cout<<"\n**********Possible actions:**********\n\n";
        cout << "1- Show list of components avaliable"<<endl;
        cout << "2- Add component to the order"<<endl;
        cout << "3- Remove component from the order"<<endl;
        cout << "4- Show order"<<endl;
        cout << "5- Send order"<<endl;
        cout << "6- Remove order"<<endl;
        cout << "7- Show estimated delivery time"<<endl;
        cout << "- Exit"<<endl;
        cin >> aux;
        switch (aux){
            case 1 :
                testF->printComponentList();
                break;
            case 2:
                cout << "Enter the reference number of the component:"<<endl;
                cin>>a;
                cout << "Enter the number of the components with reference number="<<a<<" wanted:"<<endl;
                cin>>b;
                neworder.add_component(a,b);
                break;
            case 3:
                cout << "Enter the reference number of the component:"<<endl;
                cin>>a;
                neworder.remove_component(a);
                break;
            case 4:
                neworder.show_order();
                cout<<"PRICE----->"<<testF->calculatePriceOrder(neworder)<<" Zlotys\n";
                break;
            case 5:
                if(!testF->recieve_order(neworder))
                    cout<<"Some of the components can no be built in this factory\n";
                else
                    cout<<"Order added to the list\n\t The total price of the order is "<<testF->calculatePriceOrder(neworder)<<" Zlotys"<<endl;
                    cout<<"The reference of your order is: "<<neworder.getRef()<<endl;
                    return;
                break;
            case 6:
                cout<<"Enter the reference of the order\n";
                cin>>b;
                a=testF->remove_order(name,b);
                if(a==0)
                    cout<<"This order is not in the system\n";
                else if(a==-1)
                    cout<<"ERROR, this order is from another client\n";
                else if(a==-2)
                    cout<<"ERROR, this order can not be removed because it is already being assembled\n";
                else
                    cout<< "Order "<<b<<" removed from the order list\n";
                break;
            case 7:
                cout<<"Enter the reference of the order\n";
                cin>>b;
                daux2.set_date(0,0,0);
                daux=testF->getDeliveryTime(b);
                if(daux==daux2 && testF->orderExist(b))
                    cout<<"This order is still being processed\n";
                else if (daux!=daux2)
                    cout<< "Estimated delivery date for order "<<b<<" is "<<daux<<"\n";
                else
                    cout<< "This order is not in the system\n";
                break;
            default:
                return;
        }
    }
}

int main() ///price de el ultimo no se pone bien
{
    int aux1=1,yy,mm,dd;
    Factory testF;
    testF.loadStockData();
    testF.loadComponentData();
    testF.loadOrderList();
    testF.loadOrderProcess();
    testF.loadRef();

    Date currentDate;
    ifstream gs("dateFile.txt");
    gs>>currentDate;
    gs.close();

    ++currentDate; ///Every time its executed it increases 1 day.

    testF.send_orders(currentDate);

    cout<<"\n\n\t ***** DATE : "<<currentDate<<" *****\n\n";


    cout << "-------------------------Project-----------------------" << endl;


    while(aux1!=0){
             cout<<"\n**********OPTIONS:**********\n\n";
             cout << "1- Manager"<<endl;
             cout << "2- Client"<<endl;
             cout << "3- Modify date"<<endl;
             cout << "4- Exit"<<endl;
             cout << endl;
             cin >> aux1;
             switch (aux1){
                    case 1 :
                        manager_functionallity(&testF,currentDate);
                        break;
                    case 2 :
                        user_functionallity(&testF);
                        break;
                    case 3:
                         do{
                            cout << "Enter correct date:\n\tDay:";
                            cin >>dd;
                            cout << "\tMonth: ";
                            cin >>mm;
                            cout << "\tYear: ";
                            cin >>yy;
                        }while(!is_date(yy,mm,dd));
                        currentDate.set_date(dd-1,mm-1,yy-1);
                        testF.send_orders(currentDate);
                        cout<<currentDate;

                        break;
                    case 4:
                        aux1=0;
                    default: break;
             }
    }
    testF.saveComponentList();
    testF.saveStockData();
    testF.saveOrderList();
    testF.saveOrderProcess();
    testF.saveRef();

    ofstream fs("dateFile.txt");
    fs<<currentDate;
    fs.close();

    return 0;
}
