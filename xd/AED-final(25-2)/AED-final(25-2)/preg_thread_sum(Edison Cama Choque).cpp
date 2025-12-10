#include<iostream>
#include<vector>
#include<thread>
#include<algorithm>
#include <stack>
////////////////////////////////////////////////////////////////////////////////////////////////////////




struct CBinNode
{
    CBinNode(int _v)
    {
        value = _v; nodes[0] = nodes[1] = 0;
    }
    int value;
    CBinNode* nodes[2];
};

////////////////////////////////////////////////////////////////////////////////////////////////////////

class CBinTree
{
public:
    CBinTree();
    bool Insert(int x);
    bool Insert(int* v, int n);
    void Print();
    void ThreadWorker(/* parametros aqui */);
    int TreeSum();
    int SumarVector(std::vector<int> subject);

private:
    bool Find(int x, CBinNode**& p);
    void InOrder(CBinNode* n);
    CBinNode* m_root;
};

CBinTree::CBinTree()
{
    m_root = 0;
}

bool CBinTree::Find(int x, CBinNode**& p)
{
    for (p = &m_root;
        *p && (*p)->value != x;
        p = &((*p)->nodes[(*p)->value < x]));
    return *p && (*p)->value == x;
}

bool CBinTree::Insert(int x)
{
    CBinNode** p;
    if (Find(x, p)) return 0;
    *p = new CBinNode(x);
    return 0;
}

bool CBinTree::Insert(int* v, int n)
{
    bool b = 1;
    for (int i = 0; i < n; ++i)
        b &= Insert(v[i]);
    return b;
}

void CBinTree::InOrder(CBinNode* n)
{
    if (!n) return;
    InOrder(n->nodes[0]);
    std::cout << n->value << " ";
    InOrder(n->nodes[1]);
}

void CBinTree::Print()
{
    InOrder(m_root);
    std::cout << "\n";
}

int CBinTree::SumarVector(std::vector<int> subject) {
    int sumatoria = 0;

    for (int i = 0;i < subject.size();i++) {
        sumatoria += subject[i];

    }
    return sumatoria;

};



void CBinTree::ThreadWorker(/* parametros aqui */)
{
    std::vector<int> elementos;

    //RECORRER TODO CON PILA y elementos.push_back(pila.top);


    int size_de_subvectores = elementos.size() / 5;
    std::vector<int> division1;
    std::vector<int> division2;
    std::vector<int> division3;
    std::vector<int> division4;
    std::vector<int> division5;

    for (int j = 0;j < 5;j++) {
        for (int i = 0;i < elementos.size();i++) {
            if (i < size_de_subvectores * 1)
            {
                division1.push_back(elementos[i]);
            }
            else if (i < size_de_subvectores * 2 && i> size_de_subvectores) {
                division2.push_back(elementos[i]);
            }
            else if (i < size_de_subvectores * 3 && i>size_de_subvectores * 2) {
                division3.push_back(elementos[i]);
            }
            else if (i < size_de_subvectores * 4 && i>size_de_subvectores * 3) {
                division4.push_back(elementos[i]);
            }
            else if (i >= size_de_subvectores * 4) {
                division5.push_back(elementos[i]);
            }
        }
    }





}

int CBinTree::TreeSum()
{
    std::vector<int> elementos;
    std::vector<std::thread> threads;
    std::stack<CBinNode*> pila;
    if (m_root == nullptr) return;

    CBinNode* actual = m_root;
    while (actual !=nullptr|| !pila.empty()){
        while (actual != nullptr) {
            pila.push(actual);
        }

    actual = actual->nodes[0];
    }
    actual = pila.top();
    pila.pop();
    elementos.push_back(actual->value);
    actual = actual->nodes[1];
    //RECORRER TODO CON PILA y elementos.push_back(pila.top);


    int size_de_subvectores = elementos.size() / 5;
    std::vector<int> division1;
    std::vector<int> division2;
    std::vector<int> division3;
    std::vector<int> division4;
    std::vector<int> division5;

    for (int j = 0;j < 5;j++) {
        for (int i = 0;i < elementos.size();i++) {
            if (i < size_de_subvectores * 1)
            {
                division1.push_back(elementos[i]);
            }
            else if (i < size_de_subvectores * 2 && i> size_de_subvectores) {
                division2.push_back(elementos[i]);
            }
            else if (i < size_de_subvectores * 3 && i>size_de_subvectores * 2) {
                division3.push_back(elementos[i]);
            }
            else if (i < size_de_subvectores * 4 && i>size_de_subvectores * 3) {
                division4.push_back(elementos[i]);
            }
            else if (i >= size_de_subvectores * 4) {
                division5.push_back(elementos[i]);
            }
        }
    }
    threads.push_back(std::thread(SumarVector(division1)));
    threads.push_back(std::thread(SumarVector(division2)));
    threads.push_back(std::thread(SumarVector(division3)));
    threads.push_back(std::thread(SumarVector(division4)));
    threads.push_back(std::thread(SumarVector(division5)));

    for (auto& th : threads)
        th.join();







    return 0;
}





int main()
{
    CBinTree t;
    int v[63] = { 57, 17, 83, 9, 28, 71, 95, 04, 12, 20, 33, 60, 79, 88, 99, 02, 06, 10, 14, 18, 22, 30, 36, 58, 63, 75, 82, 86, 90, 97, 102, 1, 3, 5, 7, 8, 11, 13, 15, 16, 19, 21, 23, 29, 31, 34, 38, 55, 59, 62, 70, 72, 78, 81, 83, 85, 89, 92, 94, 96, 98, 101, 104 };
    t.Insert(v, 63);
    std::cout << "La suma es: " << t.TreeSum() << "\n";
}