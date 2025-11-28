#include <iostream>

using namespace std;

// Estructura del Nodo para Listas Ortogonales
struct Node {
    int row;    // Coordenada Fila
    int col;    // Coordenada Columna
    int val;    // Valor
    Node* right; // Puntero al siguiente nodo en la misma FILA (Horizontal)
    Node* down;  // Puntero al siguiente nodo en la misma COLUMNA (Vertical)

    Node(int r, int c, int v) {
        row = r;
        col = c;
        val = v;
        right = nullptr;
        down = nullptr;
    }
};

class SparseMatrix {
private:
    Node** rows;    // Array de cabeceras de filas (búsqueda horizontal)
    Node** cols;    // Array de cabeceras de columnas (búsqueda vertical)
    int n_rows;     // Cantidad de filas
    int n_cols;     // Cantidad de columnas

    // BUSQUEDA HORIZONTAL (En una fila específica)
    // Objetivo: Buscar en la fila 'r' el nodo con columna 'c'.
    // Retorna: true si el nodo existe exactamente en (r,c).
    // Param 'p': Se pasa por referencia.
    //    - Si existe: p apunta al nodo encontrado.
    //    - Si no existe: p apunta al puntero 'right' del nodo ANTERIOR (punto de inserción).
    bool findH(int r, int c, Node**& p) {
        // TODO:
        // 1. Inicializar p con la dirección de rows[r].
        // 2. Recorrer la lista enlazada horizontalmente usando (*p)->right.
        // 3. Detenerse si llegamos al final o si la columna del nodo actual > c.
        // 4. Retornar true si (*p) no es nulo y (*p)->col == c.
        return false;
    }

    // BUSQUEDA VERTICAL (En una columna específica)
    // Objetivo: Buscar en la columna 'c' el nodo con fila 'r'.
    // Retorna: true si el nodo existe exactamente en (r,c).
    // Param 'p': Igual que arriba, pero navegando verticalmente (down).
    bool findV(int r, int c, Node**& p) {
        // TODO:
        // 1. Inicializar p con la dirección de cols[c].
        // 2. Recorrer la lista enlazada verticalmente usando (*p)->down.
        // 3. Detenerse si llegamos al final o si la fila del nodo actual > r.
        // 4. Retornar true si (*p) no es nulo y (*p)->row == r.
        return false;
    }

public:
    // Constructor: Debe inicializar los arrays de punteros
    SparseMatrix(int r, int c) {
        n_rows = r;
        n_cols = c;
        // TODO:
        // 1. Reservar memoria para el array 'rows' de tamaño n_rows.
        // 2. Reservar memoria para el array 'cols' de tamaño n_cols.
        // 3. Inicializar todos los punteros de ambos arrays a nullptr.
    }

    // Destructor
    ~SparseMatrix() {
        // TODO: Liberar memoria.
        // Estrategia: Recorrer el array 'rows' y borrar las listas horizontales.
        // Luego borrar los arrays 'rows' y 'cols' en sí.
    }

    // Método set: El corazón de la estructura
    void set(int r, int c, int val) {
        if (r < 0 || r >= n_rows || c < 0 || c >= n_cols) return;

        Node** p_row;
        Node** p_col;

        // 1. Buscamos la posición en ambas direcciones
        bool foundH = findH(r, c, p_row); // p_row apunta al lugar en la lista horizontal
        bool foundV = findV(r, c, p_col); // p_col apunta al lugar en la lista vertical

        // Nota: foundH y foundV deberían ser consistentes (ambos true o ambos false)

        if (val != 0) {
            if (foundH) {
                // CASO: Actualizar valor existente
                // TODO: Actualizar (*p_row)->val
            } else {
                // CASO: Insertar nuevo nodo
                // TODO:
                // 1. Crear newNode con (r, c, val).
                // 2. Conectar horizontalmente: newNode->right = *p_row; *p_row = newNode;
                // 3. Conectar verticalmente: newNode->down = *p_col; *p_col = newNode;
            }
        } else { // val == 0
            if (foundH) {
                // CASO: Eliminar nodo existente
                // TODO:
                // 1. Guardar puntero temporal al nodo a borrar (*p_row).
                // 2. "Saltar" el nodo en la lista horizontal: *p_row = (*p_row)->right;
                // 3. "Saltar" el nodo en la lista vertical: *p_col = (*p_col)->down;
                // 4. delete temporal.
            }
            // Si val es 0 y no existe, no hacemos nada.
        }
    }

    int get(int r, int c) {
        if (r < 0 || r >= n_rows || c < 0 || c >= n_cols) return 0;

        Node** p;
        // Solo necesitamos buscar en una dirección para obtener el valor
        if (findH(r, c, p)) {
            // TODO: Retornar (*p)->val
        }
        return 0;
    }

    void print() {
        cout << "--- Matriz Ortogonal (" << n_rows << "x" << n_cols << ") ---" << endl;
        // TODO:
        // Recorrer fila por fila (usando el array rows) e imprimir los nodos.
        // Formato sugerido: Fila 0: (0,1):5 -> (0,3):8
    }
};

int main() {
    cout << "Inicializando Matriz Ortogonal 4x4..." << endl;
    SparseMatrix m(4, 4);

    // 1. Inserción Básica
    cout << "\n1. Insertando (1, 1) = 10 y (2, 2) = 20" << endl;
    m.set(1, 1, 10);
    m.set(2, 2, 20);
    m.print();

    // 2. Inserción Cruzada (Misma fila, diferente columna y viceversa)
    cout << "\n2. Insertando (1, 2) = 15 y (2, 1) = 25" << endl;
    // Esto prueba si findH y findV manejan bien el orden de inserción
    m.set(1, 2, 15); // Debe quedar a la derecha de (1,1)
    m.set(2, 1, 25); // Debe quedar a la izquierda de (2,2)
    m.print();

    // 3. Actualización
    cout << "\n3. Actualizando (1, 1) a 50" << endl;
    m.set(1, 1, 50);
    m.print();

    // 4. Caso Borde: Insertar en (0,0) (Cabeceras de fila 0 y col 0)
    cout << "\n4. Insertando (0, 0) = 100" << endl;
    m.set(0, 0, 100);
    m.print();

    // 5. Eliminación (Set a 0)
    cout << "\n5. Eliminando (1, 2) (Nodo intermedio horizontal)" << endl;
    m.set(1, 2, 0);
    m.print();

    cout << "\n6. Eliminando (2, 1) (Nodo cabeza de fila 2, intermedio de col 1)" << endl;
    m.set(2, 1, 0);
    m.print();

    cout << "\n7. Get de valores:" << endl;
    cout << "Get(1, 1) (Existe): " << m.get(1, 1) << endl;
    cout << "Get(1, 2) (Borrado): " << m.get(1, 2) << endl;

    return 0;
}