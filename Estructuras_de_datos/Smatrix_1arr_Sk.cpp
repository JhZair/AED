#include <iostream>

using namespace std;

struct Node {
    int row;
    int col;
    int val;
    Node* next;

    Node(int r, int c, int v) {
        row = r;
        col = c;
        val = v;
        next = nullptr;
    }
};

class SparseMatrix {
private:
    Node* head;
    int n_rows;
    int n_cols;

public:
	SparseMatrix(int rows, int cols) {
		head = 0;
		n_cols = cols;
		n_rows = rows;
	}
	
	~SparseMatrix() {
		Node* p = head;
		while(p){
			head = head->next;
			delete p;
			p = head;
		}
	}
	
	// Método PRINCIPAL: Asigna un valor a una coordenada
	// Casos a manejar:
	// 1. val != 0: Insertar nuevo nodo ordenado o actualizar existente.
	// 2. val == 0: Si la celda existe, eliminar el nodo. Si no, no hacer nada.
	void set(int r, int c, int val) {
		// Validar rangos (opcional pero recomendado)
		if (r < 0 || r >= n_rows || c < 0 || c >= n_cols) {
			cout << "Error: Indices fuera de rango" << endl;
			return;
		}
		Node** p = &head;
		while(*p){
			if((*p)->row == r){
				if((*p)->col >= c){
					if((*p)->col == c){
						if(val == 0){
							Node* t = (*p)->next;
							delete (*p);
							*p = t;
							return;
						}
						(*p)->val = val;
						return;                    
					}
					break;
				}
			}
			if((*p)->row > r){
				break;
			}
			p = &((*p)->next);
		}
		if(val == 0) return;
		Node* t = new Node(r, c, val);
		t->next = (*p);
		(*p) = t; 
		// TODO: Implementar la lógica de inserción/actualización/borrado ordenada
	}
	
	// Obtener valor: Retorna el valor en (r, c) o 0 si no existe nodo
	int get(int r, int c) {
    Node* p = head; 
    while(p){
        if(p->row == r && p->col == c){
            return p->val;
        }
        if (p->row > r||(p->row == r && p->col > c)) {
            return 0; 
        }
        p = p->next;
    }
    return 0;
}
	
	// Imprimir: Muestra la matriz completa (incluyendo ceros) o solo la lista
	// Para debug, recomiendo imprimir la lista de nodos: (r,c) -> val
	void print() {
		cout << "--- Matriz Dispersa (" << n_rows << "x" << n_cols << ") ---" << endl;
		Node* p = head;
		while(p){
			cout << '(' <<p->row << ','<< p->col << ')'<< ':'<< p->val<< endl;
			p = p->next;
		}
		// TODO: Recorrer la lista e imprimir: [Fila, Col]: Valor
		// Opcional: Imprimir la cuadrícula completa con ceros para visualizar mejor
	}
};

int main() {
	// Crear una matriz de 5x5
	cout << "Creando matriz 5x5..." << endl;
	SparseMatrix m(5, 5);
	
	// CASO 1: Inserción Básica (Insertar en lista vacía o al final)
	cout << "\n1. Insertando (0, 1) = 10 y (2, 2) = 20" << endl;
	m.set(0, 1, 10);
	m.set(2, 2, 20);
	m.print(); 
	// Esperado: Nodos (0,1):10 y (2,2):20
	
	// CASO 2: Inserción Intermedia (Mantener orden)
	cout << "\n2. Insertando (1, 1) = 15 (Debe quedar entre los anteriores)" << endl;
	m.set(1, 1, 15);
	m.print();
	// Esperado: (0,1):10 -> (1,1):15 -> (2,2):20
	
	// CASO 3: Actualización (Cambiar valor existente)
	cout << "\n3. Actualizando (0, 1) a 50" << endl;
	m.set(0, 1, 50);
	m.print();
	// Esperado: (0,1):50 -> (1,1):15 -> (2,2):20
	
	// CASO 4: Caso Borde - Insertar al inicio (Cabeza)
	cout << "\n4. Insertando (0, 0) = 5 (Nueva cabeza)" << endl;
	m.set(0, 0, 5);
	m.print();
	// Esperado: (0,0):5 -> (0,1):50 -> ...
	
	// CASO 5: Eliminación ("Setear" a 0)
	cout << "\n5. Eliminando (1, 1) (Set a 0)" << endl;
	m.set(1, 1, 0);
	m.print();
	// Esperado: El nodo (1,1) debe desaparecer.
	
	// CASO 6: Eliminación de Cabeza
	cout << "\n6. Eliminando Cabeza (0, 0) (Set a 0)" << endl;
	m.set(0, 0, 0);
	m.print();
	// Esperado: La nueva cabeza debe ser (0,1)
	
	// CASO 7: "Setear" a 0 algo que no existe (No debe hacer nada/No crashear)
	cout << "\n7. Set (4, 4) a 0 (No existe)" << endl;
	m.set(4, 4, 0);
	m.print();
	
	// Verificación final con Get
	 cout << "\nVerificando con Get:" << endl;
	 cout << "Valor en (0, 1): " << m.get(0, 1) << " (Esperado: 50)" << endl;
	 cout << "Valor en (1, 1): " << m.get(1, 1) << " (Esperado: 0)" << endl;
	
	return 0;
}