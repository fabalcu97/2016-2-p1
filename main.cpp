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

	cout<<"Fablacu97 modifica"<<endl;
	tree.parallel_insert(elementos,tam);
	cout<<"mureran todos"<<endl;

    pthread_t* threads;
    threads = (pthread_t*) malloc( tam * sizeof(pthread_t) );
    pthread_t* threads1;

	threads1 = (pthread_t*) malloc( 3 * sizeof(pthread_t) );

	for (int i = 0; i < tam; ++i) {
		int n = 0;
		args.arg2 =&elementos[i];
		int a = *((int*) args.arg2);
		cout<<"Creo hilo"<<a<<endl;
		pthread_create( &threads[i], NULL, &c_BSTree<int>::insert_helper, (void *)&args);
		while(n < 10000){
			n++;
		}
	}

	for (int i = 0; i < tam; ++i) {
		pthread_join( threads[i], NULL);
	}

	// for (int i = 0; i < 3; ++i) {
	// 	//cout<<"Creo hilo"<<endl;
	// 	args.arg2 =&elementos[rand()%tam];
	// 	pthread_create( &threads1[i], NULL, &c_BSTree<int>::delete_helper, (void *)&args);
	// }
	//
	// for (int i = 0; i < 3; ++i) {
	// 	pthread_join( threads1[i], NULL);
	// }

    //tree.my_insert(5);
    //tree.my_insert(2);
    //tree.my_insert(9);
    //tree.my_insert(7);
    //tree.my_insert(3);

    //tree.my_delete(2);

    //tree.print(tree.root);
    cout<<endl<<"Impresion por niveles: "<<endl;
    tree.print_bfs();
    //tree.transform();
    //cout<<endl<<"Impresion por niveles: "<<endl;
    //tree.print_bfs();
    //tree.print(tree.root);

    return 0;
}
