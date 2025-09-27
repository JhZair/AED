#include <iostream>
using namespace std;

//void Merge(Node * A, Node * B){
//		
//}

struct Node{
	int value;
	Node * next;
	Node(int v){
		value = v;
		next = 0;
	}
};


class SList{
	Node * head;
	int numelems;
	
public:
	SList(){
		head = 0;
		numelems = 0;
	}
	~SList(){
		
	}
	void push_back(int vlue){
		Node * t = new Node (vlue);
		Node ** p = &head;
		while(*p && (*p)->next){
			p = &((*p)->next);
		}
		*p = t;
	}
	void imprimir(){
		Node ** p = &head;
		while(*p && (*p)->next){
			p = &((*p)->next);
			cout << (*p)->value << endl;
		}
	}
	
};



int main(int argc, char *argv[]) {
	
	SList A;
	A.push_back(3);
	A.push_back(5);
	A.push_back(9);
//	l.imprimir();
	
	SList B;
	B.push_back(4);
	B.push_back(7);
	B.push_back(8);
//	l.imprimir();
	
	return 0;
}

