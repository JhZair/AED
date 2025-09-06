//encontrar numero de ocurrencias de palabras patan, tapa, pato, tipa
// solo horizontal y verticalmente, sin usar string

// hacer programa que encuentre el camino mas corto en un laberinto

// hacer un buscaminas 10x10 usando matrices y punteros una version con threads y otra sin

// #include <iostream>
// #include <string>
// #include <vector>
// using namespace std;


// int contarOcurrenciasHorizontales(char matriz[10][10], string palabra) {
//     int res = 0;
//     int largoPalabra = palabra.length();
//     for (int i = 0; i < 10; ++i) {
//         for (int j = 0; j <= 10 - largoPalabra; ++j) {
//             bool palabraEncontrada = true;
//             for (int k = 0; k < largoPalabra; ++k) {
//                 if (matriz[i][j + k] != palabra[k]) {
//                     palabraEncontrada = false;
//                     break; 
//                 }
//             }
//             if (palabraEncontrada) {
//                 res++;
//             }
//         }
//     }
//     return res;
// }

// int main() {
//     char tabla[10][10] = {
//         {'T', 'P', 'P', 'A', 'P', 'T', 'P', 'Z', 'R', 'T'},
//         {'O', 'P', 'A', 'T', 'A', 'P', 'O', 'Z', 'O', 'J'},
//         {'S', 'A', 'T', 'A', 'T', 'O', 'T', 'A', 'Z', 'I'},
//         {'A', 'T', 'A', 'P', 'A', 'P', 'A', 'T', 'O', 'S'},
//         {'P', 'A', 'T', 'A', 'N', 'O', 'P', 'O', 'T', 'N'},
//         {'T', 'A', 'A', 'P', 'A', 'T', 'I', 'P', 'A', 'P'},
//         {'R', 'R', 'N', 'A', 'D', 'O', 'T', 'A', 'D', 'O'},
//         {'E', 'D', 'N', 'T', 'A', 'P', 'O', 'T', 'A', 'T'},
//         {'N', 'I', 'I', 'A', 'T', 'I', 'T', 'A', 'P', 'A'},
//         {'P', 'S', 'S', 'N', 'T', 'T', 'T', 'P', 'A', 'P'}
//     };

//     vector<string> palabras = {"PATAN", "TIPA", "PATA", "PATO", "TAPA"};

//     for (string p : palabras) {
//         cout << p << " tiene " << contarOcurrenciasHorizontales(tabla, p) << " ocurrencias" << endl;
//     }

//     return 0;
// }

#include <iostream>
#include <string>
#include <vector>

int contarOcurrencias(const char matriz[10][10], const std::string& palabra) {
    int contador = 0;
    const size_t largoPalabra = palabra.length();
    if (largoPalabra == 0 || largoPalabra > 10) {
        return 0;
    }

    const char* p_palabra_fin = &palabra[0] + largoPalabra;

    // Búsqueda Horizontal
    const char (*p_fila_fin_h)[10] = matriz + 10;
    for (const char (*p_fila)[10] = matriz; p_fila < p_fila_fin_h; ++p_fila) {
        const char* p_matriz_limite_inicio = *p_fila + 10 - largoPalabra;
        for (const char* p_matriz_inicio = *p_fila; p_matriz_inicio <= p_matriz_limite_inicio; ++p_matriz_inicio) {
            bool encontrada = true;
            const char* p_matriz = p_matriz_inicio;
            for (const char* p_palabra = &palabra[0]; p_palabra < p_palabra_fin; ++p_palabra, ++p_matriz) {
                if (*p_matriz != *p_palabra) {
                    encontrada = false;
                    break;
                }
            }
            if (encontrada) {
                contador++;
            }
        }
    }

    // Búsqueda Vertical
    const char (*p_fila_limite_inicio_v)[10] = matriz + 10 - largoPalabra;
    for (const char (*p_fila)[10] = matriz; p_fila <= p_fila_limite_inicio_v; ++p_fila) {
        const char* p_columna_fin = *p_fila + 10;
        for (const char* p_columna_inicio = *p_fila; p_columna_inicio < p_columna_fin; ++p_columna_inicio) {
            bool encontrada = true;
            const char* p_matriz = p_columna_inicio;
            for (const char* p_palabra = &palabra[0]; p_palabra < p_palabra_fin; ++p_palabra) {
                if (*p_matriz != *p_palabra) {
                    encontrada = false;
                    break;
                }
                p_matriz += 10;
            }
            if (encontrada) {
                contador++;
            }
        }
    }

    return contador;
}


int main() {
    using namespace std;

    char tabla[10][10] = {
        {'T','P','P','A','P','T','P','Z','R','T'},
        {'O','P','A','T','A','P','O','Z','O','J'},
        {'S','A','T','A','T','O','T','A','Z','I'},
        {'A','T','A','P','A','P','A','T','O','S'},
        {'P','A','T','A','N','O','P','O','T','N'},
        {'T','A','A','P','A','T','I','P','A','P'},
        {'R','R','N','A','D','O','T','A','D','O'},
        {'E','D','N','T','A','P','O','T','A','T'},
        {'N','I','I','A','T','I','T','A','P','A'},
        {'P','S','S','N','T','T','T','P','A','P'}
    };

    vector<string> palabras = {"PATAN", "TIPA", "PATA", "PATO", "TAPA"};

    for (string& p : palabras) {
        cout << p << " tiene " << contarOcurrencias(tabla, p) << " ocurrencias" << endl;
    }

    return 0;
}