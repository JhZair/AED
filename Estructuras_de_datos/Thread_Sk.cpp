#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <random>
#include <atomic>

using namespace std;

// --- CONFIGURACIÓN ---
const int DATA_SIZE = 10000000; // 10 Millones de datos
const int MAX_VAL = 100;        // Valores del 0 al 99
const int NUM_THREADS = 4;      // Número de hilos a usar

// --- DATOS COMPARTIDOS (Globales) ---
vector<int> big_data;           // El vector gigante (Solo lectura para los hilos)
vector<int> global_histogram(MAX_VAL, 0); // El resultado compartido (Lectura/Escritura)
mutex mtx;                      // Mutex para proteger la escritura

// --- FUNCIÓN DEL HILO ---
// start: Índice inicial del trozo que le toca a este hilo
// end:   Índice final (no inclusivo)
void worker_histogram(int start, int end) {
    // TODO: Implementar la lógica del hilo.
    
    // ESTRATEGIA 1 (Mala - Lenta):
    // Recorrer del start al end.
    // Por cada numero, bloquear el mutex, sumar al global_histogram, desbloquear.
    
    // ESTRATEGIA 2 (Buena - Rápida):
    // 1. Crear un vector local 'local_histogram' de tamaño MAX_VAL inicializado en 0.
    // 2. Recorrer del start al end llenando SOLO el histograma local (sin mutex).
    // 3. Al terminar el bucle, bloquear el mutex UNA SOLA VEZ.
    // 4. Sumar el histograma local al global_histogram.
    // 5. Desbloquear.
}

int main() {
    // 1. GENERACIÓN DE DATOS (No tocar)
    cout << "Generando " << DATA_SIZE << " datos aleatorios..." << endl;
    big_data.resize(DATA_SIZE);
    for(int& x : big_data) x = rand() % MAX_VAL;

    // 2. PREPARACIÓN DE THREADS
    vector<thread> threads;
    
    // TODO: Calcular los rangos y lanzar los hilos
    // Pista para dividir el trabajo:
    // int chunk_size = DATA_SIZE / NUM_THREADS;
    // for (int i = 0; i < NUM_THREADS; ++i) {
    //      int start = ...
    //      int end = ... (Cuidado con el último hilo, debe llegar hasta DATA_SIZE)
    //      threads.push_back(thread(worker_histogram, start, end));
    // }

    // 3. ESPERAR A LOS HILOS (JOIN)
    // TODO: Recorrer el vector de threads y hacer join()

    // 4. VERIFICACIÓN (No tocar)
    long long total_count = 0;
    for(int count : global_histogram) total_count += count;
    
    cout << "Total contado: " << total_count << endl;
    cout << "Total esperado: " << DATA_SIZE << endl;
    
    if(total_count == DATA_SIZE) 
        cout << "SUCCESS: El conteo coincide." << endl;
    else 
        cout << "FAIL: Hubo condicion de carrera o error de rangos." << endl;

    return 0;
}