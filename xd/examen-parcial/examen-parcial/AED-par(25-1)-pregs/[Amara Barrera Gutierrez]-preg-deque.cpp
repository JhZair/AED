#include <iostream>

class VectorDeque {
public:
    // Constructor con capacidad inicial de 5
    VectorDeque(int initial_capacity = 5) {
        // Inicializar el vector con la capacidad inicial
        // Inicializar front_index, back_index, element_count;
        int* front_index = initial_capacity/2;
        int* back_index = front;
        element_count = 0;
    }
    
    ~VectorDeque() {
        // Liberar la memoria del array
        while(data){
        	delete data;
		}
    }
    
    void push_front(int x) {
        // Insertar elemento al inicio del deque
        // Si no hay espacio al inicio, redimensionar
        if (front_index==back_index){
        	front_index == new data[x];
        	front_index--;
		}
		
		if(front_index == data){
			resize();
		}
    }
    
    void push_back(int x) {
        // Insertar elemento al final del deque
        // Si no hay espacio al final, redimensionar
        if (back_index==front_index){
        	back_index == new data[x];
        	back_index++;
		}
		
		if(back_index == data+5){
			resize();
		}
    }
    
    void resize() {
        // Duplicar la capacidad
        // Crear un nuevo array
        // Redistribuir los elementos dejando espacio similar en ambos extremos
        // Actualizar los índices y liberar el array anterior
        int ncapacity = capacity*2;
        int* ndata;
        for(int* p = ndata; (*p) != ncapacity; p++);
    }
    
    void pop_front() {
        // Eliminar el primer elemento
        // Ajustar front_index y element_count
    }
    
    void pop_back() {
        // Eliminar el último elemento
        // Ajustar back_index y element_count
    }
    
    int& operator[](int i)
    {
        // Retornar el elemento i del deque
    }
    
    void print() {
        // Imprimir todos los elementos del deque desde front_index hasta back_index
    }
    
private:
    int* data;                // Puntero al array de datos
    int capacity;             // Capacidad total del vector
    int* front_index;          // Índice, o puntero, del primer elemento
    int* back_index;           // Índice, o puntero, del último elemento
    int element_count;        // Número de elementos
    
};

int main() {
    VectorDeque dq;
    
    // Inserta elementos
    dq.push_back(10);
    dq.push_front(5);
    dq.push_back(15);
    dq.push_front(1);
    dq.print();  // Debería mostrar: 1 5 10 15
    
    // Prueba del operador []
    std::cout << "Accediendo mediante operator[]: ";
    for (int i = 0; i < 4; i++) {
        std::cout << dq[i] << " ";
    }
    std::cout << std::endl;
    
    // Modificación mediante operator[]
    dq[0] = 100;  // Modificar el primer elemento
    dq[3] = 300;  // Modificar el último elemento
    std::cout << "Después de modificar: ";
    dq.print();   // Debería mostrar: 100 5 10 300
    
    // Prueba de redimensionamiento
    for (int i = 0; i < 10; i++) {
        dq.push_front(i * 10);
        dq.push_back(i * 100);
    }
    dq.print();
    
    // Acceso después del redimensionamiento
    std::cout << "Elemento en el índice 5: " << dq[5] << std::endl;
    std::cout << "Elemento en el índice 15: " << dq[15] << std::endl;
    
    // Prueba de eliminación
    for (int i = 0; i < 5; i++) {
        dq.pop_front();
        dq.pop_back();
    }
    dq.print();
    
    return 0;
}
