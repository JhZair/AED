#include <iostream>
#include <cmath>
#include <vector>
#include <string> 
#include <SFML/Graphics.hpp>

using namespace std;

const float VENTANA_ANCHO = 1800;
const float VENTANA_ALTO = 900;
const float RADIO_NODO = 22.0f;
const float ESPACIO_Y = 150.0f; 
const float ESPACIO_X = 100.0f;

struct Node {
    int v;
    Node* left;
    Node* right;
    float x, y; 

    Node(int v) : v(v), left(nullptr), right(nullptr), x(0), y(0) {}
    Node(Node* L, Node* R) : v(L->v + R->v), left(L), right(R), x(0), y(0) {}
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
    Cola<Node*> C(n);
    for (int* p = ini; p != fin; p++) {
        Node* elem = new Node(*p);
        C.Push(elem);
    }
    while(true) {
        Node *a, *b;
        if(!C.Pop(a)) {
            return nullptr;
        }
        if(!C.Pop(b)) {
            return a;
        }
        Node* elem = new Node(a, b);
        C.Push(elem);
    }
    return nullptr;
}

void posicionesRecursivo(Node* nodo, int level, int& index) {
    if (nodo == nullptr) {
        return;
    }

    posicionesRecursivo(nodo->left, level+1, index);

    nodo->y = (level*ESPACIO_Y)+ESPACIO_Y; 
    nodo->x = index*ESPACIO_X; 
    index++;

    posicionesRecursivo(nodo->right, level + 1, index);
}

void liberarMemoria(Node* nodo) {
    if (nodo == nullptr) {
        return;
    }
    liberarMemoria(nodo->left);
    liberarMemoria(nodo->right);
    delete nodo;
}

void configPosiciones(Node* root) {
    int index_horizontal = 1; 
    posicionesRecursivo(root, 0, index_horizontal);
}

void construirLineas(Node* nodo, sf::VertexArray& lines) {
    if (nodo == nullptr) return;

    if (nodo->left) {
        lines.append(sf::Vertex(sf::Vector2f(nodo->x, nodo->y), sf::Color::White));
        lines.append(sf::Vertex(sf::Vector2f(nodo->left->x, nodo->left->y), sf::Color::White));
        construirLineas(nodo->left, lines);
    }

    if (nodo->right) {
        lines.append(sf::Vertex(sf::Vector2f(nodo->x, nodo->y), sf::Color::White));
        lines.append(sf::Vertex(sf::Vector2f(nodo->right->x, nodo->right->y), sf::Color::White));
        construirLineas(nodo->right, lines);
    }
}

void dibujarNodos(sf::RenderWindow& window, Node* nodo, sf::CircleShape& shape, sf::Text& text) {
    if (nodo == nullptr) return;

    shape.setPosition(nodo->x, nodo->y);
    window.draw(shape);

    text.setString(std::to_string(nodo->v));

    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
    text.setPosition(nodo->x, nodo->y);
    window.draw(text);

    dibujarNodos(window, nodo->left, shape, text);
    dibujarNodos(window, nodo->right, shape, text);
}

int main() { 
    int const n = 8;
    int array[n] = {1,2,3,4,5,6,7,8};
    Node* root = CrearArbol(array, array + n);

    if (root != nullptr) {
        cout << "root: " << root->v << endl;
    } else {
        cerr << "Error" << endl;
        return -1;
    }

    sf::RenderWindow window(sf::VideoMode(VENTANA_ANCHO, VENTANA_ALTO), "Arbol de Suma");
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.loadFromFile("../z_fonts/ARIAL.TTF")) { 
        cerr << "No se pudo cargar la fuente" << endl;
        liberarMemoria(root);
        return -1;
    }

    configPosiciones(root);

    sf::VertexArray lines(sf::Lines);
    construirLineas(root, lines);

    sf::CircleShape nodo(RADIO_NODO);
    nodo.setFillColor(sf::Color::Green);
    nodo.setOutlineColor(sf::Color::Green);
    nodo.setOutlineThickness(2.0f);
    nodo.setOrigin(RADIO_NODO, RADIO_NODO);

    sf::Text valorNodo;
    valorNodo.setFont(font);
    valorNodo.setCharacterSize(16);
    valorNodo.setFillColor(sf::Color::Black);


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black); 
        window.draw(lines);
        dibujarNodos(window, root, nodo, valorNodo);
        window.display();
    }

    liberarMemoria(root);

    return 0;
}