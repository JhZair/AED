#include <iostream>
using namespace std;

struct Node {
    int v;
    Node* left;
    Node* right;
    Node(int _v){
        v = _v; 
        left = nullptr;
        right = nullptr;
    }
    Node(Node* L, Node* R){ 
        v = L->v + R->v;
        left = L;
        right = R; 
    }
};

template<typename T>
class Cola {
private:
    T* A;
    T* inicio;
    T* fin;
    T* A_fin;

public:
    Cola(int n = 10) {
        A = new T[n + 1];
        inicio = A;
        fin = A;
        A_fin = A + n + 1;
    }

    ~Cola() { delete[] A; }

    bool Empty() {
        return inicio == fin;
    }

    bool Filled() {
        return (fin + 1 == A_fin ? A : fin + 1) == inicio;
    }

    bool Push(T dato) {
        if (Filled()) return false;
        *fin = dato;
        fin = (fin + 1 == A_fin) ? A : fin + 1;
        return true;
    }

    bool Pop(T& dato) {
        if (Empty()) return false;
        dato = *inicio;
        inicio = (inicio + 1 == A_fin) ? A : inicio + 1;
        return true;
    }
};

Node* CrearArbol(int* ini, int* fin) {
    int n = fin - ini;
    if(n==0){   
        return nullptr;
    }   
    if(n==1){
        return new Node(*ini);
    }
    int* mid = ini+n/2;                                             
    Node* hijo_izq = CrearArbol(ini, mid); 
    Node* hijo_derecho = CrearArbol(mid, fin); 
     
    return new Node(hijo_izq, hijo_derecho);
}

void print(Node* root) {
    if(!root) {
        return; 
    }
    Cola<Node*> C(100);
    C.Push(root);
    C.Push(nullptr);

    while(!C.Empty()) {    
        Node* actual;
        C.Pop(actual);

        if(actual == nullptr) {
            cout << "\n";
            if (!C.Empty()) {
                C.Push(nullptr);
            }       
        }
        else{    
            cout << actual->v << " ";
            if(actual->left) {
                C.Push(actual->left);
            }
            if(actual->right) {    
                C.Push(actual->right);
            }
        }
    }
}   

int main() {
    int array[8] = {1,2,3,4,5,6,7,8};
    Node* root = CrearArbol(array, array + 8);  

    cout << "Arbol: " << endl;
    print(root);

    return 0;
}