#include <iostream>
using namespace std;

struct Node
{
    int v;
    Node * sgnt;
    Node(int x);
};

class Flist
{
private:
    Node * head;
    int numelems;
public:
    Flist();
    ~Flist();
    void push_back(int x);
    void push_front(int x);
    void pop_back();
    void pop_front();
    int& operator[](int x);
    void print();
};

Node::Node(int x){
    v = x;
    sgnt = 0;
}

Flist::Flist(){
    head = 0;
    numelems = 0;
}

Flist::~Flist(){
    cout << "Comienza liberacion" << endl;
    Node* p;
    while(head){
        p = head;
        head = head->sgnt;
        delete p;
        this->print();
    }
    cout << "Se libero la memoria correctamente" << endl;
}

void Flist::push_back(int x){
    Node** p = &head;
    Node* t = new Node(x);
    while(*p){
        p = &((*p)->sgnt);
    }
    *p = t;
    numelems++;
}

void Flist::push_front(int x){
    Node* t = new Node(x);
    t->sgnt = head;
    head = t;
    numelems++;
}

void Flist::pop_back(){
    if(head){
        Node** p = &head;
        while((*p)->sgnt){
            p = &((*p)->sgnt);        
        }
        delete (*p);
        *p = 0;
        numelems--;          
    }
    else{cout << "Lista vacia" << endl;}
}

void Flist::pop_front(){
    if(head){
        Node * p = head;
        head = head->sgnt;
        delete p;
        numelems--;
    }
    else{cout << "Lista vacia" << endl;}
}

int& Flist::operator[](int x){
    if(x >= numelems)
        throw runtime_error("Fuera de rango");

    Node** p = &head;
    for(int i = 0;i < x; i++){
        p = &((*p)->sgnt);
    }
    return (*p)->v;
}

void Flist::print(){
    Node** p = &head;
    while(*p){
        cout << (*p)->v << ' ';
        p = &((*p)->sgnt);
    }
    cout << endl;
}


int main(){

    return 0;
}