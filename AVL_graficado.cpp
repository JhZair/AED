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
    Node * right;
    Node * left;
    int h; 
    float x, y;

    Node(int x_val){
        v = x_val;
        right = left = 0;
        h = 0; 
        x = 0;
        y = 0;
    }
};

class AVLtree{
    Node * root;
    bool lado_reemp;

    int altura(Node* p) {
        return p ? p->h : -1;
    }

    void actualizar_altura(Node* p) {
        if (p) {
            p->h = 1 + std::max(altura(p->left), altura(p->right));
        }
    }

    int FB(Node* p) {
        return altura(p->left) - altura(p->right);
    }

    void LL(Node*& p){ 
        Node* q = p->left;
        p->left = q->right;
        q->right = p;
        
        actualizar_altura(p);
        actualizar_altura(q);
        p = q;
    }
    
    void RR(Node*& p){
        Node* q = p->right;
        p->right = q->left;
        q->left = p;

        actualizar_altura(p);
        actualizar_altura(q);
        p = q;
    }
    
    void LR(Node*& p){
        RR(p->left);
        LL(p);
    }
    
    void RL(Node*& p){
        LL(p->right);
        RR(p);
    }

    void verificar_ruta(stack<Node**>& path) {
        while (!path.empty()) {
            Node** p_ptr = path.top();
            path.pop();
            Node* p = *p_ptr;

            actualizar_altura(p);

            int bf = FB(p);

            if (bf > 1) { 
                if (FB(p->left) >= 0) { 
                    LL(*p_ptr);
                } else { 
                    LR(*p_ptr);
                }
            } else if (bf < -1) { 
                if (FB(p->right) <= 0) { 
                    RR(*p_ptr);
                } else { 
                    RL(*p_ptr);
                }
            }
        }
    }
    
    void clear(Node* p) {
        if (p) {
            clear(p->left);
            clear(p->right);
            delete p;
        }
    }

public:
    AVLtree();
    ~AVLtree();
    bool ins(int x);
    bool fnd(int x, Node**& p);
    bool remv(int x);
    Node** reemp(Node** p, stack<Node**>& path);
    Node*& get_root(){return root;}
};

AVLtree::AVLtree(){
    root = 0;
    lado_reemp = 0;
}
AVLtree::~AVLtree(){
    clear(root);
}
    
bool AVLtree::ins(int x){
    Node** p = &root;
    stack<Node**> path; 

    while (*p) {
        path.push(p); 
        if ((*p)->v == x) return false;
        
        p = ((*p)->v > x) ? &((*p)->left) : &((*p)->right);
    }

    *p = new Node(x);

    verificar_ruta(path);
    return true;
}

bool AVLtree::remv(int x){
    Node** p = &root;
    stack<Node**> path; 

    while (*p && (*p)->v != x) {
        path.push(p);
        p = ((*p)->v > x) ? &((*p)->left) : &((*p)->right);
    }

    if (!*p) return false; 

    if ((*p)->left && (*p)->right) {
        path.push(p); 
        Node** q = reemp(p, path);
        (*p)->v = (*q)->v;
        p = q;
    }

    Node* t = *p;
    *p = (*p)->left ? (*p)->left : (*p)->right;
    delete t;

    verificar_ruta(path);
    return true;
}

Node** AVLtree::reemp(Node** p, stack<Node**>& path) {
    Node** q;
    if(lado_reemp){
        q = &((*p)->right);
        path.push(q);
        while((*q)->left) {
            q = &((*q)->left);
            path.push(q);
        }
    }
    else{
        q = &((*p)->left);
        path.push(q);
        while((*q)->right) {
            q = &((*q)->right);
            path.push(q);
        }
    }
    lado_reemp = !lado_reemp;
    return q;
}

bool AVLtree::fnd(int x, Node**& p){
    while(*p && (*p)->v != x){
        if((*p)->v > x)
            p = &((*p)->left);
        else
            p = &((*p)->right);
    }
    return *p;
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
    AVLtree a;
    int opcion, valor;

    sf::RenderWindow window(sf::VideoMode(VENTANA_ANCHO, VENTANA_ALTO), "Arbol AVL");
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.loadFromFile("../z_fonts/ARIAL.TTF")) { 
        cerr << "Error: No se pudo cargar la fuente" << endl;
        return -1;
    }

    sf::CircleShape nodoShape(RADIO_NODO);
    nodoShape.setFillColor(sf::Color::Green);
    nodoShape.setOutlineColor(sf::Color::White);
    nodoShape.setOutlineThickness(2.0f);
    nodoShape.setOrigin(RADIO_NODO, RADIO_NODO);

    sf::Text valorNodo;
    valorNodo.setFont(font);
    valorNodo.setCharacterSize(16);
    valorNodo.setFillColor(sf::Color::Black);

    auto dibujarArbol = [&]() {
        window.clear(sf::Color::Black);
        
        configPosiciones(a.get_root());

        sf::VertexArray lines(sf::Lines);
        construirLineas(a.get_root(), lines);
        window.draw(lines);

        dibujarNodos(window, a.get_root(), nodoShape, valorNodo);

        window.display();
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