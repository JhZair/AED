#include <iostream>

using namespace std;

template<typename T>
class Pila {
private:
    T A[10];
    T* top;

public:
    Pila() {
        top = nullptr;
    }

    bool vacio() {
        return !top;
    }

    bool lleno() {
        return top == A + 9;
    }

    bool push(T a) {
        if (lleno()) {
            return false;
        }
        if (!top) {
            top = A;
        } else {
            top++;
        }
        *top = a;
        return true;
    }

    bool pop(T& a) {
        if (vacio()) {
            return false;
        }
        a = *top;
        if (top == A) {
            top = nullptr;
        } else {
            top--;
        }
        return true;
    }

    void imprimir() {
        if (vacio()) {
            cout << "Pila vacia" << endl;
        } else {
            for (T* ptr = A; ptr <= top; ptr++) {
                cout << *ptr << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    Pila<int> pila;

    pila.imprimir();

    pila.push(5);
    pila.push(10);
    pila.push(15);
    cout << "Estado inicial de pila: ";
    pila.imprimir();

    int vlr_sacado;
    if (pila.pop(vlr_sacado)) cout << "Pop: " << vlr_sacado << endl;
    
    pila.imprimir();

    if (pila.pop(vlr_sacado)) cout << "Pop de Pila: " << vlr_sacado << endl;


    if (pila.pop(vlr_sacado)) cout << "Pop de Pila: " << vlr_sacado << endl;


    cout << "Estado final de la pila: ";
    pila.imprimir();

    return 0;
}