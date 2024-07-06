#include <iostream>
using namespace std;
class BPlusTreeNode{
    char *values;
    int t;
    BPlusTreeNode **pointers;
    int n;
    bool leaf;

public:
    BPlusTreeNode(int _t, bool _leaf);
    int findValue(char val);
    void remove(char val);
    void removeFromLeaf(int idx);
    void removeFromNonLeaf(int idx);
    char getPred(int idx);
    char getSucc(int idx);
    void fill(int idx);
    void borrowFromPrev(int idx);
    void borrowFromNext(int idx);
    void merge(int idx);
    void insertNonFull(char val);
    void splitChild(int i, BPlusTreeNode *y);
    void traverse();
    BPlusTreeNode *search(char val);
    friend class BPlusTree;
};
class BPlusTree{
    BPlusTreeNode *root;
    int t;

public:
    BPlusTree(int _t){
        root = nullptr;
        t = _t;
    }
    void traverse(){
        if (root != nullptr)
            root->traverse();
    }
    BPlusTreeNode *search(char val){
        return (root == nullptr) ? nullptr : root->search(val);
    }
    void insert(char val);
    void remove(char val);
};
BPlusTreeNode::BPlusTreeNode(int t1, bool leaf1){
    t = t1;
    leaf = leaf1;
    values = new char[2 * t - 1];
    pointers = new BPlusTreeNode *[2 * t];
    n = 0;
}
int BPlusTreeNode::findValue(char val){
    int idx = 0;
    while (idx < n && values[idx] < val)
        idx++;
    return idx;
}
void BPlusTreeNode::remove(char val){
    int idx = findValue(val);
    if (idx < n && values[idx] == val){
        if (leaf)
            removeFromLeaf(idx);
        else
            removeFromNonLeaf(idx);
    }
    else{
        if (leaf){
            cout << "The value " << val << " does not exist in the tree, hence it couldn't be deleted\n";
            return;
        }
        bool flag = (idx == n);
        if (pointers[idx]->n < t)
            fill(idx);
        if (flag && idx > n)
            pointers[idx - 1]->remove(val);
        else
            pointers[idx]->remove(val);
    }
}
void BPlusTreeNode::removeFromLeaf(int idx){
    for (int i = idx + 1; i < n; ++i)
        values[i - 1] = values[i];
    n--;
}
void BPlusTreeNode::removeFromNonLeaf(int idx){
    char val = values[idx];
    if (pointers[idx]->n >= t){
        char pred = getPred(idx);
        values[idx] = pred;
        pointers[idx]->remove(pred);
    }
    else if (pointers[idx + 1]->n >= t){
        char succ = getSucc(idx);
        values[idx] = succ;
        pointers[idx + 1]->remove(succ);
    }
    else{
        merge(idx);
        pointers[idx]->remove(val);
    }
}
char BPlusTreeNode::getPred(int idx){
    BPlusTreeNode *cur = pointers[idx];
    while (!cur->leaf)
        cur = cur->pointers[cur->n];
    return cur->values[cur->n - 1];
}
char BPlusTreeNode::getSucc(int idx){
    BPlusTreeNode *cur = pointers[idx + 1];
    while (!cur->leaf)
        cur = cur->pointers[0];
    return cur->values[0];
}
void BPlusTreeNode::fill(int idx){
    if (idx != 0 && pointers[idx - 1]->n >= t)
        borrowFromPrev(idx);
    else if (idx != n && pointers[idx + 1]->n >= t)
        borrowFromNext(idx);
    else{
        if (idx != n)
            merge(idx);
        else
            merge(idx - 1);
    }
}
void BPlusTreeNode::borrowFromPrev(int idx){
    BPlusTreeNode *child = pointers[idx];
    BPlusTreeNode *sibling = pointers[idx - 1];
    for (int i = child->n - 1; i >= 0; --i)
        child->values[i + 1] = child->values[i];
    child->values[0] = values[idx - 1];
    if (!child->leaf){
        for (int i = child->n; i >= 0; --i)
            child->pointers[i + 1] = child->pointers[i];
    }
    values[idx - 1] = sibling->values[sibling->n - 1];
    child->n += 1;
    sibling->n -= 1;
}
void BPlusTreeNode::borrowFromNext(int idx){
    BPlusTreeNode *child = pointers[idx];
    BPlusTreeNode *sibling = pointers[idx + 1];
    child->values[(child->n)] = values[idx];
    if (!child->leaf)
        child->pointers[(child->n) + 1] = sibling->pointers[0];
    values[idx] = sibling->values[0];
    for (int i = 1; i < sibling->n; ++i)
        sibling->values[i - 1] = sibling->values[i];
    if (!sibling->leaf){
        for (int i = 1; i <= sibling->n; ++i)
            sibling->pointers[i - 1] = sibling->pointers[i];
    }
    child->n += 1;
    sibling->n -= 1;
}
void BPlusTreeNode::merge(int idx){
    BPlusTreeNode *child = pointers[idx];
    BPlusTreeNode *sibling = pointers[idx + 1];
    child->values[t - 1] = values[idx];
    for (int i = 0; i < sibling->n; ++i)
        child->values[i + t] = sibling->values[i];
    if (!child->leaf){
        for (int i = 0; i <= sibling->n; ++i)
            child->pointers[i + t] = sibling->pointers[i];
    }
    for (int i = idx + 1; i < n; ++i)
        values[i - 1] = values[i];
    for (int i = idx + 2; i <= n; ++i)
        pointers[i - 1] = pointers[i];
    child->n += sibling->n + 1;
    n--;
    delete sibling;
}
void BPlusTreeNode::insertNonFull(char val){
    int i = n - 1;
    if (leaf){
        while (i >= 0 && values[i] > val)
        {
            values[i + 1] = values[i];
            i--;
        }
        values[i + 1] = val;
        n = n + 1;
    }
    else{
        while (i >= 0 && values[i] > val)
            i--;
        if (pointers[i + 1]->n == (2 * t - 1)){
            splitChild(i + 1, pointers[i + 1]);
            if (values[i + 1] < val)
                i++;
        }
        pointers[i + 1]->insertNonFull(val);
    }
}
void BPlusTreeNode::splitChild(int i, BPlusTreeNode *y){
    BPlusTreeNode *z = new BPlusTreeNode(y->t, y->leaf);
    n++;
    for (int j = n - 1; j > i; j--)
    {
        values[j] = values[j - 1];
        pointers[j + 1] = pointers[j];
    }
    values[i] = y->values[t - 1];
    for (int j = t - 1; j < y->n - 1; j++)
        z->values[j - t] = y->values[j];
    if (!y->leaf)
    {
        for (int j = t; j <= y->n; j++)
            z->pointers[j - t] = y->pointers[j];
    }
    y->n = t - 1;
    pointers[i + 1] = z;
}
void BPlusTreeNode::traverse(){
    int i;
    for (i = 0; i < n; i++){
        if (!leaf)
            pointers[i]->traverse();
        cout << " " << values[i];
    }
    if (!leaf)
        pointers[i]->traverse();
}
BPlusTreeNode *BPlusTreeNode::search(char val){
    int i = 0;
    while (i < n && val > values[i])
        i++;
    if (values[i] == val)
        return this;
    if (leaf)
        return nullptr;
    return pointers[i]->search(val);
}
void BPlusTree::insert(char val){
    if (root == nullptr){
        root = new BPlusTreeNode(t, true);
        root->values[0] = val;
        root->n = 1;
    }
    else{
        if (root->n == (2 * t - 1))
        {
            BPlusTreeNode *s = new BPlusTreeNode(t, false);
            s->pointers[0] = root;
            s->splitChild(0, root);
            int i = 0;
            if (s->values[0] < val)
                i++;
            s->pointers[i]->insertNonFull(val);
            root = s;
        }
        else
            root->insertNonFull(val);
    }
}
void BPlusTree::remove(char val){
    if (!root){
        cout << "The tree is empty\n";
        return;
    }
    root->remove(val);
    if (root->n == 0){
        BPlusTreeNode *tmp = root;
        if (root->leaf)
            root = nullptr;
        else
            root = root->pointers[0];
        delete tmp;
    }
}
int main(){
    BPlusTree t(3);
    char values[] = {'c', 'a', 'h', 'f', 'd', 'b', 'e', 'i', 'j', 'g','k'};
    int n = sizeof(values) / sizeof(values[0]);
    for (int i = 0; i < n; i++)
        t.insert(values[i]);
    cout << "Traversal of the constructed B+ tree: ";
    t.traverse();
    cout << endl;
    char val = 'f';
    (t.search(val) != nullptr) ? cout << "Present\n" : cout << "Not Present\n";
    val = 'k';
    (t.search(val) != nullptr) ? cout << "Present\n" : cout << "Not Present\n";
    val = 'b';
    t.remove(val);
    cout << "Traversal after removing " << val << ": ";
    t.traverse();
    cout << endl;
    val = 'h';
    t.remove(val);
    cout << "Traversal after removing " << val << ": ";
    t.traverse();
    cout << endl;
    return 0;
}