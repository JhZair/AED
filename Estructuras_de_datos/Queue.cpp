#include <iostream>
#include <deque>
using namespace std;

template<class T, class C>
class Queue{
    int numelems;
    C l;
public:
    Queue(){
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
        l.pop_front();
        numelems--;
    }
    T& top(){
        if(!numelems){
            throw runtime_error("Sin elementos");
        }
        return l.back();
    }
    T& back(){
        if(!numelems){
            throw runtime_error("Sin elementos");
        }
        return l.front();
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
    
    Queue<int, deque<int>> q;

    cout <<  q.size() << endl;
    q.push(4);
    q.push(6);
    q.push(7);
    q.push(1);
    q.print();
    q.pop();
    q.push(3);
    q.push(4);
    q.print();
    q.pop();
    q.pop();

    q.top() = 5;
    q.back() = 2;
    q.print();
    cout << q.empty() << endl;

    return 0;
}