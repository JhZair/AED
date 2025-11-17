#include <iostream>
#include <stack>
#include <queue>
using namespace std;

struct Node{
	int v;
	Node* left;
	Node* right;
	Node(int _v){
		left = right = 0;
		v = _v;
	}
};

class BinaryTree{
	Node* root;
	bool lado_reemp;
public:
	BinaryTree();
	~BinaryTree();
	bool insrt(int x);
	bool remv(int x);
	Node** fnd_reemp(Node** p);
	bool find(int x, Node**& p);
	void print();
	void inorder(Node* p);
	void inorderST();
	void Levels(Node* p);
	void PrintLevels();
	int alturaMax();
	void altr_maxI(Node* p, int cont, int& max);
	int altr_maxR(Node* p);
	void clear(Node* p);
	Node* get_root(){return root;}
};

BinaryTree::BinaryTree(){
	root = 0;
	lado_reemp = 0;
}
BinaryTree::~BinaryTree(){
	cout << "Comienza liberacion" << endl;
	this->clear(root);
	root = 0;
	cout << "Termina liberacion" << endl;
}
bool BinaryTree::insrt(int x){
	Node** p = &root;
	if(find(x, p)) return 0;
	*p = new Node(x);
	return 1;
}
bool BinaryTree::remv(int x){
	Node** p = &root;
	if(!find(x, p)) return 0;
	if((*p)->left && (*p)->right){
		Node** q = fnd_reemp(p);
		(*p)->v = (*q)->v;
		p = q;
	}
	Node* t= *p;
	if((*p)->left)
		*p = (*p)->left;
	else
		*p = (*p)->right;
	delete t;
	return 1;
}
Node** BinaryTree::fnd_reemp(Node** p){
	Node** q = p;
	if(lado_reemp){
		q = &((*q)->left);
		while((*q)->right)
			q = &((*q)->right);
	}
	else{
		q = &((*q)->right);
		while((*q)->left)
			q = &((*q)->left);
	}
	lado_reemp = !lado_reemp;
	return q;
}
bool BinaryTree::find(int x, Node**& p){
	while(*p && (*p)->v != x){
		if(x < (*p)->v)
			p = &((*p)->left);
		else
			p = &((*p)->right);
	}
	return *p;
}
void BinaryTree::print(){
	inorder(root);
	cout << endl;
}
void BinaryTree::inorder(Node* p){
	if(!p) return;
	inorder(p->left);
	cout << p->v << ' ';
	inorder(p->right);
}
void BinaryTree::inorderST(){
	std::stack<Node*> pila;
	Node* actual = root;
	std::cout << "In-Orden con Stack: ";	
	while (actual != 0 || !pila.empty()) {
		while (actual != 0) {
			pila.push(actual);
			actual = actual->left;
		}
		actual = pila.top();
		pila.pop();
		std::cout << actual->v << " ";
		actual = actual->right;
	}
	std::cout << std::endl;
}
void BinaryTree::Levels(Node* p){
	if(!p) return;
	queue<Node*> q;
	q.push(p);
	while(!q.empty()){
		Node* c = q.front();
		cout << c->v << ' ';
		if(c->left) q.push(c->left);
		if(c->right) q.push(c->right);
		q.pop();
	}
}
void BinaryTree::PrintLevels(){
	cout << endl;
	Levels(root);
	cout << endl;
}
int BinaryTree::alturaMax(){
	int max = 0;
	altr_maxI(root, 0, max);
	return max;
}
void BinaryTree::altr_maxI(Node* p, int cont, int& max){
	if(!p){
		if(max < cont)
			max = cont;
		return;
	}
	altr_maxI(p->left, cont+1, max);
	altr_maxI(p->right, cont+1, max);
}
int BinaryTree::altr_maxR(Node* p){
	if (!p) return 0;
	int l = altr_maxR(p->left);
	int r = altr_maxR(p->right);
	return std::max(l,r)+1;
}

void BinaryTree::clear(Node* p){
	if(!p) return;
	clear(p->left);
	clear(p->right);
	delete p;
	cout << "se elimino nodo" << endl;
}

int main(){
	BinaryTree t;
	t.insrt(60); t.print();
	t.insrt(30); t.print();
	t.insrt(70); t.print();
	t.insrt(20); t.print();
	t.insrt(40); t.print();
	t.insrt(65); t.print(); t.inorderST();
	t.insrt(80); t.print();
	t.insrt(75); t.print();
	t.remv(20); t.print();
	t.remv(40); t.print();
	t.remv(65); t.print();
	t.remv(60); t.print();
	cout << t.alturaMax() << endl;
	cout << t.altr_maxR(t.get_root()) << endl;
	t.PrintLevels();
	return 0;
}
