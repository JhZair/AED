#include <iostream>
#include <thread>
#include <vector>
using namespace std;

int F1(char arr[], int size)
{	int Acount = 0;
int Bcount = 0;
int Ccount = 0;
int Dcount = 0;
int Ecount = 0;

m.lock();

	for (int i = 0; i < size; i++)
	{	if (arr[i] = 'a')
			++Acount;
		if (arr[i] = 'b')
			++Bcount;
		if (arr[i] = 'c')
			++Ccount;
		if (arr[i] = 'd')
			++Dcount;
		if (arr[i] = 'e')
			++Ecount;
	}
	
m.unlock();

    cout << Acount << endl;
    cout << Bcount << endl;
    cout << Ccount << endl;
    cout << Dcount << endl;
    cout << Ecount << endl;

}


int main() {
    char letras[165] = {'a','b','c','d','e','a','c','b','d','e','b','a','e','c','d',
                        'a','b','c','e','d','c','d','a','e','b','d','a','c','b','e',
                        'e','b','d','c','a','b','e','a','d','c','a','c','e','b','d',
                        'c','a','b','e','d','d','e','a','c','b','e','d','c','a','b',
                        'b','c','d','e','a','c','b','a','d','e','a','d','b','e','c',
                        'b','a','e','c','d','e','a','c','d','b','d','e','b','a','c',
                        'c','b','a','e','d','a','c','e','b','d','a','b','e','d','c',
                        'b','a','c','e','d','d','c','a','b','e','e','d','a','c','b',
                        'c','e','b','d','a','a','b','d','e','c','b','d','c','a','e',
                        'c','e','a','b','d','e','a','d','c','b','d','b','e','a','c',
                        'a','c','b','d','e','b','e','a','c','d','a','a','c','c','b'};
    
    
    thread t1(F1, arr, 42);
    thread t2(F1, arr[42], 41);
    thread t3(F1, arr[83], 41);
    thread t4(F1, arr[124], 41);
    
    t1.join();
	t2.join();
    t3.join();
    t4.join();
	
    
    return 0;
}
