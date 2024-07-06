#include <iostream>
#include <list>
#include <cmath>
#include <limits>
#include <vector> 
using namespace std;
struct Node{
    int key;
    int degree;
    Node *parent;
    Node *child;
    Node *next;
    Node *prev;
    bool mark;
    Node(int val) : key(val), degree(0), parent(nullptr), child(nullptr), next(this), prev(this), mark(false) {}
};
class FibonacciHeap{
private:
    Node *minNode = nullptr;
    list<Node *> roots;
    int numNodes = 0;
    void link(Node *y, Node *x){
        // Remove y from root list
        y->prev->next = y->next;
        y->next->prev = y->prev;
        if (x->child){
            y->prev = x->child;
            y->next = x->child->next;
            x->child->next->prev = y;
            x->child->next = y;
        }
        else{
            x->child = y;
            y->next = y->prev = y;
        }
        y->parent = x;
        y->mark = false;
    }
    void consolidate(){
        int maxDegree = floor(log(numNodes) / log(2.0));
        vector<Node *> A(maxDegree + 1, nullptr);
        for (Node *w : roots){
            Node *x = w;
            int d = x->degree;
            while (A[d]){
                Node *y = A[d];
                if (x->key > y->key){
                    swap(x, y);
                }
                link(y, x);
                A[d] = nullptr;
                d++;
            }
            A[d] = x;
        }
        minNode = nullptr;
        for (Node *n : A){
            if (n){
                if (!minNode){
                    roots.clear();
                    roots.push_back(n);
                    minNode = n;
                }
                else{
                    roots.push_back(n);
                    if (n->key < minNode->key){
                        minNode = n;
                    }
                }
            }
        }
    }
public:
    void insert(int val){
        Node *newNode = new Node(val);
        if (!minNode){
            roots.push_back(newNode);
            minNode = newNode;
        }
        else{
            roots.push_back(newNode);
            if (val < minNode->key){
                minNode = newNode;
            }
        }
        numNodes++;
    }
    int find_min(){
        if (minNode)
            return minNode->key;
        return numeric_limits<int>::max();
    }
    void make_heap(){
        minNode = nullptr;
        roots.clear();
        numNodes = 0;
    }
};
int main(){
    FibonacciHeap heap;
    int choice, value;
    while (true){
        cout << "Choose an operation from the following:\n";
        cout << "1. Make_heap\n2. Insert\n3. Find_min\n4. Exit\n";
        cin >> choice;
        switch (choice){
        case 1:
            heap.make_heap();
            break;
        case 2:
            cout << "Enter value to insert: ";
            cin >> value;
            heap.insert(value);
            break;
        case 3:
            value = heap.find_min();
            if (value != numeric_limits<int>::max())
                cout << "Minimum value: " << value << endl;
            else
                cout << "Heap is empty\ninsert values\n";
            break;
        case 4:
            return 0;
        }
    }
    return 0;
}
