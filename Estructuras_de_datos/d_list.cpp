#include <iostream>
using namespace std;

struct Node{
	int v;
	Node* right;
	Node* left;
	Node(int x){
		v = x;
		right = left = 0;
	}
};

class Dlist{
	Node * head;
	Node * tail;
    int numelems;
public:
	Dlist();
	~Dlist();
	void push_back(int x);
	void push_front(int x);
	void pop_back();
	void pop_front();
	int& operator[](int x);
	void print();
};
Dlist::Dlist(){
	head = tail =0;
    numelems = 0; 
}
Dlist::~Dlist(){
	Node * p = head;
	while(p){
		head = head->right;
		delete p;
		p = head;
	}
}
	void Dlist::push_back(int x){
		Node* t = new Node(x);
		if(tail){
			t->left = tail;
			tail->right = t;
		}
		else{
			head = t;
		}
		tail = t;
        numelems++;
	}
	void Dlist::push_front(int x){
		Node* t = new Node(x);
		if(head){
			t->right = head;
			head->left = t;
		}
		else{
			tail = t;
		}
		head= t;
        numelems++;
	}
	void Dlist::pop_back(){
		if(!tail) return;
		Node * tmp = tail;
		tail = tail->left;
		if(tail){
			tail->right = 0;
		}
		else{
			head = 0;
		}
		delete tmp;
        numelems--;
	}
	void Dlist::pop_front(){
		if(!head) return;
		Node * tmp = head;
		head = head->right;
		if(head){
			head->left = 0;
		}
		else{
			tail = 0;
		}
		delete tmp;
        numelems--;
	}
	int& Dlist::operator[](int x){
		if(x < 0 || x >= numelems) throw runtime_error("Fuera de rango");
		Node** p = &head;
		while(x--){
			p = &((*p)->right);
		}
		return (*p)->v;
	}
	void Dlist::print(){
		Node** p = &head;
		while((*p) != 0){
			cout << (*p)->v << ' '; 
			p = &((*p)->right);
		}
		cout << "\n";
	}
	int main(){
		
		Dlist l;
		l.push_back(1);
		l.push_back(4);
		l.push_back(5);
		l.push_front(8);
		l.push_front(9);
		l.print();
		l.pop_back(); 
		l.pop_front();
		l.print();
		l[1] = 5;
		l.print();
		
		
		return 0;
	}
