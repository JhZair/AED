#include <iostream>
#include <queue>
#include <stack>
#include <algorithm>
#include <cmath>
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
    Node *left, *right, *parent;
    bool is_red;
    float x, y;

    Node(int val) : v(val), is_red(true), left(nullptr), right(nullptr), parent(nullptr), x(0), y(0) {}
};

class RBTree {
private:
    Node* root;
    Node* NIL;

    void rotarIzq(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        if (y->left != NIL) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == NIL) {
            root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    void rotarDerecha(Node* x) {
        Node* y = x->left;
        x->left = y->right;
        if (y->right != NIL) {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == NIL) {
            root = y;
        } else if (x == x->parent->right) {
            x->parent->right = y;
        } else {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }

    void ins_fix(Node* z) {
        while (z->parent->is_red) {
            if (z->parent == z->parent->parent->left) {
                Node* y = z->parent->parent->right;
                if (y->is_red) {
                    z->parent->is_red = false;
                    y->is_red = false;
                    z->parent->parent->is_red = true;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->right) {
                        z = z->parent;
                        rotarIzq(z);
                    }
                    z->parent->is_red = false;
                    z->parent->parent->is_red = true;
                    rotarDerecha(z->parent->parent);
                }
            } else {
                Node* y = z->parent->parent->left;
                if (y->is_red) {
                    z->parent->is_red = false;
                    y->is_red = false;
                    z->parent->parent->is_red = true;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->left) {
                        z = z->parent;
                        rotarDerecha(z);
                    }
                    z->parent->is_red = false;
                    z->parent->parent->is_red = true;
                    rotarIzq(z->parent->parent);
                }
            }
        }
        root->is_red = false;
    }

    void transplant(Node* u, Node* v) {
        if (u->parent == NIL) {
            root = v;
        } else if (u == u->parent->left) {
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
        v->parent = u->parent;
    }

    Node* minimum(Node* n) {
        while (n->left != NIL) {
            n = n->left;
        }
        return n;
    }

    void remv_fix(Node* x) {
        while (x != root && !x->is_red) {
            if (x == x->parent->left) {
                Node* w = x->parent->right;
                if (w->is_red) {
                    w->is_red = false;
                    x->parent->is_red = true;
                    rotarIzq(x->parent);
                    w = x->parent->right;
                }
                if (!w->left->is_red && !w->right->is_red) {
                    w->is_red = true;
                    x = x->parent;
                } else {
                    if (!w->right->is_red) {
                        w->left->is_red = false;
                        w->is_red = true;
                        rotarDerecha(w);
                        w = x->parent->right;
                    }
                    w->is_red = x->parent->is_red;
                    x->parent->is_red = false;
                    w->right->is_red = false;
                    rotarIzq(x->parent);
                    x = root;
                }
            } else {
                Node* w = x->parent->left;
                if (w->is_red) {
                    w->is_red = false;
                    x->parent->is_red = true;
                    rotarDerecha(x->parent);
                    w = x->parent->left;
                }
                if (!w->right->is_red && !w->left->is_red) {
                    w->is_red = true;
                    x = x->parent;
                } else {
                    if (!w->left->is_red) {
                        w->right->is_red = false;
                        w->is_red = true;
                        rotarIzq(w);
                        w = x->parent->left;
                    }
                    w->is_red = x->parent->is_red;
                    x->parent->is_red = false;
                    w->left->is_red = false;
                    rotarDerecha(x->parent);
                    x = root;
                }
            }
        }
        x->is_red = false;
    }

    Node* find(int v) {
        Node* n = root;
        while (n != NIL && n->v != v) {
            n = (v < n->v) ? n->left : n->right;
        }
        return n;
    }

    void clear(Node* n) {
        if (n != NIL) {
            clear(n->left);
            clear(n->right);
            delete n;
        }
    }

    void posicionesRecursivo(Node* nodo, int level, int& index) {
        if (nodo == NIL) {
            return;
        }
        posicionesRecursivo(nodo->left, level + 1, index);
        nodo->y = (level * ESPACIO_Y) + ESPACIO_Y;
        nodo->x = index * ESPACIO_X;
        index++;
        posicionesRecursivo(nodo->right, level + 1, index);
    }

    void configPosiciones() {
        int index_horizontal = 1;
        posicionesRecursivo(root, 0, index_horizontal);
    }

    void construirLineas(Node* nodo, sf::VertexArray& lines) {
        if (nodo == NIL) return;

        if (nodo->left != NIL) {
            lines.append(sf::Vertex(sf::Vector2f(nodo->x, nodo->y), sf::Color::White));
            lines.append(sf::Vertex(sf::Vector2f(nodo->left->x, nodo->left->y), sf::Color::White));
            construirLineas(nodo->left, lines);
        }

        if (nodo->right != NIL) {
            lines.append(sf::Vertex(sf::Vector2f(nodo->x, nodo->y), sf::Color::White));
            lines.append(sf::Vertex(sf::Vector2f(nodo->right->x, nodo->right->y), sf::Color::White));
            construirLineas(nodo->right, lines);
        }
    }

    void dibujarNodos(sf::RenderWindow& window, Node* nodo, sf::CircleShape& shape, sf::Text& text) {
        if (nodo == NIL) return;

        shape.setFillColor(nodo->is_red ? sf::Color::Red : sf::Color::Black);
        shape.setOutlineColor(sf::Color::White);
        shape.setPosition(nodo->x, nodo->y);
        window.draw(shape);

        text.setString(std::to_string(nodo->v));
        sf::FloatRect bounds = text.getLocalBounds();
        text.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
        text.setFillColor(sf::Color::White);
        text.setPosition(nodo->x, nodo->y);
        window.draw(text);

        dibujarNodos(window, nodo->left, shape, text);
        dibujarNodos(window, nodo->right, shape, text);
    }

public:
    RBTree() {
        NIL = new Node(0);
        NIL->is_red = false;
        root = NIL;
    }

    ~RBTree() {
        clear(root);
        delete NIL;
    }

    bool ins(int v) {
        Node* z = new Node(v);
        z->left = NIL;
        z->right = NIL;
        z->parent = NIL;

        Node* y = NIL;
        Node* x = root;

        while (x != NIL) {
            y = x;
            if (z->v == x->v) {
                delete z;
                return false;
            }
            x = (z->v < x->v) ? x->left : x->right;
        }

        z->parent = y;
        if (y == NIL) {
            root = z;
        } else if (z->v < y->v) {
            y->left = z;
        } else {
            y->right = z;
        }

        ins_fix(z);
        return true;
    }

    bool remv(int v) {
        Node* z = find(v);
        if (z == NIL) return false;

        Node *y = z, *x;
        bool y_orig_is_red = y->is_red;

        if (z->left == NIL) {
            x = z->right;
            transplant(z, z->right);
        } else if (z->right == NIL) {
            x = z->left;
            transplant(z, z->left);
        } else {
            y = minimum(z->right);
            y_orig_is_red = y->is_red;
            x = y->right;
            if (y->parent == z) {
                x->parent = y;
            } else {
                transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->is_red = z->is_red;
        }
        delete z;
        if (!y_orig_is_red) {
            remv_fix(x);
        }
        return true;
    }

    void draw(sf::RenderWindow& window, sf::CircleShape& shape, sf::Text& text) {
        window.clear(sf::Color::Black);
        configPosiciones();
        sf::VertexArray lines(sf::Lines);
        construirLineas(root, lines);
        window.draw(lines);
        dibujarNodos(window, root, shape, text);
        window.display();
    }
};

int main() {
    RBTree a;
    int opcion, valor;

    sf::RenderWindow window(sf::VideoMode(VENTANA_ANCHO, VENTANA_ALTO), "Arbol Rojo-Negro");
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.loadFromFile("../z_fonts/ARIAL.TTF")) { 
        cerr << "Error: No se pudo cargar la fuente" << endl;
        return -1;
    }

    sf::CircleShape nodoShape(RADIO_NODO);
    nodoShape.setOutlineThickness(2.0f);
    nodoShape.setOrigin(RADIO_NODO, RADIO_NODO);

    sf::Text valorNodo;
    valorNodo.setFont(font);
    valorNodo.setCharacterSize(16);

    auto dibujarArbol = [&]() {
        a.draw(window, nodoShape, valorNodo);
    };

    dibujarArbol(); 

    while (true) {
        cout << "1. Insertar 2. Eliminar 3. Salir" << endl;
        
        sf::Event event;
        while(window.isOpen() && !cin.eof()) {
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                    return 0;
                }
            }

            if (!(cin >> opcion)) { 
                cin.clear(); 
                cin.ignore(10000, '\n'); 
                continue; 
            }

            switch (opcion) {
                case 1:
                    cout << "Ingrese valor a insertar: ";
                    cin >> valor;
                    if (a.ins(valor)) {
                        cout << "Valor insertado" << endl;
                    } else {
                        cout << "El valor ya existe" << endl;
                    }
                    break;
                case 2:
                    cout << "Ingrese valor a eliminar: ";
                    cin >> valor;
                    if (a.remv(valor)) {
                        cout << "Valor eliminado" << endl;
                    } else {
                        cout <<"Mo se encontro" << endl;
                    }
                    break;
                case 3:
                    window.close();
                    return 0;
                default:
                    cout << "Opcion no valida" << endl;
                    break;
            }

            if (opcion == 1 || opcion == 2) {
                dibujarArbol();
                break; 
            }
        }

        if (!window.isOpen()) {
            break;
        }
    }

    return 0;
}