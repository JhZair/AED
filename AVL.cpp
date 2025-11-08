#include <iostream>
#include <queue>
using namespace std;

struct Node {
	int v;
	Node * right;
	Node * left;
	Node(int x){
		v = x;
		right = left = 0;
	}
};

class Btree{
	Node * root;
	bool lado_reemp;
public:
	Btree();
	~Btree();
	bool ins(int x);
	bool fnd(int x, Node**& p);
	bool remv(int x);
	Node** reemp(Node** p);
	void inorder(Node* p);
	void imprimir();
};

Btree::Btree(){
	root = 0;
	bool lado_reemp = 0;
}
Btree::~Btree(){
	queue<int> q;
	
}
	
	bool Btree::ins(int x){
		Node** p = &root;
		if(fnd(x, p))return 0;
		*p = new Node(x);
		return 1;
	}
	bool Btree::remv(int x){
		Node** p = &root;
		if(!fnd(x, p))return 0;
		
		if((*p)->left && (*p)->right ){
			Node** q = reemp(p);
			(*p)->v = (*q)->v;
			p = q; 
		}
		Node* t = *p;
		if((*p)->left)
			*p = (*p)->left;
		else
			*p = (*p)->right;
		delete t;
		return 1;
	}
	Node** Btree::reemp(Node** p){
		Node** q;
		if(lado_reemp){
			q = &((*p)->right);
			while((*q)->left)
				q = &((*q)->left);
		}
		else{
			q = &((*p)->left);
			while((*q)->right)
				q = &((*q)->right);
		}
		lado_reemp = !lado_reemp;
		return q;
	}
	bool Btree::fnd(int x, Node**& p){
		while(*p && (*p)->v != x){
			if((*p)->v > x)
				p = &((*p)->left);
			else
				p = &((*p)->right);
		}
		return *p;
	}
	void Btree::inorder(Node* p){
		if(!p) return;
		inorder(p->left);
		cout << p->v << ' ';
		inorder(p->right);
	}
	void Btree::imprimir(){
		inorder(root);
		cout<< endl;
	}
	
	void case1(Node* p){ // linea recta hacia la izq
		Node* q = (p->left)->right;
		(p->left)->right = p;
		p->right = q;
		p = p->left;
	}
	void case2(Node* p){ // linea recta hacia la derech
		Node* q = (p->right)->left;
		(p->right)->left = p;
		p->left = q;
		p = p->right;
	}
	void case3(Node* p){ // zigzag hacia la izq
		Node* q = (p->right)->left;
		(p->right)->left = p;
		p->left = q;
		p = p->right;
	}
	
		
	int main(int argc, char *argv[]) {
		Btree a;
		a.ins(14); a.imprimir();
		a.ins(13); a.imprimir();
		a.ins(33); a.imprimir();
		a.ins(7); a.imprimir();
		a.ins(28); a.imprimir();
		
		return 0;
	}
	
	//segunda tarea hacer arbol roj y negro
