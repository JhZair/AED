#include <iostream>
using namespace std;

// Primero, implementa una lista enlazada simple
struct Node
{
    // Metodos y datos del nodo
    int valor;
    Node* next;
    Node(int v){
    	valor = v;
    	next = NULL;
	}
};

class SinglyLinkedList
{
public:

    // Metodos de la lista enlazada: constructor, destructor, etc
    //Node* head = nullptr;
	void ins(int x){
		//si LE vacia
		if(head == NULL){
			Node* nuevo = new Node(x);
			head = nuevo;
		}
		
		//si LE no esta vacia
		else{
			Node* nuevo = new Node(x);
			Node* tmp = head;
			head = nuevo;
			nuevo->next = tmp;
		}
	};
	
    bool rem(){
    	//si la LE vacia
    	if(head == NULL){
    		cout << "lista vacia" << endl;
    		return 0;
		}
		
		//si no esta vacia
		else{
			Node* tmp = head;
			head = head->next;
			delete tmp;
			return 1;
		}
	};
	
    void print()
    {
        // Este metodo es importante para ver los elementos de la lista y luego del stack
        
		//si LE vacia
		if(head == NULL){
			cout << "Head->NULL" << endl;
		}
		
		cout << "head->";
		for(Node* ptr=head; ptr; ptr=ptr->next){
			cout << ptr->valor << "->";
		}
		cout << "null" << endl;
    }
    
    ~SinglyLinkedList(){
    	while(head){
    		Node* tmp = head;
    		head = head->next;
    		delete tmp;
		}
	}
    
    Node* head;
};

// Ahora, crea un adaptador de Stack usando tu lista enlazada
class Stack
{
public:
    // Debes implementar estas funciones
    void push(int x)
    {
        // Inserta el elemento x en la parte superior de la pila
        Node* nuevo = new Node(x);	
        
    }
    
    void pop()
    {
        // Elimina el elemento superior de la pila
        if(empty()){
        	cout << "pila vacia" << endl;
		}
		
		
		
    }
    
    int& top()
    {
        // Devuelve una referencia al elemento superior de la pila
        //top = head->v;
        
    }
    
    bool empty()
    {
        // Devuelve true si la pila está vacía, false en caso contrario
		
		return true;
        
    }
    
    // Función auxiliar para depuración
    void print()
    {
        // Aqui llamar al print de la lista enlazada
        l.print();
    }
    
private:
    // Debes usar tu lista enlazada como almacenamiento interno
    SinglyLinkedList l;
    
};

int main()
{
    // Pruebas del stack
    Stack stack;
    
    // Prueba 1: Inserción de elementos
    std::cout << "Prueba 1: Insertando elementos" << std::endl;
    stack.push(10);
    stack.push(20);
    stack.push(30);
    std::cout << "Stack: ";
    stack.print();
    
    // Prueba 2: Acceso al elemento superior
    std::cout << "\nPrueba 2: Elemento superior" << std::endl;
    std::cout << "Top: " << stack.top() << std::endl;
    
    // Prueba 3: Eliminación de elementos
    std::cout << "\nPrueba 3: Eliminando elementos" << std::endl;
    stack.pop();
    std::cout << "Después de pop: ";
    stack.print();
    std::cout << "Nuevo top: " << stack.top() << std::endl;
    
    // Prueba 4: Verificación de pila vacía
    std::cout << "\nPrueba 4: Verificación de pila vacía" << std::endl;
    std::cout << "¿Está vacía? " << (stack.empty() ? "Sí" : "No") << std::endl;
    
    // Prueba 5: Vaciado completo de la pila
    std::cout << "\nPrueba 5: Vaciado completo" << std::endl;
    stack.pop(); // Queda un elemento
    stack.pop(); // Queda vacía
    std::cout << "Después de vaciar: ";
    stack.print();
    std::cout << "¿Está vacía? " << (stack.empty() ? "Sí" : "No") << std::endl;
    
    // Prueba 6: Operaciones adicionales
    std::cout << "\nPrueba 6: Operaciones adicionales" << std::endl;
    for (int i = 1; i <= 5; i++)
    {
        stack.push(i * 10);
    }
    std::cout << "Después de insertar 5 elementos: ";
    stack.print();
    
    return 0;
}
