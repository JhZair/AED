#include <iostream>
#include <vector>
using namespace std;

struct cLess{
	bool operator()(int a, int b){
		return a < b;
	}
};
struct cGreater{
	bool operator()(int a, int b){
		return a > b;
	}
};

template<class O>
class cHeap{
	vector<int> heap;
	O functor;
	void bubbleUp(int index){
        while (index > 0) {
            int parent = (index - 1)/2;
            if (functor(heap[index], heap[parent])){
                swap(heap[index], heap[parent]);
                index = parent;
            } else{
                break;
            }
        }
    }
    void bubbleDown(int index){
        int size = heap.size();
        while (true) {
            int left = 2*index + 1;
            int right = 2*index + 2;
            int indx_elegido = index;
            if (left < size && functor(heap[left], heap[indx_elegido])){
                indx_elegido = left;
            }
            if (right < size && functor(heap[right], heap[indx_elegido])){
                indx_elegido = right;
            }
            if (indx_elegido == index) {
                break;
            }
            swap(heap[index], heap[indx_elegido]);
            index = indx_elegido;
        }
    }
public:
	cHeap(){}
	void push(int x){
		heap.push_back(x);
		bubbleUp(heap.size()-1);
	}
	void pop(int x){ 		// no debería poderse elegir el elem a borrar ya que debe ser en tiempo O(log n), por lo que solo debería haber pop_top()
		int index = -1;		
		for(size_t i = 0; i < heap.size(); i++){
			if(heap[i] == x){
				index = i;
				break;
			}
		}
		if(index == -1)return;
		heap[index] = heap[heap.size()-1];
		heap.pop_back();
		if (index > 0){
             if (functor(heap[index], heap[(index-1)/2])){
                 bubbleUp(index);
                 return;
             }
        }
        bubbleDown(index);
	}
	void pop_top() {
        if (heap.empty()) return;
        heap[0] = heap.back();
        heap.pop_back();
        bubbleDown(0);
    }
	int top(){
		return heap[0];
	}
	void print(){
		for(size_t i = 0; i < heap.size(); i++){
			cout << heap[i] << ' ';
		}
		cout << endl;
	}
};

int main(int argc, char *argv[]) {
	cHeap<cLess> heap;
	heap.push(5);heap.print();
	heap.push(15);heap.print();
	heap.push(21);heap.print();
	heap.push(12);heap.print();
	heap.push(2);heap.print();
	heap.pop(5);heap.print();
	heap.pop(21);heap.print();
	heap.pop(90);heap.print();
	cout << "Top es: " << heap.top() << endl;
	
	return 0;
}
