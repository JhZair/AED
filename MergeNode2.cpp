#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* next;
    Node* prev;

    Node(int valor) {
        data = valor;
        next = nullptr;
        prev = nullptr;
    }
};

class ListaDoble {
private:
    Node* head;
    Node* tail;

public:
    ListaDoble() {
        head = nullptr;
        tail = nullptr;
    }

    ~ListaDoble() {
        Node* actual = head;
        while (actual != nullptr) {
            Node* siguiente = actual->next;
            delete actual;
            actual = siguiente;
        }
    }

    void insertar(int valor) {
        Node* nuevo = new Node(valor);
        if (head == nullptr) {
            head = nuevo;
            tail = nuevo;
            return;
        }
        if (valor < head->data) {
            nuevo->next = head;
            head->prev = nuevo;
            head = nuevo;
            return;
        }
        
        Node* actual = head;
        while (actual->next != nullptr && actual->next->data < valor) {
            actual = actual->next;
        }
        
        if (actual->next == nullptr) {
            tail->next = nuevo;
            nuevo->prev = tail;
            tail = nuevo;
        } else {
            nuevo->next = actual->next;
            actual->next->prev = nuevo;
            actual->next = nuevo;
            nuevo->prev = actual;
        }
    }

    void imprimir() {
        if (head == nullptr) {
            cout << "(Lista vacia)";
        }
        Node* temp = head;
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    Node* getHead() { return head; }
    void setHead(Node* n) { head = n; }
    void setTail(Node* n) { tail = n; }
};

void merge(Node* a, Node* b) {
    if (a == nullptr || b == nullptr) {
        return;
    }

    Node* p1 = a;
    Node* p2 = b;
    
    while (p1 != nullptr && p2 != nullptr) {
        if (p1->data <= p2->data) {
            if (p1->next == nullptr) {
                p1->next = p2;
                p2->prev = p1;
                p2 = nullptr;
            } else {
                p1 = p1->next;
            }
        } else {
            Node* temp = p2->next;
            p1->prev->next = p2;
            p2->prev = p1->prev;
            p2->next = p1;
            p1->prev = p2;
            p2 = temp;
        }
    }
}


int main() {
    ListaDoble A;
    ListaDoble B;

    A.insertar(25);
    A.insertar(12);
    A.insertar(41);
    A.insertar(33);
    A.insertar(53);

    B.insertar(45);
    B.insertar(28);
    B.insertar(68);
    B.insertar(49);

    cout << "Lista A: ";
    A.imprimir();
    cout << "Lista B: ";
    B.imprimir();
    
    Node* head_a = A.getHead();
    Node* head_b = B.getHead();

    if (head_a != nullptr && head_b != nullptr) {
        
        Node* nuevo_head = nullptr;
        if (head_a->data <= head_b->data) {
            nuevo_head = head_a;
            merge(head_a, head_b);
        } else {
            nuevo_head = head_b;
            merge(head_b, head_a);
        }

        A.setHead(nuevo_head);

        Node* nuevo_tail = nuevo_head;
        while (nuevo_tail != nullptr && nuevo_tail->next != nullptr) {
            nuevo_tail = nuevo_tail->next;
        }
        A.setTail(nuevo_tail);

        if (head_a->data <= head_b->data) {
            B.setHead(nullptr);
            B.setTail(nullptr);
        } else {
            B.setHead(nullptr);
            B.setTail(nullptr);
        }
    }

    cout << "Lista A: ";
    A.imprimir();
    cout << "Lista B: ";
    B.imprimir();

    return 0;
}