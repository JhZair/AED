#include <iostream>
#include <vector>
using namespace std;

template<class T, class C>
class Pila{
    int numelems;
    C l;
public:
    Pila(){
        numelems = 0;
    }
    void push(T x){
        l.push_back(x);
        numelems++;
    }
    void pop(){
        if(!numelems){
            throw runtime_error("Sin elementos");
        }
        l.pop_back();
        numelems--;
    }
    T& top(){
        if(!numelems){
            throw runtime_error("Sin elementos");
        }
        return l.back();
    }
    bool empty(){
        return l.empty();
    }
    int size(){
        return numelems;
    }
    void print(){
        for(int i=0; i<numelems;i++){
            cout << l[i] << ' ';
        }
        cout << endl;
    }
};


int main(){
    
    Pila<int, vector<int>> p;

    cout <<  p.size() << endl;
    p.push(4);
    p.push(6);
    p.push(7);
    p.push(1);
    p.print();
    p.pop();
    p.push(3);
    p.push(4);
    p.print();
    p.pop();
    p.pop();
    p.pop();

    p.top() = 5;
    p.print();
    cout << p.empty() << endl;

    return 0;
}