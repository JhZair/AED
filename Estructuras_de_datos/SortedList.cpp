#include <iostream>
using namespace std;

struct Node
{
    int v;
    Node * next;
    Node(int x);
};

class SFlist
{
private:
    Node * head;
    int numelems;
public:
    SFlist();
    ~SFlist();
    bool fnd(int x, Node**& p);
    bool rmv(int x);
    bool insrt(int x);
    void print();
};

Node::Node(int x){
    v = x;
    next = 0;
}

SFlist::SFlist(){
    head = 0;
    numelems = 0;
}

SFlist::~SFlist(){
    cout << "Comienza liberacion" << endl;
    Node* p;
    while(head){
        p = head;
        head = head->next;
        delete p;
        this->print();
    }
    cout << "Se libero la memoria correctamente" << endl;
}

bool SFlist::fnd(int x, Node**& p){
    while(*p && (*p)->v < x){
        p = &((*p)->next);
    }
    return *p && (*p)->v == x;
}

bool SFlist::rmv(int x){
    Node** p = &head;
    if(!fnd(x, p)) return 0;
    Node * t = *p;
    *p = t->next;
    delete t;
    return 1;
}

bool SFlist::insrt(int x){
    Node** p = &head;
    if(fnd(x, p)) return 0;
    Node * t = new Node(x);
    t->next = *p;
    *p = t;
    return 1;
}

void SFlist::print(){
    Node** p = &head;
    while(*p){
        cout << (*p)->v << ' ';
        p = &((*p)->next);
    }
    cout << endl;
}

int main(){

    SFlist l;
    l.insrt(11); l.print();
    l.insrt(7); l.print();
    l.insrt(4); l.print();
    l.insrt(13); l.print();
    l.insrt(10); l.print();
    l.insrt(2); l.print();
    l.insrt(17); l.print();
    l.rmv(10); l.print();
    l.rmv(2); l.print();
    l.rmv(17); l.print();
    l.rmv(4); l.print();
    l.rmv(11); l.print();
    l.rmv(13); l.print();
    l.rmv(7); l.print();

    return 0;

}