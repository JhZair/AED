#include <iostream>
#include <vector>
#include <string>
using namespace std;

int contarOcurrencias(char tabla[10][10], string pal) {
    int resltdo = 0;
    int tam_pal = pal.length();
    if (tam_pal == 0 || tam_pal > 10) {
        return 0;
    }
    char* p_ini_pal = &pal[0];
    char* p_fin_pal = p_ini_pal + tam_pal;

    char (*p_fila_fin)[10] = tabla+10;
    for (char (*p_fila)[10] = tabla; p_fila<p_fila_fin; ++p_fila) {
        char* p_limite_ini = *p_fila+10-tam_pal;
        for (char* p_tabla_ini = *p_fila;p_tabla_ini <= p_limite_ini; ++p_tabla_ini) {
            bool encontrada = true;
            char* p_tabla = p_tabla_ini;
            for (char* p_palabra = p_ini_pal; p_palabra < p_fin_pal; ++p_palabra, ++p_tabla) {
                if (*p_tabla != *p_palabra) {
                    encontrada = false;
                    break;
                }
            }
            if (encontrada) {
                resltdo++;
            }
        }
    }
    char (*p_limite2_ini)[10] = tabla+10-tam_pal;
    for (char (*p_fila)[10]=tabla; p_fila <= p_limite2_ini;++p_fila) {
        char* p_columna_fin = *p_fila+10;
        for (char* p_columna_ini = *p_fila; p_columna_ini < p_columna_fin; ++p_columna_ini) {
            bool encontrada = true;
            char* p_tabla = p_columna_ini;
            for (char* p_palabra = p_ini_pal; p_palabra < p_fin_pal; ++p_palabra) {
                if (*p_tabla != *p_palabra) {
                    encontrada = false;
                    break;
                }
                p_tabla += 10;
            }
            if (encontrada) {
                resltdo++;
            }
        }
    }
    return resltdo;
}

int main() {
    char tabla[10][10] = {
        {'T', 'P', 'P', 'A', 'P', 'T', 'P', 'Z', 'R', 'T'},
        {'O', 'P', 'A', 'T', 'A', 'P', 'O', 'Z', 'O', 'J'},
        {'S', 'A', 'T', 'A', 'T', 'O', 'T', 'A', 'Z', 'I'},
        {'A', 'T', 'A', 'P', 'A', 'P', 'A', 'T', 'O', 'S'},
        {'P', 'A', 'T', 'A', 'N', 'O', 'P', 'O', 'T', 'N'},
        {'T', 'A', 'A', 'P', 'A', 'T', 'I', 'P', 'A', 'P'},
        {'R', 'R', 'N', 'A', 'D', 'O', 'T', 'A', 'D', 'O'},
        {'E', 'D', 'N', 'T', 'A', 'P', 'O', 'T', 'A', 'T'},
        {'N', 'I', 'I', 'A', 'T', 'I', 'T', 'A', 'P', 'A'},
        {'P', 'S', 'S', 'N', 'T', 'T', 'T', 'P', 'A', 'P'}
    };

    vector<string> palabras = {"PATAN", "TIPA", "PATA", "PATO", "TAPA"};

    for (string p : palabras)
        cout <<p<< " tiene "<<contarOcurrencias(tabla, p)<<" ocurrencias"<<endl;

    return 0;
}