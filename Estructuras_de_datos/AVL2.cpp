#include <iostream>
#include <stack>
#include <algorithm>
#include <queue>
using namespace std;

struct Node{
	int v;
	Node* left;
	Node* right;
	int h;
	Node(int _v){
		v = _v;
		left = right = 0;
		h = 0;
	}
};

class AVLtree{
	Node* root;
	bool lado_reemp;
	
	bool find(int x, Node**& p, stack<Node**>& path){
		while(*p && (*p)->v != x){
			path.push(p);
			if((*p)->v > x)
				p = &((*p)->left);
			else
				p = &((*p)->right);
		}
		return *p;
	}
	void LL(Node*& p){
		Node* t = p->left;
		p->left = t->right;
		t->right = p;
		p=t;
		actualizar_altura(p->right);
		actualizar_altura(p);
	}
	void RR(Node*& p){
		Node* t = p->right;
		p->right = t->left;
		t->left= p;
		p=t;
		actualizar_altura(p->left);
		actualizar_altura(p);
	}
	void LR(Node*& p){
		RR(p->left);
		LL(p);
	}
	void RL(Node*& p){
		LL(p->right);
		RR(p);
	}
	int altura(Node* p){
		if(p)
			return p->h;
		else 
			return -1;
	}
	void actualizar_altura(Node* p){
		if(p)
			p->h = 1 + std::max(altura(p->left),altura(p->right));
	}
	int FB(Node* p){
		if(p)
			return altura(p->right) - altura(p->left);
		else
			return 0;
	}
	void verificar_ruta(stack<Node**>& path){
		while(!path.empty()){
			Node** nodo_actual = path.top();
			path.pop();
			
			actualizar_altura(*nodo_actual);
			int bfActual = FB(*nodo_actual);
			
			if(bfActual < -1){
				if(FB((*nodo_actual)->left) <= 0)
					LL(*nodo_actual);
				else
					LR(*nodo_actual);
			}
			else if(bfActual > 1){
				if(FB((*nodo_actual)->right) >= 0)
					RR(*nodo_actual);
				else
					RL(*nodo_actual);
			}
		}
	}
	
public:
	AVLtree(){
		root = 0;
		lado_reemp = false;
	}
	~AVLtree(){
		clear(root);
	}
	bool insrt(int x){
		Node** p = &root;
		stack<Node**> path;
		
		if(find(x, p, path)) return false;
		
		*p = new Node(x);
		
		verificar_ruta(path);
		return true;
	}
	Node** fnd_reemp(Node** p, stack<Node**>& path){
		Node** q = p;
		if(lado_reemp){
			q = &((*q)->left);
			path.push(q);
			while((*q)->right){
				q = &((*q)->right);
				path.push(q);
			}
		}
		else{
			q = &((*q)->right);
			path.push(q);
			while((*q)->left){
				q = &((*q)->left);
				path.push(q);
			}
		}
		lado_reemp = !lado_reemp;
		return q;
	}
	bool remv(int x){
		Node** p = &root;
		stack<Node**> path;
		
		if(!find(x, p, path)) return false;
		
		if((*p)->left && (*p)->right){
			path.push(p);
			Node**q = fnd_reemp(p, path);
			(*p)->v = (*q)->v;
			p = q;
		}
		Node* t = *p;
		if((*p)->left)
			*p = (*p)->left;
		else
			*p = (*p)->right;
		delete t;
		
		verificar_ruta(path);
		return true;
	}
	void inorder(Node* p){
		if(!p) return;
		inorder(p->left);
		cout << p->v << ' ';
		inorder(p->right);
	}
	void clear(Node* p){
		if(!p) return;
		clear(p->left);
		clear(p->right);
		delete p;
	}
	void print(){
		cout << endl;
		inorder(root);
		cout << endl;
	}

	void printLevels(){
		if(!root) return;
		cout << endl;
		queue<Node*> q;
		q.push(root);
		while(!q.empty()){
			Node* p = q.front();
			cout << p->v << '|';
			if(p->left)
				q.push(p->left);
			if(p->right)
				q.push(p->right);
			q.pop();
		}
		cout << endl;
	}
};


int main(int argc, char *argv[]) {
	AVLtree t;
	t.insrt(60); t.print();t.printLevels();
	t.insrt(30); t.print();t.printLevels();
	t.insrt(20); t.print();t.printLevels();
	t.insrt(40); t.print();t.printLevels();
	t.insrt(90); t.print();t.printLevels();
	t.insrt(65); t.print();t.printLevels();
	t.insrt(80); t.print();t.printLevels();
	t.insrt(75); t.print();t.printLevels();
	t.remv(20); t.print();t.printLevels();
	t.remv(40); t.print();t.printLevels();
	t.remv(65); t.print();t.printLevels(); 
	t.remv(60); t.print();t.printLevels();
	return 0;
}