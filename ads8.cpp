#include <iostream>
#include <list>
#include <iterator>
#include <algorithm>
using namespace std;
struct Node{
    int value, degree;
    Node *child, *sibling, *parent;
};
class BinomialHeap{
public:
    std::list<Node *> heap;
    Node *make_heap(int key){
        Node *newNode = new Node;
        newNode->value = key;
        newNode->parent = newNode->sibling = newNode->child = nullptr;
        newNode->degree = 0;
        return newNode;
    }
    void insert(int key){
        Node *newNode = make_heap(key);
        heap.push_back(newNode);
        merge();
    }
    Node *find_min(){
        if (heap.empty())
            return nullptr;
        std::list<Node *>::iterator it = heap.begin();
        Node *min = *it;
        while (it != heap.end())
        {
            if ((*it)->value < min->value)
                min = *it;
            it++;
        }
        return min;
    }
private:
    void merge(){
        if (heap.size() <= 1)
            return;
        heap.sort([](Node *a, Node *b)
                  { return a->degree < b->degree; });
        list<Node *>::iterator prev = heap.begin();
        list<Node *>::iterator curr = prev;
        curr++;
        list<Node *>::iterator next = heap.end();
        while (curr != next){
            if ((*prev)->degree < (*curr)->degree ||
                (next != heap.end() && (*next)->degree == (*prev)->degree + 1)){
                prev = curr;
                curr++;
            }
            else if ((*prev)->value < (*curr)->value){
                (*prev)->sibling = (*curr)->sibling;
                (*curr)->parent = *prev;
                (*curr)->sibling = (*prev)->child;
                (*prev)->child = *curr;
                (*prev)->degree++;
                curr = heap.erase(curr);
            }
            else{
                if (prev == heap.begin()){
                    heap.pop_front();
                }
                else{
                    heap.erase(prev);
                    prev = curr;
                }
                (*curr)->parent = *prev;
                (*curr)->sibling = (*prev)->child;
                (*prev)->child = *curr;
                (*prev)->degree++;
                curr++;
            }
            if (curr != next)
                next = std::next(curr);
        }
    }
};
int main(){
    BinomialHeap heap;
    int choice, val;
    do{
        cout << "Choose operation:\n";
        cout << "1. Insert\n";
        cout << "2. Find Minimum\n";
        cout << "3. Exit\n";
        cin >> choice;

        switch (choice){
        case 1:
            cout << "Enter value to insert: ";
            cin >> val;
            heap.insert(val);
            break;
        case 2:
            if (Node *minNode = heap.find_min())
                cout << "Minimum value: " << minNode->value << "\n";
            else
                cout << "Heap is empty.\n";
            break;
        case 3:
            break;
        default:
            cout << "Invalid choice.\n";
        }
    } while (choice != 3);
    return 0;
}
