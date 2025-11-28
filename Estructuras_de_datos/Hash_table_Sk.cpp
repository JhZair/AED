#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <functional> // Para std::hash

using namespace std;

// --- ESTRUCTURA DE LOS DATOS ---
template <typename K, typename V>
struct Entry {
    K key;
    V value;
    
    // Sobrecarga para facilitar comparaciones dentro de los contenedores
    bool operator==(const Entry& other) const {
        return key == other.key;
    }
};

// --- CLASE HASH TABLE GENÉRICA ---
// K: Tipo de la clave
// V: Tipo del valor
// Container: El contenedor para manejar colisiones (ej: list<Entry<K,V>>)
template <typename K, typename V, typename Container = std::list<Entry<K, V>>>
class HashTable {
private:
    // El arreglo principal de "cubetas" (buckets)
    // Cada posición contiene un Contenedor (lista, vector, etc.)
    vector<Container> table;
    
    int num_elements;   // Cantidad total de elementos insertados
    int table_size;     // Tamaño del vector principal (M)
    const float MAX_LOAD_FACTOR = 0.75; // Factor de carga para redimensionar (Rehashing)

    // --- FUNCIONES HASH ---
    
    // Función Hash interna. Retorna un índice entre [0, table_size - 1]
    size_t hashFunction(const K& key) {
        // TODO: Implementar una buena función hash.
        // Estrategia sugerida para ENTEROS: 
        //      return (key * constante_primo) % table_size;
        
        // Estrategia sugerida para STRINGS (Polynomial Rolling Hash):
        //      hash = 0; p = 31; m = table_size;
        //      for char c in key: hash = (hash * p + c) % m;
        //      return hash;
        
        // *Truco*: Puedes usar std::hash<K>{}(key) % table_size para empezar rápido.
        return std::hash<K>{}(key) % table_size; 
    }

    // Rehashing: Se llama cuando num_elements > table_size * MAX_LOAD_FACTOR
    void rehash() {
        // TODO:
        // 1. Guardar la tabla actual en una temporal.
        // 2. Duplicar table_size (idealmente al siguiente número primo).
        // 3. Limpiar y redimensionar 'table'.
        // 4. Reinicializar num_elements = 0.
        // 5. Recorrer la tabla vieja e insertar CADA elemento de nuevo en la nueva tabla.
        cout << "[INFO] Rehashing... Nuevo tamaño: " << table_size * 2 << endl;
    }

public:
    // Constructor
    HashTable(int initial_size = 11) {
        table_size = initial_size;
        num_elements = 0;
        table.resize(table_size);
    }

    // INSERTAR
    void insert(const K& key, const V& value) {
        // 1. Verificar factor de carga y llamar a rehash() si es necesario.
        if ((float)num_elements / table_size > MAX_LOAD_FACTOR) {
            rehash();
        }

        // 2. Calcular índice con hashFunction.
        size_t index = hashFunction(key);

        // 3. Buscar en el contenedor 'table[index]' si la clave YA existe.
        //    (Depende del tipo de Container, iterar para buscar).
        //    SI existe: Actualizar el valor.
        //    NO existe: Agregar Entry{key, value} al contenedor e incrementar num_elements.
        
        // TODO: Implementar lógica de inserción según el Container.
    }

    // OBTENER
    // Retorna puntero al valor para poder modificarlo, o nullptr si no existe.
    V* get(const K& key) {
        size_t index = hashFunction(key);

        // TODO:
        // 1. Obtener referencia al contenedor en table[index].
        // 2. Iterar sobre el contenedor buscando 'key'.
        // 3. Si se encuentra, retornar la dirección del valor (&entry.value).
        // 4. Si no, retornar nullptr.
        return nullptr;
    }

    // ELIMINAR
    bool remove(const K& key) {
        size_t index = hashFunction(key);

        // TODO:
        // 1. Buscar 'key' en table[index].
        // 2. Si existe, eliminar el elemento del contenedor.
        // 3. Decrementar num_elements y retornar true.
        // 4. Si no existe, retornar false.
        return false;
    }

    // DEBUG: Imprimir la distribución
    void printDistribution() {
        cout << "\n--- Estado de la Tabla Hash (Size: " << table_size << ") ---" << endl;
        for (int i = 0; i < table_size; ++i) {
            cout << "Bucket [" << i << "]: ";
            if (table[i].empty()) {
                cout << "(vacio)";
            } else {
                // Asumiendo que Container es iterable
                for (const auto& entry : table[i]) {
                    cout << "{" << entry.key << ":" << entry.value << "} -> ";
                }
            }
            cout << endl;
        }
    }
};

int main() {
    // PRUEBA 1: Usando std::list (Clásica lista enlazada para colisiones)
    cout << "=== Test con std::list ===" << endl;
    HashTable<string, int, list<Entry<string, int>>> hashList;
    
    hashList.insert("Manzana", 10);
    hashList.insert("Pera", 20);
    hashList.insert("Uva", 30);
    hashList.insert("Manzana", 15); // Actualización
    
    // Forzamos colisiones o rehashing insertando más datos
    hashList.insert("Limon", 40);
    hashList.insert("Fresa", 50);
    hashList.insert("Melon", 60); // Debería activar rehash si size es pequeño
    
    hashList.printDistribution();

    if (int* v = hashList.get("Pera")) {
        cout << "Valor de Pera: " << *v << endl;
    }

    // PRUEBA 2: Usando std::vector (Más rápido en caché, pero cuidado con redimensionamiento interno)
    cout << "\n=== Test con std::vector ===" << endl;
    HashTable<int, string, vector<Entry<int, string>>> hashVector(7);
    
    hashVector.insert(1, "Uno");
    hashVector.insert(8, "Ocho (Colisiona con 1 en mod 7)");
    hashVector.insert(15, "Quince (Colisiona con 1 y 8)");
    
    hashVector.printDistribution();
    
    hashVector.remove(8);
    cout << "\nDespues de borrar 8:" << endl;
    hashVector.printDistribution();

    return 0;
}