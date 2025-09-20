#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <cstring>
#include <ctime>

using namespace std;

struct Laberinto {
    char _mapa[11][21];

    void inicializar_mapa() {
        memset(_mapa, '#', 11 * 21);
    }

    void generar_recursivo(int fila, int col) {
        char* p_actual = &_mapa[0][0] + (fila * 21 + col);
        *p_actual = ' ';

        int direcciones[] = {0, 1, 2, 3}; 
        random_shuffle(begin(direcciones), end(direcciones));

        for (int i = 0; i < 4; ++i) {
            int dir = direcciones[i];
            int df = 0, dc = 0; 

            if (dir == 0) df = -2; 
            if (dir == 1) df = 2;  
            if (dir == 2) dc = 2;  
            if (dir == 3) dc = -2;  

            int nueva_fila = fila + df;
            int nueva_col = col + dc;

            if (nueva_fila > 0 && nueva_fila < 10 && nueva_col > 0 && nueva_col < 20) {
                char* p_vecino = &_mapa[0][0] + (nueva_fila * 21 + nueva_col);
                if (*p_vecino == '#') {
                    char* p_pared = &_mapa[0][0] + ((fila + df / 2) * 21 + (col + dc / 2));
                    *p_pared = ' ';
                    generar_recursivo(nueva_fila, nueva_col);
                }
            }
        }
    }

    void generar() {
        srand(time(0));
        inicializar_mapa();
        generar_recursivo(1, 1);

        char* p_inicio = &_mapa[0][0] + (1 * 21 + 1);
        *p_inicio = 'I';

        char* p_fin = &_mapa[0][0] + (9 * 21 + 19);
        *p_fin = 'F';
    }

    bool resolver_recursivo(int fila, int col) {
        if (fila < 0 || fila >= 11 || col < 0 || col >= 21) {
            return false;
        }

        char* p_actual = &_mapa[0][0] + (fila * 21 + col);

        if (*p_actual == '#' || *p_actual == '.') {
            return false;
        }

        if (*p_actual == 'F') {
            return true;
        }
        
        *p_actual = '.';

        if (resolver_recursivo(fila + 1, col)) return true;
        if (resolver_recursivo(fila - 1, col)) return true;
        if (resolver_recursivo(fila, col + 1)) return true;
        if (resolver_recursivo(fila, col - 1)) return true;

        *p_actual = ' ';
        return false;
    }

    void resolver() {
        resolver_recursivo(1, 1);
        char* p_inicio = &_mapa[0][0] + (1 * 21 + 1);
        *p_inicio = 'I';
    }
    void mostrar() {
        for (int i = 0; i < 11; i++) {
            for (int j = 0; j < 21; j++) {
                cout << _mapa[i][j];
            }
            cout << endl;
        }
    }
};

int main() {
    Laberinto lab;
    lab.generar();
    lab.resolver();
    lab.mostrar();
    return 0;
}