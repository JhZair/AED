#include <iostream>
using namespace std;

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

    bool vacio() const {
        return inicio == fin;
    }

    bool lleno() const {
        return (fin + 1 == A_fin ? A : fin + 1) == inicio;
    }

    bool Push(const T& dato) {
        if (lleno()) return false;
        *fin = dato;
        fin = (fin + 1 == A_fin) ? A : fin + 1;
        return true;
    }

    bool Pop(T& dato) {
        if (vacio()) return false;
        dato = *inicio;
        inicio = (inicio + 1 == A_fin) ? A : inicio + 1;
        return true;
    }

    void imprimir() const {
        if (vacio()){
            cout << "(vacia)";
        }
        const T* i = inicio;
        while (i != fin) {
            cout << *i << " ";
            i = (i + 1 == A_fin) ? A : i + 1;
        }
        cout << endl;
    }
};

int main() {
    Cola<int> miCola(5);

    cout << "Estado inicial de la cola: ";
    miCola.imprimir();

    miCola.Push(10);
    miCola.Push(20);
    miCola.Push(30);

    miCola.imprimir();

    int valor_sacado;
    if (miCola.Pop(valor_sacado)) {
        cout << "Pop de Cola: " << valor_sacado << endl;
    } else {
        cout << "Cola vacia" << endl;
    }

    miCola.imprimir();

    miCola.Push(40);
    miCola.Push(50);

    miCola.imprimir();

    if (miCola.Pop(valor_sacado)) {
        cout << "Pop de Cola: " << valor_sacado << endl;
    }
    
    miCola.Push(60);
    cout << "Cola: ";
    miCola.imprimir();

    if (miCola.lleno()){
        cout << "La cola esta llena." << endl;
    }

    if (!miCola.Push(99)){
        cout << "No se pudo agregar 99, la cola esta llena." << endl;
    }

    while(miCola.Pop(valor_sacado)){
         cout << "Pop de Cola: " << valor_sacado << endl;
    }

    cout << "Estado final de la cola: ";
    miCola.imprimir();

    return 0;
}