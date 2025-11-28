#include <iostream>
#include <vector>
#include <queue>
#include <limits> // Para infinity

using namespace std;

// Usamos un número muy grande para representar "distancia infinita"
const int INF = numeric_limits<int>::max();

// Definición de una Arista: {destino, peso}
struct Edge {
    int to;
    int weight;
};

// La función que debes implementar
// n: Número de nodos en el grafo
// adj: Lista de adyacencia. adj[u] contiene las aristas que salen de 'u'
// startNode: El nodo origen (ej: 0)
// Retorno: Un vector donde vector[i] es la distancia mínima desde startNode a i
vector<int> calcularTiemposMinimos(int n, const vector<vector<Edge>>& adj, int startNode) {
    
    // 1. Vector de distancias inicializado en INF
    vector<int> dist(n, INF);
    
    // 2. Estructura para la Priority Queue (Min-Heap)
    //    Necesitamos guardar pares {distancia_acumulada, nodo_actual}
    //    IMPORTANTE: std::priority_queue es un Max-Heap por defecto. 
    //    Para Dijkstra necesitamos un Min-Heap (el menor peso arriba).
    //    Sintaxis: priority_queue<Tipo, Contenedor, Comparador>
    
    // TODO: Definir la priority_queue correcta.
    // priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    // 3. Inicialización
    // TODO:
    // - La distancia al startNode es 0.
    // - Insertar {0, startNode} en la pq.

    // 4. Bucle principal (Mientras la pq no esté vacía)
    // while (!pq.empty()) {
        // TODO:
        // - Sacar el elemento con menor distancia (top).
        // - Si la distancia sacada es mayor que la que ya tenemos en dist[], ignorar (continue).
        
        // - Recorrer los vecinos del nodo actual (usando 'adj').
        // - RELAJACIÓN (Relaxation):
        //      Si (distancia_actual + peso_arista < distancia_vecino) {
        //          Actualizar distancia_vecino.
        //          Insertar {nueva_distancia, vecino} en la pq.
        //      }
    // }

    return dist;
}

int main() {
    // --- CONSTRUCCIÓN DEL GRAFO (NO MODIFICAR) ---
    // Grafo de 5 nodos (0 a 4)
    int numNodes = 5;
    vector<vector<Edge>> adj(numNodes);

    // Conexiones: origen -> {destino, peso}
    adj[0] = {{1, 10}, {4, 5}};      // Del 0 al 1 (peso 10), del 0 al 4 (peso 5)
    adj[1] = {{2, 1}, {4, 2}};
    adj[2] = {{3, 4}};
    adj[3] = {{2, 6}, {0, 7}};
    adj[4] = {{1, 3}, {2, 9}, {3, 2}};

    // --- LLAMADA AL ALGORITMO ---
    cout << "Calculando rutas minimas desde el Nodo 0..." << endl;
    vector<int> distancias = calcularTiemposMinimos(numNodes, adj, 0);

    // --- VERIFICACIÓN ---
    cout << "Resultados:" << endl;
    for (int i = 0; i < numNodes; ++i) {
        cout << "Nodo 0 -> Nodo " << i << " : ";
        if (distancias[i] == INF) 
            cout << "Inalcanzable" << endl;
        else 
            cout << distancias[i] << " ms" << endl;
    }

    // Resultados esperados visualmente:
    // 0 -> 4 = 5
    // 0 -> 4 -> 1 = 5 + 3 = 8 (Mejor que directo 0->1 que es 10)
    // 0 -> 4 -> 3 = 5 + 2 = 7
    // 0 -> 4 -> 1 -> 2 = 5 + 3 + 1 = 9
    
    return 0;
}