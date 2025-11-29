#include <iostream>

using namespace std;

// Estructura del Nodo para Listas Ortogonales
struct Node {
    int row;
    int col;
    int val;
    Node* right;
    Node* down;

    Node(int r, int c, int v) {
        row = r;
        col = c;
        val = v;
        right = nullptr;
        down = nullptr;
    }
};

class SparseMatrix; // Necesario para la clase de referencia
class Objx;    // La clase Proxy/Referencia

class Objx {
private:
    SparseMatrix* matrix; // Puntero a la matriz real (el contexto)
    int ref_r;            // Fila capturada
    int ref_c;            // Columna capturada
public:
    // Constructor: Captura la matriz y la coordenada (r, c)
    Objx(SparseMatrix* m, int r, int c);

    // Sobrecarga de ASIGNACIÓN: Permite m(r, c) = valor;
    Objx& operator=(int v);

    // Sobrecarga de CASTEO a int: Permite int a = m(r, c);
    operator int();
};

class SparseMatrix {
private:
    Node** rows;
    Node** cols;
    int n_rows;
    int n_cols;

    // Métodos privados para el manejo de la estructura (necesarios para MatrixRef)
    bool findH(int r, int c, Node**& p);
    bool findV(int r, int c, Node**& p);

public:
    SparseMatrix(int r, int c);
    ~SparseMatrix();

    // Método principal de asignación y obtención (usado por MatrixRef)
    void set(int r, int c, int val);
    int get(int r, int c);

    // OPERADOR DE INDEXACIÓN: Retorna el objeto proxy (MatrixRef)
    Objx operator()(int r, int c);

    void print();
};

bool SparseMatrix::findH(int r, int c, Node**& p) {
    p = &rows[r];
    while (*p && (*p)->col < c) {
        p = &((*p)->right);
    }
    return *p && (*p)->col == c;
}

bool SparseMatrix::findV(int r, int c, Node**& p) {
    p = &cols[c];
    while (*p && (*p)->row < r) {
        p = &((*p)->down);
    }
    return *p && (*p)->row == r;
}

SparseMatrix::SparseMatrix(int r, int c) {
    n_rows = r;
    n_cols = c;
    rows = new Node*[n_rows];
    cols = new Node*[n_cols];
    for(int i = 0; i < n_rows; i++) rows[i] = nullptr;
    for(int i = 0; i < n_cols; i++) cols[i] = nullptr;
}

SparseMatrix::~SparseMatrix() {
    for(int i = 0; i < n_rows; i++) {
        Node* current = rows[i];
        while(current) {
            Node* temp = current;
            current = current->right;
            delete temp;
        }
    }
    delete[] rows;
    delete[] cols;
}

void SparseMatrix::set(int r, int c, int val) {
    if (r < 0 || r >= n_rows || c < 0 || c >= n_cols) return;

    Node** p_row;
    Node** p_col;

    bool foundH = findH(r, c, p_row);
    findV(r, c, p_col);

    if (val != 0) {
        if (foundH) {
            (*p_row)->val = val;
        } else {
            Node* newNode = new Node(r, c, val);
            
            // Conexión Horizontal
            newNode->right = *p_row; 
            *p_row = newNode;
            
            // Conexión Vertical
            newNode->down = *p_col; 
            *p_col = newNode;
        }
    } else { // val == 0 -> ELIMINAR
        if (foundH) {
            Node* toDelete = *p_row;
            *p_row = toDelete->right;
            *p_col = toDelete->down;
            delete toDelete;
        }
    }
}

int SparseMatrix::get(int r, int c) {
    if (r < 0 || r >= n_rows || c < 0 || c >= n_cols) return 0;
    Node** p;
    if (findH(r, c, p)) {
        return (*p)->val;
    }
    return 0;
}

Objx SparseMatrix::operator()(int r, int c) {
    return Objx(this, r, c);
}

void SparseMatrix::print() {
    cout << "--- Matriz Ortogonal (" << n_rows << "x" << n_cols << ") ---" << endl;
    for (int i = 0; i < n_rows; ++i) {
        cout << "Fila " << i << ": ";
        Node* curr = rows[i];
        if (!curr) cout << "(vacia)";
        while (curr) {
            cout << "(" << curr->row << "," << curr->col << "):" << curr->val << " -> ";
            curr = curr->right;
        }
        cout << "NULL" << endl;
    }
}

Objx::Objx(SparseMatrix* m, int r, int c) {
    matrix = m;
    ref_r = r;
    ref_c = c;
}

Objx& Objx::operator=(int v) {
    // La asignación se traduce en una llamada al método set de la matriz
    matrix->set(ref_r, ref_c, v);
    return *this; // Retornamos la referencia al objeto proxy para permitir encadenamiento
}

Objx::operator int() {
    // La conversión se traduce en una llamada al método get de la matriz
    return matrix->get(ref_r, ref_c);
}


int main() {
    cout << "Inicializando Matriz Ortogonal 4x4..." << endl;
    SparseMatrix m(4, 4);

    // --- 1. PRUEBA DE ASIGNACIÓN (Set) ---
    cout << "\n--- 1. Asignacion (Set) ---" << endl;
    m(1, 1) = 10;     // Llama a operator() -> MatrixRef -> operator=(10) -> m.set(1, 1, 10)
    m(2, 2) = 20;
    m(1, 2) = 15;     // Inserción ordenada
    m(0, 0) = 5;      // Inserción en cabeza

    m.print();

    // --- 2. PRUEBA DE OBTENCIÓN (Get) ---
    cout << "\n--- 2. Obtencion (Get) ---" << endl;
    int a = m(1, 1);  // Llama a operator() -> MatrixRef -> operator int() -> m.get(1, 1)
    int b = m(3, 3);  // Llama a m.get(3, 3), retorna 0
    cout << "a = m(1, 1): " << a << endl; // Esperado: 10
    cout << "b = m(3, 3): " << b << endl; // Esperado: 0

    // --- 3. PRUEBA DE ACTUALIZACIÓN ---
    cout << "\n--- 3. Actualizacion ---" << endl;
    m(1, 1) = 99;
    cout << "m(1, 1) despues de actualizar: " << m(1, 1) << endl; // Esperado: 99

    // --- 4. PRUEBA DE ELIMINACIÓN (Set a 0) ---
    cout << "\n--- 4. Eliminacion (Set a 0) ---" << endl;
    m(1, 2) = 0; // Llama a m.set(1, 2, 0) y el nodo es eliminado

    m.print();
    
    cout << "m(1, 2) (Borrado): " << m(1, 2) << endl; // Esperado: 0

    return 0;
}