#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <thread>
using namespace std;

struct BuscaminasThreads {
    char tablero_sol[10][10];
    char tablero_juego[10][10];
    bool juego_terminado;
    bool victoria;
    int casillas_restantes;

    void rellenar_tablero(char* p_inicio, int num_casillas) {
        char* p_fin = p_inicio + num_casillas;
        while (p_inicio < p_fin) {
            *p_inicio = '#';
            p_inicio++;
        }
    }

    void iniciar_juego() {
        char solucion[10][10] = {
            {'1', '1', '1', '0', '0', '0', '0', '1', '1', '1'},
            {'*', '2', '*', '1', '0', '0', '0', '1', '*', '1'},
            {'2', '3', '2', '1', '0', '0', '0', '1', '1', '1'},
            {'1', '*', '1', '0', '0', '0', '0', '0', '0', '0'},
            {'1', '1', '1', '0', '0', '1', '1', '1', '0', '0'},
            {'0', '0', '1', '1', '1', '*', '1', '1', '*', '1'},
            {'0', '0', '1', '*', '2', '2', '2', '2', '2', '1'},
            {'0', '1', '2', '2', '1', '0', '0', '1', '*', '1'},
            {'0', '1', '*', '1', '0', '0', '0', '1', '1', '1'},
            {'0', '1', '1', '1', '0', '0', '0', '0', '0', '0'}
        };
        
        memcpy(tablero_sol, solucion, 10*10);
        juego_terminado = false;
        victoria = false;
        casillas_restantes = 10*10 - 10;
        
        vector<thread> hilos;
        char* p_inicio_tablero = &tablero_juego[0][0];
        int casillas_por_hilo = (10 * 10) / 4;

        for (int i = 0; i < 4; i++) {
            char* p_inicio_seccion = p_inicio_tablero + (i*casillas_por_hilo);
            hilos.push_back(thread(&BuscaminasThreads::rellenar_tablero, this, p_inicio_seccion, casillas_por_hilo));
        }

        for (int i = 0; i < 4; i++) {
            hilos[i].join();
        }
    }

    void mostrar_tablero() {
        cout << "\n  ";
        for (int i = 0; i < 10; i++) cout << i << " ";
        cout << "\n-----------------------\n";
        for (int i = 0; i < 10; i++) {
            cout << i << "|";
            char* p_fila = tablero_juego[i];
            for (int j = 0; j < 10; j++) {
                cout << *(p_fila + j) << " ";
            }
            cout << "|\n";   
        }
        cout << "-----------------------\n";
    }

    void descubrir_casilla(int fila, int col) {
        if (fila<0||fila>= 10||col<0||col>= 10) return;

        char* p_juego = &tablero_juego[0][0]+(fila*10 + col);      
        
        if (*p_juego != '#') return;

        char* p_solucion = &tablero_sol[0][0]+(fila*10 + col);
        *p_juego = *p_solucion;
        
        casillas_restantes--;

        if (*p_juego == '*') {
            juego_terminado = true;
            victoria = false;
            return;
        }
        if (*p_juego == '0') {
            *p_juego = ' ';
            for (int df = -1; df <= 1; df++) {
                for (int dc = -1; dc <= 1; dc++) {
                    descubrir_casilla(fila + df, col + dc);
                }
            }
        }
    }

    void jugar() {
        iniciar_juego();
        while (!juego_terminado) {
            mostrar_tablero();
            cout << "Ingresa tu jugada (r para revelar y b para bandera): ";
            char accion;
            int fila, col;
            cin >> accion >> fila >> col;

            if (cin.fail() || (accion != 'r' && accion != 'b')) {
                cout << "Entrada invalida\n";
                cin.clear();
                cin.ignore(10000, '\n');
                continue;
            }

            if (fila < 0 || fila >= 10 || col < 0 || col >= 10) {
                 cout << "Coordenadas fuera del tablero.\n";
                 continue;
            }
            char* p_casilla_juego = &tablero_juego[0][0] + (fila * 10 + col);

            if (accion == 'r') {
                descubrir_casilla(fila, col);
            } else if (accion == 'b') {
                if (*p_casilla_juego == '#') *p_casilla_juego = 'B';
                else if (*p_casilla_juego == 'B') *p_casilla_juego = '#';
            }

            if (casillas_restantes == 0 && !juego_terminado) {
                juego_terminado = true;
                victoria = true;
            }
        }

        for (int i = 0; i < 10; i++) {
           memcpy(tablero_juego[i], tablero_sol[i], 10);
        }
        mostrar_tablero();

        if (victoria) {
            cout << "Ganaste!\n";
        } else {
            cout << "Perdiste\n";
        }
    }
};

int main() {
    BuscaminasThreads juego;
    juego.jugar();
    return 0;
}