#include <iostream>
using namespace std;

template<typename T>
class Cola {
private:
    T* A;
    int* frente;
    int* final;
    static const int tamañoarreglo = 10;

public:
    Cola() {
        A = new T[tamañoarreglo];
        frente = new int(0);
        final = new int(0);
    }

    ~Cola() {
        delete[] A;
        delete frente;
        delete final;
    }

    bool vacio() {
        return *frente == *final;
    }

    bool lleno() {
        return (*final + 1) % tamañoarreglo == *frente;
    }

    bool Push(const T& a) {
        if (lleno()) return false;
        A[*final] = a;
        *final = (*final + 1) % tamañoarreglo;
        return true;
    }

    bool Pop(T& a) {
        if (vacio()) return false;
        a = A[*frente];
        *frente = (*frente + 1) % tamañoarreglo;
        return true;
    }

    void imprimir() {
        int i = *frente;
        while (i != *final) {
            cout << A[i] << " ";
            i = (i + 1) % tamañoarreglo;
        }
        cout << endl;
    }

    int getFrente() {
        return *frente;
    }

    int getFinal() {
        return *final;
    }
};

template<typename T>
struct Pila {
    T A[10];
    T* top = nullptr;

    bool vacio() {
        return !top;
    }

    bool lleno() {
        return top == A + 9;
    }

    bool Push(const T& a) {
        if (lleno()) return false;
        if (!top) top = A;
        else top++;
        *top = a;
        return true;
    }

    bool Pop(T& a) {
        if (vacio()) return false;
        a = *top;
        top--;
        if (top < A) top = nullptr;
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
    using namespace std;

    Cola<int> c;
    c.Push(7);
    c.Push(2);
    c.Push(1);
    cout << "Estado inicial de cola: ";
    c.imprimir();
    if(c.Push(8)) cout << "Push(8): " << endl;
    c.imprimir();

    int y;
    if (c.Pop(y)) cout << "Pop(" << y << ")"<< endl;
    c.imprimir();

    cout << "Frente: " << c.getFrente() << ", Final: " << c.getFinal() << endl;

    cout << endl;

    Pila<int> p;
    p.Push(5);
    p.Push(10);
    p.Push(15);
    cout << "Estado inicial de pila: ";
    p.imprimir();

    int x;
    if (p.Pop(x)) cout << "Pop(" << x << ")"<< endl;
    p.imprimir();

    return 0;
}