#include <iostream>
using namespace std;

template<typename T>
class Pila {
private:
    T* A;
    T* top;
    T* A_fin;

public:
    Pila(int n = 10) {
        A = new T[n];
        top = nullptr;
        A_fin = A + n;
    }

    ~Pila() {
        delete[] A;
    }

    bool vacio() const {
        return top == nullptr;
    }

    bool lleno() const {
        return top == A_fin - 1;
    }

    bool Push(const T& dato) {
        if (lleno()) {
            return false;
        }
        if (vacio()) {
            top = A;
        } else {
            top++;
        }
        *top = dato;
        return true;
    }

    bool Pop(T& dato) {
        if (vacio()) {
            return false;
        }
        dato = *top;
        if (top == A) {
            top = nullptr;
        } else {
            top--;
        }
        return true;
    }

    void imprimir() const {
        if (vacio()) {
            cout << "(vacia)";
        } else {
            for (T* ptr = A; ptr <= top; ptr++) {
                cout << *ptr << " ";
            }
        }
        cout << endl;
    }
};

int main() {
    Pila<int> miPila(5);

    cout << "Estado inicial de la pila: ";
    miPila.imprimir();

    miPila.Push(5);
    miPila.Push(10);
    miPila.Push(15);

    miPila.imprimir();

    int valor_sacado;
    if (miPila.Pop(valor_sacado)) {
        cout << "Pop de Pila: " << valor_sacado << endl;
    } else {
        cout << "Pila vacia" << endl;
    }

    miPila.imprimir();
    
    miPila.Push(20);
    miPila.Push(25);
    
    miPila.imprimir();
    
    if (miPila.lleno()){
        cout << "La pila esta llena." << endl;
    }

    if (!miPila.Push(99)){
        cout << "No se pudo agregar 99, la pila esta llena." << endl;
    }

    while(miPila.Pop(valor_sacado)){
         cout << "Pop de Pila: " << valor_sacado << endl;
    }

    cout << "Estado final de la pila: ";
    miPila.imprimir();

    return 0;
}