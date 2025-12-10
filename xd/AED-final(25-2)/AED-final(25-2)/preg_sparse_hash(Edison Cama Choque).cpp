#include <iostream>
#include <list>
#include <vector>
#include <set>




class Node {
public:
    int x;
    int y;
    int dato;
    Node* next;
    int getposicion();

};

int Node::getposicion() {
    return x * 10 + y;
}

// Clase adaptadora para std::list
template<class T>
class ListAdapter {
private:
    std::list<T> data;
public:
    void insert(const T& value) {
        data.push_back(value);
    }

    bool find(const T& value) const {
        for (const auto& item : data) {
            if (item == value) return true;
        }
        return false;
    }

    bool remove(const T& value) {
        auto it = std::find(data.begin(), data.end(), value);
        if (it != data.end()) {
            data.erase(it);
            return true;
        }
        return false;
    }

    T* get(const T& key) {
        for (auto& item : data) {
            if (item == key) return &item;
        }
        return nullptr;
    }

    void print() const {
        for (const auto& item : data) {
            std::cout << item << " ";
        }
    }

    bool empty() const {
        return data.empty();
    }
};

// Tabla Hash con templates
template<class T, class S, class F, size_t Z>
class CHashTable {
private:
    S table[Z];
    F hash_function;

public:
    void insert(const T& value) {
        size_t index = hash_function(value) % Z;
        table[index].insert(value);
    }

    bool remove(const T& value) {
        size_t index = hash_function(value) % Z;
        return table[index].remove(value);
    }

    T* find(const T& key) {
        size_t index = hash_function(key) % Z;
        return table[index].get(key);
    }

    void print_hash_table() {
        for (size_t i = 0; i < Z; ++i) {
            if (!table[i].empty()) {
                std::cout << "[" << i << "]: ";
                table[i].print();
                std::cout << std::endl;
            }
        }
    }
};

/*---------------------------------------------*/

// Estructura para elemento de matriz dispersa
struct MatrixElement
{
    int row, col;
    int value;

    MatrixElement(int r = 0, int c = 0, int v = 0)
    {
        row = r;    col = c;    value = v;
    }

    bool operator==(const MatrixElement& other) const
    {
        return row == other.row && col == other.col;
    }
};

// FunciÃ³n hash para MatrixElement
struct MatrixHash
{
    int operator()(const MatrixElement& elem)
    {
        return 0;
        // // put your code here !
        // retornar alguna operacion con elem.row , elem.col
    }
};

// Adaptador de Sparse Matrix
class SparseMatrix
{
private:
    CHashTable<MatrixElement, /*contenedor para colisiones*/, /*funcion de dispersion*/, 100> hash_table;
    int rows;
    int cols;
    Node* initial;

public:
    SparseMatrix(int c, int r)
    {
        rows = r;   cols = c;
    }







    void add(int row, int col, int value) {

        if (initial == nullptr) {//CASO 1= SI NO EXISTEN ELEMENTOS

            initial = new Node{ row,col,value,nullptr };
            return;


        }
        else { // CASO 2 = SI EXISTEN ELEMENTOS
            int posicion = row * 10 + col;
            Node* p1;

            if (initial->next == nullptr) { //CASO 2.1= SI EXISTE SOLO 1 ELEMENTO
                if (posicion < initial->getposicion()) { //CASO 2.1.1 SI HAY QUE INSERTAR ATRAS
                    p1 = new Node{ row,col,value,initial };
                    initial = p1;
                    return;

                }
                else if (posicion > initial->getposicion()) { //CASO 2.1.2 SI HAY QUE INSERTAR ADELANTE
                    initial->next = new Node{ row,col,value,nullptr };
                    return;
                }
                else if (posicion == initial->getposicion()) { // CASO 2.2.3 SI SOLO HAY QUE MODIFICAR DATO
                    initial->dato = value;
                    return;
                }
            }

            else {// SI EXISTE MAS DE UN ELEMENTO
                Node* p1 = initial;
                Node* p2 = initial->next;

                if (posicion < p1->getposicion()) { // SI HAY MAS DE 1 ELEMENTO PERO SE DEBE INSERTAR AL INICIO
                    p1 = new Node{ row,col,value,initial };
                    initial = p1;
                    return;
                }
                while (p2->getposicion() < posicion) {
                    if (p2->next == nullptr) {
                        if (p2->getposicion() == posicion) { // SI SON IGUALES DE COORDENADA
                            p2->dato = value;
                            return;
                        }
                        else if (p2->getposicion() > posicion) { // SI DEBE IR DETRAS
                            p1->next = new Node{ row,col,value,p2 };
                            return;
                        }
                        else if (p2->getposicion() < posicion) { // SI DEBE SER EL ULTIMO
                            p2->next = new Node{ row,col,value,nullptr };
                            return;
                        }
                    }
                    p1 = p1->next;
                    p2 = p2->next;
                }
                if (p2->getposicion() == posicion) {
                    p2->dato = value;
                    return;
                }
                else {
                    p1->next = new Node{ row,col,value,p2 };
                    return;
                }
            }
        }
    }


    void remove(int row, int col) {
        
        if (initial == nullptr) { // SI NO HAY ELEMENTOS
            return;
        }

        else {

        }






    }

    void set(int row, int col, int value)
    {

        if (value == 0) {
            remove(row,col);
        }
        else {
            add(row, col, value);
        }



    }

    int get(int row, int col)
    {
        Node* p1 = initial;
        int posicion = row * 10 + col;
        while (p1->getposicion() < posicion) {
            p1 = p1->next;
        }



        return 0;
    }

    void print()
    {

        Node* p1 = initial;

        // put your code here !

        /* ejemplo de como debe salir la impresion
         7    0    0
         0    0    9
         0    8    0
         0    0    3
         0    5    0
         */
    }

};

int main()
{
    std::cout << "=== SparseMatrix test ===" << std::endl;

    SparseMatrix matrix(3, 5);  // 3 columnas, 5 filas

    matrix.set(0, 0, 10);
    matrix.set(1, 2, 20);
    matrix.set(2, 1, 30);
    matrix.set(3, 0, 40);
    matrix.set(4, 2, 50);
    matrix.set(2, 2, 60);
    matrix.print(); std::cout << "\n";

    matrix.set(1, 2, 21);
    matrix.set(2, 2, 10);
    matrix.set(2, 1, 31);
    matrix.print(); std::cout << "\n";

    matrix.set(3, 0, 10);
    matrix.set(3, 0, 41);
    matrix.set(4, 2, 10);
    matrix.print(); std::cout << "\n";

    return 0;
}

