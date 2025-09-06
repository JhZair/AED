#include <iostream>
#include <string>
#include <cstring>
using namespace std;

struct Buscaminas {
    char _tablero_solucion[10][10];
    char _tablero_juego[10][10];
    bool _juego_terminado;
    bool _victoria;
    int _casillas_restantes;

    void iniciar_juego() {
        char solucion_fija[10][10] = {
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
     
    }

    void jugar() {
        iniciar_juego();
    }
};

int main() {
    Buscaminas juego;
    juego.jugar();
    return 0;
}