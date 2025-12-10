#include <iostream>
#include <string>
#include <cmath>
using namespace std;

// Crear function objects para >50 y múltiplos de 7

class Filters
{
public:
	bool mayores(int* arr, int n)
	{
		for (int i = 0; i < n; i++)
		{	
			if (arr[i] > 50)
			{
				cout << arr[i];
			}
		}
	};
	
	bool multiplos(int* arr, int n)
	{
		for (int i = 0; i < n; i++)
		{
			if (arr[i]%7 == 0)
				cout << arr[i];
		}
	}
};
// Crear funciones para rango 40-70 y cuadrados perfectos

bool enRango(int* arr, int n)
	{
		for (int i = 0; i < n; i++)
		{
			if ((arr[i] > 40) && (arr[i] < 70))
				cout << arr[i];
		}
	}
	
bool cuadrados(int* arr, int n)
{
	for (int i = 0; i < n; i++)
	{
		int x;
		if (arr[i] == (x*x))
		{
			cout << arr[i];
		}
	}
}



// Completar función para filtrar con function objects
void filtrarConFunctor(int* arr, int size, Filters f)
{
   bool (Filters::*pfx)(int*, int);
   pfx = &Filters::mayores(arr, size);
   bool a = (f.*pfx)(arr, size);
   
   bool (Filters::*pfx2)(int*, int);
   pfx2 = &Filters::multiplos(arr, size);
   bool b = (f.*pfx2)(arr, size);
   
   
}

// Completar función para filtrar con punteros a funciones
void filtrarConPunteroAFuncion(int arr[], int size, bool (*pf)(int*, int))
{
   bool (*pf)(int*, int);
   pf = &enRango;
   bool a = (*pf)(arr, size);
   
   void (*pf2)(int*, int);
   pf2 = &cuadrados;
   bool b = (*pf2)(arr, size);
   
}

int main()
{
    int numeros[12] = {12, 7, 23, 56, 9, 88, 45, 67, 25, 91, 16, 4};
   
    // Usar function objects
    filtrarConFunctor(numeros, 12, a);
    filtrarConFunctor(numeros, 12, b);

    // Usar punteros a funciones
    filtrarConPunteroAFuncion(numeros, 12, a);
    filtrarConPunteroAFuncion(numeros, 12, b);
   
   return 0;
}


