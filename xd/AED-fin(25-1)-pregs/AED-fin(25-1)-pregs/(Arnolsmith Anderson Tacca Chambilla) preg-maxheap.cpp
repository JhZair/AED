#include <iostream>

int HijoIzq(int i) { return 2 * i + 1; }
int HijoDer(int i) { return 2 * i + 2; }

void XMayores(int heap[], int size, int x)
{
    
}

int main()
{
    int heap1[15] = {95, 83, 90, 75, 80, 89, 70, 60, 65, 55, 45, 87, 40, 35, 25};
    int heap2[15] = {100, 95, 90, 80, 85, 88, 75, 70, 78, 82, 83, 86, 73, 72, 71};
    int heap3[15] = {98, 95, 92, 91, 85, 80, 75, 70, 88, 82, 83, 78, 76, 73, 72};
    
    XMayores(heap1, 15, 4);
    XMayores(heap2, 15, 4);
    XMayores(heap3, 15, 4);
    
    return 0;
}
