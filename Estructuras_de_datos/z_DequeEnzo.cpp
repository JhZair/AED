#include <iostream>
using namespace std;

class cDeque
{
private:
	int **mapa;
	int **M_INI;
	int **M_FIN;
	int *V_INI;
	int *V_FIN;
public:
	void push_front(int n);
	void push_back(int n);
	int pop_front();
	int pop_back();
	int &operator[](int id);
	cDeque()
	{
		mapa=new int*[11]; 
		M_INI=mapa+5;
		M_FIN=M_INI;
		*V_INI=NULL;
		*V_FIN=NULL;
	}
};

void cDeque::push_back(int n)
{
	if(!V_FIN)
	{
		M_INI=mapa+5;
		M_FIN=M_INI;
		*M_INI= new int[11];
		V_INI=*M_INI+5;
		V_FIN=V_INI;
		*V_INI=n;
	}
	else if(V_FIN==*M_FIN+10)
	{
		if(M_FIN==mapa+10)
		{
			cout << "LIMITES LLENOS";
			return;
		}
		M_FIN++;
		*M_FIN= new int[11];
		V_FIN=*M_FIN;
		*V_FIN=n;
	}
	else
	{
		V_FIN++;
		*V_FIN=n;
	}
}

void cDeque::push_front(int n)
{
	if(!V_INI) // V_INI == NULL
	{
		M_INI=mapa+5;
		M_FIN=M_INI;
		*M_INI= new int[11];
		V_INI=*M_INI+5;
		V_FIN=V_INI;
		*V_INI=n;
	}
	else if(V_INI==*M_INI)
	{
		if(M_INI==mapa)
		{
			cout << "LIMITES LLENOS";
			return;
		}
		
		M_INI--;
		*M_INI= new int[11];
		V_INI=*M_INI+10;
		*V_INI=n;
	}
	else
	{
		V_INI--;
		*V_INI=n;
	}
}

int cDeque::pop_front()
{
	int retorno=0;
	if(!V_INI)
	{
		cout << "No hay elementos" << endl;
		return -1;
	}
	else if(V_INI==V_FIN)
	{
		retorno=*V_INI;
		V_INI=NULL;
		V_FIN=NULL;
		delete [] *M_INI;
	}
	else if(V_INI==*M_INI+10)
	{
		retorno=*V_INI;
		delete [] *M_INI;
		M_INI++;
		V_INI=*M_INI;
	}
	else
	{
		retorno=*V_INI;
		V_INI++;
	}
	return retorno;
}
int cDeque::pop_back()
{
	int retorno=0;
	if(!V_FIN)
	{
		cout << "No hay elementos" << endl;
		return -1;
	}
	else if(V_INI==V_FIN)
	{
		retorno=*V_INI;
		V_INI=NULL;
		V_FIN=NULL;
		delete [] *M_INI;
	}
	else if(V_FIN==*M_FIN)
	{
		retorno=*V_FIN;
		delete [] *M_FIN;
		M_FIN--;
		V_FIN=*M_FIN+10;
	}
	else
	{
		retorno=*V_FIN;
		V_FIN--;
	}
	return retorno;
}
int &cDeque::operator[](int id)
{
	if(!V_INI)
	{
		cout << "No hay elementos" << endl;
		return *V_INI;
	}
	int elem_faltan = (V_INI-*M_INI);
	int n_id = id+ elem_faltan;
	return *(*(M_INI+(n_id/11))+n_id%11);
}
int main() 
{
	cDeque prueba;
	prueba.push_back(1);
	prueba.push_back(2);
	prueba.push_back(3);
	prueba.push_back(4);
	prueba.push_back(1);
	prueba.push_back(2);
	prueba.push_back(3);
	prueba.push_back(4);
	prueba.push_front(1);
	prueba.push_front(2);
	prueba.push_front(3);
	cout << prueba.pop_back() << endl;
	cout << prueba.pop_back() << endl;
	cout << prueba.pop_back() << endl;
	cout << prueba.pop_back() << endl;
	cout << prueba.pop_back() << endl;
	cout << prueba.pop_back() << endl;
	cout << prueba.pop_back() << endl;
	cout << prueba.pop_back() << endl;
	cout << prueba.pop_back() << endl;
	cout << prueba.pop_back() << endl;
	cout << prueba.pop_front() << endl;
	cout << prueba.pop_front() << endl;
	cout << prueba.pop_front() << endl;
	cout << prueba.pop_front() << endl;
	cout << prueba.pop_front() << endl;
	cout << prueba.pop_front() << endl;
}
