#include <iostream>
using namespace std;

class Deque{
private:
    int** mapa;
    int** blq_ini;
    int** blq_fin;
    int* ini_vlr;
    int* fin_vlr;
    int tam_mapa;
    int tam_blq;
    int numelems;

public:
    Deque();
    ~Deque();
    void push_back(int x);
    void push_front(int x);
    void pop_back();
    void pop_front();
    int& operator[](int x);
    void print();
};

Deque::Deque(){
    tam_mapa=6;
    tam_blq=8;
    mapa= new int*[tam_mapa];
    blq_ini = mapa + (tam_mapa/2);
    blq_fin = blq_ini;
    ini_vlr = 0;
    fin_vlr = 0;
    numelems = 0;
}

Deque::~Deque(){
    cout << "Comienza liberacion" << endl;
    if(!ini_vlr){
        delete[] mapa;
    }
    else{
        for(int** i=blq_ini; i<=blq_fin;i++){
            delete[] *i;
        }
        delete[] mapa;
    }
    cout << "Se libero la memoria correctamente" << endl;
}

void Deque::push_back(int x){
    if(!fin_vlr){
        *blq_fin = new int[tam_blq];
        ini_vlr =*blq_fin + (tam_blq/2);
        fin_vlr = ini_vlr;
    }
    else if(fin_vlr == *blq_fin+(tam_blq-1)){
        cout << "Se crea nuevo bloque" << endl;
        if(blq_fin == mapa+tam_mapa-1){
            cout << "Mapa lleno por la derecha"<< endl;
            return;
        }
        blq_fin++;
        *blq_fin = new int[tam_blq];
        fin_vlr = *blq_fin;
    }
    else{
        fin_vlr++;
    }
    *fin_vlr = x;
    numelems++;
}

void Deque::push_front(int x){
    if(!ini_vlr){
        *blq_ini = new int[tam_blq];
        ini_vlr =*blq_ini + (tam_blq/2);
        fin_vlr = ini_vlr;
    }
    else if(ini_vlr == *blq_ini){
        cout << "Se crea nuevo bloque" << endl;
        if(blq_ini == mapa){
            cout << "Mapa lleno por la izq"<< endl;
            return;
        }
        blq_ini--;
        *blq_ini = new int[tam_blq];
        ini_vlr = *blq_ini + (tam_blq-1);
    }
    else{
        ini_vlr--;
    }
    *ini_vlr = x;
    numelems++;
}

void Deque::pop_back(){
    if(!fin_vlr){
        throw runtime_error("No hay elementos");
        return;
    }
    else if(fin_vlr == ini_vlr ){ //Si hay 1 elem
        fin_vlr = ini_vlr = 0;
        delete[] *blq_fin;
    }
    else if(fin_vlr == *blq_fin){ // Si es el ultimo de su bloque
        cout << "Caso de ultimo en el bloque fin" << endl;
        delete[] *blq_fin;
        blq_fin--;
        fin_vlr = *blq_fin + (tam_blq-1);
    }
    else{ // Caso normal
        fin_vlr--;
    }
    numelems--;
}

void Deque::pop_front(){
    if(!ini_vlr){
        throw runtime_error("No hay elementos");
        return;
    }
    else if(ini_vlr == fin_vlr){ //Si hay 1 elem
        fin_vlr = ini_vlr = 0;
        delete[] *blq_ini;
    }
    else if(ini_vlr == *blq_ini + (tam_blq-1)){ // Si es el ultimo de su bloque
        cout << "Caso de ultimo en el bloque ini" << endl;
        delete[] *blq_ini;
        blq_ini++;
        ini_vlr = *blq_ini;
    }
    else{ // Caso normal
        ini_vlr++;
    }
    numelems--;
}

int& Deque::operator[](int i){
    if(i >= numelems || i < 0) throw runtime_error("Fuera de rango");
    int ini_fisico = ini_vlr - *blq_ini;
    int index_fisico = ini_fisico + i;
    return *(*(blq_ini + (index_fisico / tam_blq))+(index_fisico % tam_blq));
}

void Deque::print() {

    if (!ini_vlr) { 
        cout << "(vacio)" << endl;
        return;
    }
    int** blq_actual = blq_ini;
    int* vlr_actual = ini_vlr;

    for (int k = 0; k < numelems; ++k) {
        cout << *vlr_actual << ' ';

        vlr_actual++;

        if (vlr_actual == *blq_actual + tam_blq) {
            if (blq_actual != blq_fin) {
                blq_actual++;
                vlr_actual = *blq_actual;
            }
        }
    }
    cout << endl;
}


int main(){

    Deque d;
    d.push_back(1);
    d.push_back(4);
    d.push_back(5);
    d.push_front(8);
    d.push_front(9);
    d.push_back(7);
    d.push_back(2);
    d.push_front(3);
    d.push_front(2);
    d.push_front(6);
    d.push_front(4);
    d.print();
    // d.pop_back(); 
    // d.pop_front();
    // d.print();
    d[10] = 5;
    d.print();
    
    return 0;
}