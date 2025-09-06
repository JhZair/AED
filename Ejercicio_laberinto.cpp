#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

struct Coordenada {
    int fila;
    int col;
};

struct Laberinto {
    char _mapa[11][21];
    int _jugador_fila;
    int _jugador_col;
    bool _juego_terminado;

    void iniciar() {
        char mapa_fijo[11][22] = {
            "#####################",
            "#I    #   # #     # #",
            "# # ### # # # ##### #",
            "#     #   #   #   # #",
            "### # ##### ### # # #",
            "#   #   #   #   # # #",
            "# ##### # ####### # #",
            "#     #   #         #",
            "# ### # # # ## #### #",
            "#   #   #   #   # F #",
            "#####################"
        };
        
        for (int i = 0; i < 11; ++i) {
            memcpy(_mapa[i], mapa_fijo[i], 21);
        }

        for (int i = 0;i < 11;++i) {
            for (int j = 0; j < 21; ++j) {
                if (_mapa[i][j] =='I') {
                    _jugador_fila = i;
                    _jugador_col = j;
                    char* p_inicio = &_mapa[0][0]+(i*21 + j);
                    *p_inicio = 'P';
                    break;
                }
            }
        }
        _juego_terminado = false;
    }

    void mostrar() {
        for(int i = 0; i < 20; ++i) cout << "\n";
        
        cout << "--- ENCUENTRA LA SALIDA (F) ---" << endl;
        cout << "Controles: W, A, S, D" << endl;
        
        for (int i = 0; i < 11; i++) {
            for (int j = 0; j < 21; j++) {
                cout << _mapa[i][j];
            }
            cout << endl;
        }
    }
    void mover_jugador(char direccion) {
        int nueva_fila = _jugador_fila;
        int nueva_col = _jugador_col;
        if (direccion == 'w' || direccion == 'W') nueva_fila--;
        else if (direccion == 's' || direccion == 'S') nueva_fila++;
        else if (direccion == 'a' || direccion == 'A') nueva_col--;
        else if (direccion == 'd' || direccion == 'D') nueva_col++;
        else return;

        char* p_destino = &_mapa[0][0] + (nueva_fila * 21 + nueva_col);

        if (*p_destino == '#') {
            return;
        }
        if (*p_destino == 'F') {
            _juego_terminado = true;
            return;
        }
        char* p_actual = &_mapa[0][0] + (_jugador_fila * 21 + _jugador_col);
        *p_actual = ' ';

        _jugador_fila = nueva_fila;
        _jugador_col = nueva_col;
        *p_destino = 'P';
    }

    void jugar() {
        iniciar();
        while (!_juego_terminado) {
            mostrar();
            cout << "Moverse hacia: ";
            char movimiento;
            cin >> movimiento;
            mover_jugador(movimiento);
        }
        
        mostrar();
        cout << "\nEncontraste la salida\n";
    }
};

int main() {
    Laberinto juego;
    juego.jugar();
    return 0;
}