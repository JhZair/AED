#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <ctime>
#include <cmath>
#include <thread>

using namespace std;

struct Buscaminas {
    char _tablero[10][10];

    void limpiar_tablero() {
        char* p_inicio = &_tablero[0][0];
        char* p_fin = p_inicio + 100;
        while (p_inicio < p_fin) {
            *p_inicio = '0';
            p_inicio++;
        }
    }

    void colocar_minas(int num_minas) {
        if (num_minas >= 100) {
            num_minas = 99;
        }
        srand(time(0));
        int minas_colocadas = 0;
        while (minas_colocadas < num_minas) {
            int pos = rand() % 100;
            char* p_casilla = &_tablero[0][0] + pos;
            if (*p_casilla != '*') {
                *p_casilla = '*';
                minas_colocadas++;
            }
        }
    }

    void calcular_hilos(int fila_inicio, int fila_fin) {
        char (*p_fila)[10] = _tablero + fila_inicio;
        char (*p_fin_seccion)[10] = _tablero + fila_fin;

        for (; p_fila < p_fin_seccion; ++p_fila) {
            char* p_casilla = *p_fila;
            char* p_fin_fila = *p_fila + 10;
            for (; p_casilla < p_fin_fila; ++p_casilla) {
                if (*p_casilla == '*') {
                    continue;
                }

                int conteo = 0;
                int offsets[] = {-11, -10, -9, -1, 1, 9, 10, 11};
                
                long pos_actual = p_casilla - &_tablero[0][0];
                int col_actual = pos_actual % 10;

                for (int i = 0; i < 8; ++i) {
                    int offset = offsets[i];
                    char* p_vecino = p_casilla + offset;
                    long pos_vecino = p_vecino - &_tablero[0][0];

                    if (pos_vecino >= 0 && pos_vecino < 100) {
                        int col_vecino = pos_vecino % 10;
                        if (abs(col_actual - col_vecino) > 1) {
                            continue;
                        }
                        if (*p_vecino == '*') {
                            conteo++;
                        }
                    }
                }
                
                if (conteo > 0) {
                    *p_casilla = conteo + '0';
                }
            }
        }
    }

    void generar(int num_minas) {
        limpiar_tablero();
        colocar_minas(num_minas);
        
        vector<thread> hilos;
        hilos.push_back(thread(&Buscaminas::calcular_hilos, this, 0, 2));
        hilos.push_back(thread(&Buscaminas::calcular_hilos, this, 2, 4));
        hilos.push_back(thread(&Buscaminas::calcular_hilos, this, 4, 7));
        hilos.push_back(thread(&Buscaminas::calcular_hilos, this, 7, 10));

        for (int i = 0; i < hilos.size(); ++i) {
            hilos[i].join();
        }
    }

    void mostrar_tablero() {
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                if (_tablero[i][j] == '0') {
                    cout << ". ";
                } else {
                    cout << _tablero[i][j] << " ";
                }
            }
            cout << endl;
        }
    }
};

int main() {
    Buscaminas juego;
    int num_minas = 0;

    cout << "Ingrese el numero de minas a colocar: ";
    cin >> num_minas;

    if (cin.fail() || num_minas <= 0) {
        cout << "Numero invalido" << endl;
        num_minas = 10;
    }

    juego.generar(num_minas);
    juego.mostrar_tablero();

    return 0;
}