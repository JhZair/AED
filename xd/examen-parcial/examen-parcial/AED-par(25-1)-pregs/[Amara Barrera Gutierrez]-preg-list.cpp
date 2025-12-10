#include <iostream>

struct CNode
{
    CNode(int _v)
    {   v = _v; next = 0;   }
    int v;
    CNode* next;
};

class CList
{
public:
    CList();
    ~CList();
    bool Find(int v, CNode**& p);
    bool Ins(int v);
    bool Rem(int v);
    void Print();
private:
    CNode* head;
};

CList::CList()
{   head = 0;   }

CList::~CList()
{
    while (head)
    {   CNode* temp = head;
        head = head->next;
        delete temp;
    }
}

bool CList::Find(int x, CNode**& p)
{
    for ( p = &head; *p &&  (*p)->v <= x; p = &((*p)->next) ); 
    return *p; //&& (*p)->v == x;
}

bool CList::Ins(int x)
{
    CNode** p;
    Find(x, p);
	CNode* t = new CNode(x);
	t->next = *p;
	*p = t;
	return 1;
}

bool CList::Rem(int x)
{
    CNode** p;
    if ( !Find(x, p) ) return 0;
    
    CNode* t = *p;
    if((*p)->v == (*p)->next->v ){
    	*p = t->next->next;
    	delete t->next;
	}
	else{
		*p = t->next;
		delete t;
    	return 1;
	}
    
}

void CList::Print()
{
    for ( CNode* t = head; t; t = t->next )
        std::cout<<t->v<<" ";
    std::cout<<"\n";
}

int main()
{
    CList l;
    
    // Prueba inserción básica
    std::cout << "Insertando 8, 15, 5, 11:" << std::endl;
    l.Ins(8);
    l.Ins(15);
    l.Ins(5);
    l.Ins(11);
    l.Print();
    
    // Prueba inserción de valores repetidos
    std::cout << "Insertando valores repetidos (8, 5, 15, 5, 11):" << std::endl;
    l.Ins(8);
    l.Ins(5);
    l.Ins(15);
    l.Ins(5);
    l.Ins(11);
    l.Print();
    
    // Prueba eliminación de valores con múltiples ocurrencias
    std::cout << "Eliminando la primera ocurrencia de 5:" << std::endl;
    l.Rem(5);
    l.Print();
    
    std::cout << "Eliminando la primera ocurrencia de 5 otra vez:" << std::endl;
    l.Rem(5);
    l.Print();
    
    std::cout << "Eliminando la primera ocurrencia de 8:" << std::endl;
    l.Rem(8);
    l.Print();
    
    std::cout << "Eliminando la primera ocurrencia de 8 otra vez:" << std::endl;
    l.Rem(8);
    l.Print();
    
    // Prueba con inserción adicional después de eliminar
    std::cout << "Insertando 3, 11, 11:" << std::endl;
    l.Ins(3);
    l.Ins(11);
    l.Ins(11);
    l.Print();
    
    // Prueba eliminando todos los valores uno por uno
    std::cout << "Eliminando todos los valores uno por uno:" << std::endl;
    while (l.Rem(11)) {}
    l.Print();
    
    while (l.Rem(15)) {}
    l.Print();
    
    l.Rem(3);
    l.Print();
    
    return 0;
}

