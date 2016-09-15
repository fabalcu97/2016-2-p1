#include <iostream>
#include <pthread.h>
#include <random>
#include <time.h>
#include "c_BSTree.h"
using namespace std;
typedef int ENTERO;
typedef c_BSTree<int> ArbolEntero;
//Modificacion Joaquingx
//Agregar Jonathan

int main()
{
    c_BSTree<int> tree;
    int tam;
    srand(time(NULL));
    tam=10;
    int elementos[tam];
    for(int i=0; i< tam; ++i){
	elementos[i]=rand()%100;
    }
    cout<<"Angel modifica"<<endl;
    cout<<"Angel modifica2"<<endl;
    cout<<"vivo"<<endl;
    struct arg_struct args;
    args.arg1 = &tree;

	cout<<"JonMoll modifica"<<endl;
	
	tree.parallel_insert(elementos,tam);


    return 0;
}
