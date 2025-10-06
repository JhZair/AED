#include <iostream>
using namespace std;

struct Node {
	int v;
	Node * right;
	Node * left;
	Node(){
		v = 0;
		right = left = 0;
	}
};

class Btree{
	Node * root;
//	int nelemns
public:
	Btree();
	~Btree();
	bool fnd(int x, Node**& p);
	bool ins(int x, Node**& p);
	bool remv(int x, Node**& p);
	void imprimir();
	
};

Btree::Btree(){
	root = 0;
}
Btree::~Btree(){
	
}

bool Btree::fnd(int x, Node**& p){
	p = &root;
	while(*p && (*p)->v != x){
		if((*p)->v < x){
			p = &((*p)->left);
		}
		else{
			p = &((*p)->right);
		}
	}
	return (*p) != 0;
}
bool Btree::ins(int x, Node**& p){
	
}
bool Btree::remv(int x, Node**& p){}
void Btree::imprimir(){}



int main(int argc, char *argv[]) {
	
	return 0;
}

//hay tarea de ingresar punteros de array a una función y que te devuelva un árbol de abajo a arriba con las sumas de los elems continuos
