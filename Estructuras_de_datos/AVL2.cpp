#include <iostream>
#include <queue>
#include <stack>
#include <algorithm> 

using namespace std;

struct Node {
    int v;
    Node * right;
    Node * left;
    int h; 

    Node(int x){
        v = x;
        right = left = 0;
        h = 0; 
    }
};

class AVLtree{
    Node * root;
    bool lado_reemp;

    int height(Node* p) {
        return p ? p->h : -1;
    }

    void altura_actualizada(Node* p) {
        if (p) {
            p->h = 1 + std::max(height(p->left), height(p->right));
        }
    }

    int FB(Node* p) {
    if (p == nullptr) {
        return 0;
    }
    return height(p->left) - height(p->right);
}

    void LL(Node*& p){ 
        Node* q = p->left;
        p->left = q->right;
        q->right = p;
        
        altura_actualizada(p);
        altura_actualizada(q);
        p = q;
    }
    
    void RR(Node*& p){
        Node* q = p->right;
        p->right = q->left;
        q->left = p;

        altura_actualizada(p);
        altura_actualizada(q);
        p = q;
    }
    
    void LR(Node*& p){
        RR(p->left);
        LL(p);
    }
    
    void RL(Node*& p){
        LL(p->right);
        RR(p);
    }

    void verificar_ruta(stack<Node**>& path) { 
        while (!path.empty()) {
            Node** p_ptr = path.top();
            path.pop();
            Node* p = *p_ptr;

            altura_actualizada(p);

            int bf = FB(p);

            if (bf > 1) { 
                if (FB(p->left) >= 0) { 
                    LL(*p_ptr);
                } else { 
                    LR(*p_ptr);
                }
            } else if (bf < -1) { 
                if (FB(p->right) <= 0) { 
                    RR(*p_ptr);
                } else { 
                    RL(*p_ptr);
                }
            }
        }
    }
    
    void clear(Node* p) {
        if (p) {
            clear(p->left);
            clear(p->right);
            delete p;
        }
    }

public:
    AVLtree();
    ~AVLtree();
    bool ins(int x);
    bool fnd(int x, Node**& p, stack<Node**>& path);
    bool remv(int x);
    Node** reemp(Node** p, stack<Node**>& path);
    void inorder(Node* p);
    void print_levels();
    void levels(Node* n);
    void imprimir();
    Node*& get_root(){return root;}
};

AVLtree::AVLtree(){
    root = 0;
    lado_reemp = 0;
}
AVLtree::~AVLtree(){
    clear(root);
}
    
bool AVLtree::ins(int x){
    Node** p;
    stack<Node**> path; 

    if (fnd(x, p, path)) {
        return false;
    }

    *p = new Node(x);

    verificar_ruta(path);
    return true;
}

bool AVLtree::remv(int x){
    Node** p;
    stack<Node**> path; 

    if (!fnd(x, p, path)) {
        return false; 
    }

    if ((*p)->left && (*p)->right) {
        path.push(p); 
        Node** q = reemp(p, path);
        (*p)->v = (*q)->v;
        p = q;
    }

    Node* t = *p;
    *p = (*p)->left ? (*p)->left : (*p)->right;
    delete t;

    verificar_ruta(path);
    return true;
}

Node** AVLtree::reemp(Node** p, stack<Node**>& path) {
    Node** q;
    if(lado_reemp){
        q = &((*p)->right);
        path.push(q);
        while((*q)->left) {
            q = &((*q)->left);
            path.push(q);
        }
    }
    else{
        q = &((*p)->left);
        path.push(q);
        while((*q)->right) {
            q = &((*q)->right);
            path.push(q);
        }
    }
    lado_reemp = !lado_reemp;
    return q;
}

bool AVLtree::fnd(int x, Node**& p, stack<Node**>& path){
    p = &root;
    while(*p && (*p)->v != x){
        path.push(p);
        if((*p)->v > x)
            p = &((*p)->left);
        else
            p = &((*p)->right);
    }
    return *p;
}

void AVLtree::inorder(Node* p){
    if(!p) return;
    inorder(p->left);
    cout << p->v << ' ';
    inorder(p->right);
}
void AVLtree::imprimir(){
    inorder(root);
    cout<< endl;
}
    
void AVLtree::print_levels() {
    std::cout<<"\nImpresion por niveles: ";
    levels(root);
    std::cout<<"\n";
}

void AVLtree::levels(Node* n) {
    if ( !n ) return;
    std::queue<Node*> q;
    q.push(n);
    while ( !q.empty() )
    {
        Node* x = q.front();
        std::cout << x->v << "(h=" << x->h << ", FB=" << FB(x) << ") ";
        if ( x->left ) q.push(x->left);
        if ( x->right ) q.push(x->right);
        q.pop();
    }
}
    
int main() {
    AVLtree a;
    int opcion,valor;
    while (true) {
        cout << "1. Insertar 2. Eliminar 3. Imprimir 4. Salir" << endl;
        cin >> opcion;

        switch (opcion) {
            case 1:
                cin >> valor;
                a.ins(valor);
                a.print_levels();
                break;
            case 2:
                cin >> valor;
                if (a.remv(valor)) {
                    cout<<"Valor "<<valor<< " eliminado"<< endl;
                } else {
                    cout <<"No se encontro en el arbol"<<endl;
                }
                a.print_levels();
                break;
            case 3:
                a.print_levels();
                cout << endl;
                a.imprimir();
                break;
            case 4:
                return 0;
            default:
                cout << "Opcion no valida" << endl;
        }
    }

    return 0;
}