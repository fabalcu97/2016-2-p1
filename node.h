template <class T>

struct c_Node{

	c_Node(int n){
		data = n;
		lock = 0;
		hijos[1] = nullptr;
		hijos[0] = nullptr;
	}

	c_Node<T>* hijos[2];

	T data;
	bool lock;
};
