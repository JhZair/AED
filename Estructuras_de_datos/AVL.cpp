#include <iostream>
#include <queue>
#include <stack>
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
	void print_levels();
	void levels(Node* n);
	void imprimir();
	void LL(Node*& p);
	void LR(Node*& p);
	void RR(Node*& p);
	void RL(Node*& p);
	Node*& get_root(){return root;}
};

Btree::Btree(){
	root = 0;
	bool lado_reemp = 0;
}
Btree::~Btree(){

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
	
	void Btree::print_levels()
{
    std::cout<<"\n";
    levels(root);
    std::cout<<"\n";
}

void Btree::levels(Node* n)
{
    if ( !n ) return;
    std::queue<Node*> q;
    q.push(n);
    while ( !q.empty() )
    {
        Node* x = q.front();
        std::cout<<x->v<<" ";
        if ( x->left ) q.push(x->left);
        if ( x->right ) q.push(x->right);
        q.pop();
    }
}
	void Btree::LL(Node*& p){ // linea recta hacia la izq
		Node* q = (p->left)->right;
		(p->left)->right = p;
		p = p->left;
		(p->right)->left = q;
	}
	void Btree::RR(Node*& p){ // linea recta hacia la derecha
		Node* q = (p->right)->left;
		(p->right)->left = p;
		p = p->right;
		(p->left)->right = q;
	}
	void Btree::LR(Node*& p){ // zigzag hacia la izq
		Node* q = (p->left)->right;
		(p->left)->right = q->left;
		q->left = p->left;
		p->left = q->right;
		q->right = p;
		p = q;
	}
	void Btree::RL(Node*& p){ // zigazag hacia la derecha
		Node* q = (p->right)->left;
		(p->right)->left = q->right;
		q->right = p->right;
		p->right = q->left;
		q->left = p;
		p = q;
	}
	
	
	int main(int argc, char *argv[]) {
		Btree a;
		a.ins(14); a.print_levels();
		a.ins(13); a.print_levels();
		a.ins(33); a.print_levels();
		a.ins(7); a.print_levels();
		a.ins(28); a.print_levels();
		a.LL(a.get_root());
		a.print_levels();
		
		return 0;
	}
	
	//segunda tarea hacer arbol roj y negro
