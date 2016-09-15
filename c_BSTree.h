#ifndef C_BSTREE_H
#define C_BSTREE_H

#include <iostream>
#include <queue>

#include"node.h"

using namespace std;

struct arg_struct {
	void* arg1;
	void* arg2;
};

template <class T>
class c_BSTree{

	public:
		c_BSTree(){
			root=nullptr;
		}

		c_Node<T>* root;
		pthread_mutex_t mMutex;

		void* my_insert(void* mdata);
		static void* insert_helper(void* context);
		void* my_delete(void* mdata);
		static void* delete_helper(void* context);
		void print(c_Node<T>* it);
		void print_bfs();
		void transform();
		c_Node<T>** my_find(T data, c_Node<T>*&ant);

};

template <class T>

c_Node<T>** c_BSTree<T>::my_find(T data, c_Node<T>*&ant){

	c_Node<T>** it=&root;

	// cout<<"Buscando"<<data<<endl;

	for(; *it!=nullptr && (*it)->data!=data; it=&(*it)->hijos[(*it)->data < data]){

		if(ant){
			ant->lock=0;
		}

		while((*it)->lock);

		if( *it != nullptr && (*it)->data != data ){
			ant=*it;
			(*it)->lock=1;
		}
	}
	return it;

}

template <class T>

void* c_BSTree<T>::my_insert(void *mdata){
	int a = *((int*) mdata);
	cout<<"Inserto: "<<a<<endl;
	T data;
	data= *((T *)mdata);
	// cout<<"Insertando "<<(data)<<endl;
	c_Node<T>* ant = nullptr;
	c_Node<T>** it;
	it=my_find(data, ant);

	while(it!=nullptr && (*it)->data!=data){
		it=my_find(data, ant);
	}

	cout<<"entro"<<endl;

	if(ant){
		ant->lock=1;
	}

	again:
	pthread_mutex_lock(&mMutex);
	if(!(*it)){
	  *it = new c_Node<T> (data);
	}
	pthread_mutex_unlock(&mMutex);

	if ( (*it) && (*it)->data != data ){
		it = my_find(data, ant);
		goto again;
	}
	//if(ant) {
	// ant->lock=0;
	// cout<<"Desbloqueo"<<endl;
	//}

}

/*
template <class T>

void c_BSTree<T>::parallel_insert(int elementos[], int tam){

	pthread_t* threads;

	threads = (pthread_t*) malloc( tam * sizeof(pthread_t) );
	void* u[2];
	u[0]=this;

	for (int i = 0; i < tam; ++i) {
		u[1]=(void*) elementos[i];
		pthread_create( &threads[i], NULL, c_BSTree<T>::insert_helper,u);
	}

	for (int i = 0; i < tam; ++i) {
		pthread_join( threads[i], NULL);
	}


}*/

template <class T>

void* c_BSTree<T>::insert_helper(void* context){
	struct arg_struct *args = (struct arg_struct *)context;
	//int el=args->arg1;

	return ((c_BSTree<T> *)args->arg1)->my_insert(args->arg2);
}

template <class T>

void c_BSTree<T>::print(c_Node<T>* it){

	if(!it) return;
	print(it->hijos[0]);
	cout<<it->data<<endl;
	print(it->hijos[1]);
}

template <class T>

void c_BSTree<T>::print_bfs(){

	int nivel;
	queue<pair<c_Node<T>* ,int> > cola;
	c_Node<T>* aux;

	cola.push(make_pair(root,0));

	while(!cola.empty()){

	aux=cola.front().first;
	nivel=cola.front().second;
	cout<<aux->data<<" en nivel "<<nivel<<endl;
	cola.pop();
	if(aux->hijos[0]!=nullptr) cola.push(make_pair(aux->hijos[0],nivel+1));
	if(aux->hijos[1]!=nullptr) cola.push(make_pair(aux->hijos[1],nivel+1));
	}
	cout<<endl;
}

template<class T>

void* c_BSTree<T>::my_delete(void* mdata)
{
	c_Node<T>** p;
	c_Node<T>* temp;
	c_Node<T>* ant=nullptr;
	T data;
	data= *((T *)mdata);
	p=my_find(data, ant);
	pthread_mutex_lock(&mMutex);
	if(!(*p)) return 0;
	cout<<"Elimino "<<data<<endl;
	temp=(*p);
	if((*p)->hijos[0] && (*p)->hijos[1]){


		for(p=&((*p)->hijos[0]); (*p)->hijos[1]; p=&((*p)->hijos[1]));
		swap((*p)->data,temp->data);
	}

	temp=(*p);
	(*p)=(*p)->hijos[!!(*p)->hijos[1]];
	pthread_mutex_unlock(&mMutex);
	//if(ant) {
	//ant->lock=0;
	cout<<"Desbloqueo"<<endl;
	//}
}

template <class T>

void* c_BSTree<T>::delete_helper(void* context){
	struct arg_struct *args = (struct arg_struct *)context;
	//int el=args->arg1;
	return ((c_BSTree<T> *)args->arg1)->my_delete(args->arg2);
}

#endif // C_BSTREE_H
