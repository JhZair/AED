#include <iostream>
#include <cmath>
#include <vector>
#include <string> 


#include <SFML/Graphics.hpp>

using namespace std;


const float VENTANA_ANCHO = 1600;
const float VENTANA_ALTO = 900;
const float RADIO_NODO = 22.0f;
const float ESPACIO_Y = 100.0f; // Espacio vertical entre niveles

struct Nodo {
    int valor;
    Nodo* izq;
    Nodo* der;

    //  Coordenadas para SFML
    float x, y;

    Nodo(int v) : valor(v), izq(nullptr), der(nullptr), x(0), y(0) {}
};


// Función recursiva para crear el árbol
// INI y FIN son PUNTEROS al inicio y fin del segmento del array
Nodo* crearArbol(int* INI, int* FIN) {
    // Caso base: un solo elemento
    if (INI == FIN) {
        return new Nodo(*INI);  // *INI desreferencia el puntero
    }

    // Calcular punto medio usando aritmética de punteros
    int longitud = FIN - INI + 1;  // Resta de punteros
    int mitad = longitud / 2;
    int* MED = INI + mitad - 1;    // MED es un PUNTERO calculado

    // Crear subárboles recursivamente (pasando punteros)
    Nodo* izquierdo = crearArbol(INI, MED);     // Retorna puntero a Nodo
    Nodo* derecho = crearArbol(MED + 1, FIN);   // MED + 1 es aritmética de punteros

    // Crear nodo padre con la suma
    Nodo* padre = new Nodo(izquierdo->valor + derecho->valor);  // new retorna puntero
    padre->izq = izquierdo;  // Asignar puntero izquierdo
    padre->der = derecho;    // Asignar puntero derecho

    return padre;  // Retorna puntero al nodo padre
}

/*
 Asigna recursivamente las coordenadas (x, y) a cada nodo del árbol.
 */
void configurarPosiciones(Nodo* nodo, float x, float y, float x_offset) {
    if (nodo == nullptr) return;

    nodo->x = x;
    nodo->y = y;

    // Los hijos se dibujan más abajo (y + ESPACIO_Y)
    // El offset horizontal se reduce a la mitad en cada nivel
    configurarPosiciones(nodo->izq, x - x_offset, y + ESPACIO_Y, x_offset / 2.0f);
    configurarPosiciones(nodo->der, x + x_offset, y + ESPACIO_Y, x_offset / 2.0f);
}

/**
Construye un VertexArray con las líneas que conectan padres e hijos.
 */
void construirLineas(Nodo* nodo, sf::VertexArray& lines) {
    if (nodo == nullptr) return;

    // Si tiene hijo izquierdo, dibuja una línea hacia él
    if (nodo->izq) {
        lines.append(sf::Vertex(sf::Vector2f(nodo->x, nodo->y), sf::Color::Black));
        lines.append(sf::Vertex(sf::Vector2f(nodo->izq->x, nodo->izq->y), sf::Color::Black));
        construirLineas(nodo->izq, lines);
    }

    // Si tiene hijo derecho, dibuja una línea hacia él
    if (nodo->der) {
        lines.append(sf::Vertex(sf::Vector2f(nodo->x, nodo->y), sf::Color::Black));
        lines.append(sf::Vertex(sf::Vector2f(nodo->der->x, nodo->der->y), sf::Color::Black));
        construirLineas(nodo->der, lines);
    }
}

/**
 Dibuja recursivamente los nodos (círculo y texto) en la ventana.
 */
void dibujarNodos(sf::RenderWindow& window, Nodo* nodo, sf::CircleShape& shape, sf::Text& text) {
    if (nodo == nullptr) return;

    // 1. Configurar y dibujar el Círculo
    shape.setPosition(nodo->x, nodo->y);
    window.draw(shape);

    // 2. Configurar y dibujar el Texto
    text.setString(std::to_string(nodo->valor));

    // Centrar el texto dentro del círculo
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
    text.setPosition(nodo->x, nodo->y);
    window.draw(text);

    // 3. Recursión
    dibujarNodos(window, nodo->izq, shape, text);
    dibujarNodos(window, nodo->der, shape, text);
}

// --- **** NUEVA FUNCIÓN PARA LIBERAR MEMORIA **** ---

/**
 Libera recursivamente la memoria de todos los nodos del árbol.
 * Usa un recorrido post-orden para eliminar hijos antes que padres.
 * @param nodo El nodo raíz del subárbol a eliminar.
 */
void liberarMemoria(Nodo* nodo) {
    // Caso base: si el nodo es nulo, no hay nada que hacer.
    if (nodo == nullptr) {
        return;
    }

    // 1. Liberar recursivamente el subárbol izquierdo
    liberarMemoria(nodo->izq);

    // 2. Liberar recursivamente el subárbol derecho
    liberarMemoria(nodo->der);

    // 3. Liberar el nodo actual (después de que sus hijos han sido liberados)
    // std::cout << "Liberando nodo con valor: " << nodo->valor << std::endl; // Descomenta para depurar
    delete nodo;
}



int main() {
    //   Creación del Árbol 
    int arr[] = { 2, 4, 7, 9, 10, 15, 3, 25, 38, 74, 1, 5, 10, 13, 11, 35 };
    int n = 4;
    int longitud = pow(2, n);
    int* INI = arr;
    int* FIN = arr + longitud - 1;

    // Crear el arbol
    Nodo* raiz = crearArbol(INI, FIN);
    cout << "Valor en la raiz (suma total): " << raiz->valor << endl;


    // 2. Configuración de SFML 
    sf::RenderWindow window(sf::VideoMode(VENTANA_ANCHO, VENTANA_ALTO), "Visualizador de Arbol de Suma");
    window.setFramerateLimit(60);

    sf::Font font;
  
    if (!font.loadFromFile("z_fonts/ARIAL.TTF")) {
        cerr << "Error: No se pudo cargar la fuente del sistema desde arial.ttf" << endl;
        cerr << "Asegurate de que Windows este instalado en la unidad C:." << endl;
        return -1;
    }


    // Asignar posiciones (x, y) a todos los nodos
    configurarPosiciones(raiz, VENTANA_ANCHO / 2.0f, ESPACIO_Y, VENTANA_ANCHO / 4.0f);

    // Crear el array de líneas (se hace una sola vez)
    sf::VertexArray lines(sf::Lines);
    construirLineas(raiz, lines);

    // Preparar las formas que se reutilizarán para dibujar
    sf::CircleShape nodeShape(RADIO_NODO);
    nodeShape.setFillColor(sf::Color::White);
    nodeShape.setOutlineColor(sf::Color::Black);
    nodeShape.setOutlineThickness(2.0f);
    nodeShape.setOrigin(RADIO_NODO, RADIO_NODO); // Centrar el origen

    sf::Text nodeText;
    nodeText.setFont(font);
    nodeText.setCharacterSize(16);
    nodeText.setFillColor(sf::Color::Black);


    //  4. Bucle principal de SFML
    while (window.isOpen()) {
        // Manejo de eventos
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        //  Dibujado (Render)
        window.clear(sf::Color(220, 220, 220)); // Un fondo gris claro

        // 1. Dibujar las líneas (detrás de los nodos)
        window.draw(lines);

        // 2. Dibujar los nodos (círculos y texto)
        dibujarNodos(window, raiz, nodeShape, nodeText);

        // 3. Mostrar en pantalla
        window.display();
    }

    cout << "Cerrando la ventana y liberando memoria del arbol..." << endl;
    liberarMemoria(raiz);
    cout << "Memoria liberada." << endl;

    return 0;
}

//g++ -o arboldibuj Arbol_graficado.cpp -lsfml-graphics -lsfml-window -lsfml-system