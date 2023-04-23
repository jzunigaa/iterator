#include <iostream>
#include "CircularArray.h"
#include "CircularDoubleList.h"
using namespace std;

void test_IteratorCirculararray(){
    CircularArray<int> contenedor;
    contenedor.push_front(10);
    contenedor.push_front(5);
    contenedor.push_back(8);
    contenedor.push_back(9);

    CircularArray<int>::iterator ite;
    for(ite = contenedor.begin(); ite != contenedor.end(); ++ite)
        cout << *ite << endl;
}

void test_IteratorCircularDoubleList(){
    circularDoubleList<int> list;
    list.push_front(10);
    list.push_front(5);
    list.push_back(8);
    list.push_back(9);
    list.push_front(20);
    list.push_front(26);
    list.push_back(39);
    cout<<"\nUsamos operador []"<<endl;
    cout<<"elemento[1]: "<<list[1]<<endl;
    cout<<"elemento[5]: "<<list[5]<<endl;
    cout<<"elemento[10]: "<<list[10]<<endl;
    cout<<"\nUsamos el Iterador"<<endl;
    circularDoubleList<int>::iterator ite;
    for(ite = list.begin(); ite != list.end(); ++ite)
        cout << *ite << endl;
}

int main()
{
    cout<<"::::::Test iterator Circular Array::::::"<<endl;
    test_IteratorCirculararray();
    cout<<"\n::::::Test iterator Circular Double List::::::"<<endl;
    test_IteratorCircularDoubleList();

}