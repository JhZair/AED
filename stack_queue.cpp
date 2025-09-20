#include <iostream>

using namespace std;

template<class T, int MAX>
struct Pila {
    T A[MAX];
    int top;

    Pila() {
        top = -1;
    }

    bool vacia() {
        return top == -1;
    }

    bool llena() {
        return top == MAX - 1;
    }

    bool push(T valor) {
        if (llena()) {
            cout << "la pila esta llena." << endl;
            return false;
        }
        top++;
        A[top] = valor;
        return true;
    }

    bool pop(T &valor) {
        if (vacia()) {
            cout << "La pila esta vacia." << endl;
            return false;
        }
        valor = A[top];
        top--;
        return true;
    }
};

template<class T, int MAX>
struct Cola {
    T A[MAX];
    int frente;
    int final;
    int contador;

    Cola() {
        frente = 0;
        final = 0;
        contador = 0;
    }

    bool vacia() {
        return contador == 0;
    }

    bool llena() {
        return contador == MAX;
    }

    bool push(T valor) {
        if (llena()) {
            cout << "la cola esta llena" << endl;
            return false;
        }
        A[final] = valor;
        final = (final + 1) % MAX;
        contador++;
        return true;
    }

    bool pop(T &valor) {
        if (vacia()) {
            cout << "la cola esta vacia" << endl;
            return false;
        }
        valor = A[frente];
        frente = (frente + 1) % MAX;
        contador--;
        return true;
    }
};

int main() {
    Pila<int, 5> miPila;

    cout << "10, 20, 30" << endl;
    miPila.push(10);
    miPila.push(20);
    miPila.push(30);

    int valor;
    miPila.pop(valor);
    cout << "Se saco el valor " << valor << endl;

    miPila.pop(valor);
    cout << "Se saco el valor " << valor << endl;

    Cola<string, 4> miCola;

    miCola.push("A");
    miCola.push("B");
    miCola.push("C");

    string valor2;
    miCola.pop(valor2);
    cout << "Se saco el valor '" << valor2 << "'" << endl;
    
    miCola.pop(valor2);
    cout << "Se saco el valor '" << valor2 << "'" << endl;

    miCola.push("D");

    miCola.pop(valor2);
    cout << "Se saco el valor '" << valor2 << "'" << endl;

    return 0;
}