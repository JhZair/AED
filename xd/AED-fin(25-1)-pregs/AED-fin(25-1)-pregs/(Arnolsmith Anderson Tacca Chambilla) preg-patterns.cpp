#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

void searchPattern(char matrix[10][10] /* otros parametros aqui*/)
{
    
}

int main()
{
    int totalPatterns = 0;
    char matrix[10][10] = {
       {'.', '#', '#', '.', '.', '.', '#', '#', '.', '.'},
       {'.', '.', '.', '.', '.', '.', '#', '.', '#', '#'},
       {'.', '.', '#', '#', '.', '.', '.', '.', '#', '.'},
       {'.', '.', '#', '.', '.', '.', '.', '.', '.', '.'},
       {'#', '#', '.', '.', '#', '#', '.', '#', '#', '.'},
       {'.', '.', '.', '.', '#', '.', '.', '.', '.', '.'},
       {'.', '.', '.', '.', '.', '#', '#', '.', '.', '.'},
       {'.', '.', '.', '#', '#', '#', '.', '#', '#', '.'},
       {'.', '#', '#', '#', '.', '.', '.', '#', '.', '.'},
       {'.', '#', '.', '.', '.', '.', '.', '.', '#', '#'}
   };
   
    // Creación de threads aqui
    // para pasar la matriz a la funcion seria asi:
    // => searchPattern(matrix, /*otros parametros aqui*/ )
    
    
   std::cout << "\nTotal de patrones encontrados: " << totalPatterns << std::endl;
   
   return 0;
}
