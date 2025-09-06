//encontrar numero de ocurrencias de palabras patan, tapa, pato, tipa
// solo horizontal y verticalmente, sin usar string

// hacer programa que encuentre el camino mas corto en un laberinto

// hacer un buscaminas 10x10 usando matrices y punteros una version con threads y otra sin

#include <iostream>
#include <string>
#include <vector>
using namespace std;

// int Encontrar_Horizontal(string palabra, char b[][10],int tam_pal){
// 	int res=0;
// 	char * pal = &palabra[0];
// 	for(char * p = *b; p < *b + 100;p++){
// 		if(*p == *pal){
// 			pal++;
// 		}
// 		if(*pal == '\0'){
// 			res++;
// 			pal = &palabra[0];
// 		}
// 		else{
// 		pal = &palabra[0];
// 		}
// 	}
// 	return res;
// }

// int main(int argc, char *argv[]) {

// 	char tabla[10][10]= {
//         {'T', 'P', 'P', 'A', 'P', 'T', 'P', 'Z', 'R', 'T'},
//         {'O', 'P', 'A', 'T', 'A', 'P', 'O', 'Z', 'O', 'J'},
//         {'S', 'A', 'T', 'A', 'T', 'O', 'T', 'A', 'Z', 'I'},
//         {'A', 'T', 'A', 'P', 'A', 'D', 'A', 'T', 'O', 'S'},
//         {'P', 'A', 'T', 'A', 'N', 'O', 'P', 'O', 'T', 'N'},
//         {'T', 'A', 'A', 'P', 'A', 'T', 'I', 'P', 'A', 'P'},
//         {'R', 'R', 'N', 'A', 'D', 'O', 'T', 'A', 'D', 'O'},
//         {'E', 'D', 'N', 'T', 'A', 'P', 'O', 'T', 'A', 'T'},
//         {'N', 'I', 'I', 'A', 'T', 'I', 'T', 'A', 'P', 'A'},
//         {'P', 'S', 'S', 'N', 'T', 'T', 'T', 'P', 'A', 'P'}
//     };
// 	const int tam = 5;
// 	string palabras[tam] = {"PATAN","TIPA","PATA","PATO","TAPA"};
// 	for(string *p = palabras; p < palabras + tam;p++){
// 		cout <<*p << " tiene "<< Encontrar_Horizontal(*p, tabla, (*p).size()) << " ocurrencias"<< endl;	
// 	}

// 	return 0;
// }


int contarOcurrenciasHorizontales(char matriz[10][10], string palabra) {
    int res = 0;
    int largoPalabra = palabra.length();
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j <= 10 - largoPalabra; ++j) {
            bool palabraEncontrada = true;
            for (int k = 0; k < largoPalabra; ++k) {
                if (matriz[i][j + k] != palabra[k]) {
                    palabraEncontrada = false;
                    break; 
                }
            }
            if (palabraEncontrada) {
                res++;
            }
        }
    }
    return res;
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

    for (string p : palabras) {
        cout << p << " tiene " << contarOcurrenciasHorizontales(tabla, p) << " ocurrencias" << endl;
    }

    return 0;
}