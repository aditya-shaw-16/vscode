#include <iostream>
#include <vector>
using namespace std;

class BTreeNode {
public:
    vector<int> keys;
    vector<BTreeNode*> children;
    bool isLeaf;
    int minDegree;

    BTreeNode(int minDegree, bool isLeaf);
    void insertNonFull(int k);
    void splitChild(int i, BTreeNode* y);
    void traverse();
    void remove(int k);
    int findKey(int k);

private:
    void removeFromLeaf(int idx);
    void removeFromNonLeaf(int idx);
    int getPred(int idx);
    int getSucc(int idx);
    void fill(int idx);
    void borrowFromPrev(int idx);
    void borrowFromNext(int idx);
    void merge(int idx);
};

class BTree {
public:
    BTreeNode* root;
    int minDegree;

    BTree(int minDegree) : minDegree(minDegree), root(nullptr) {}
    void insert(int k);
    void remove(int k) {
        if (!root) {
            cout << "The tree is empty\n";
            return;
        }
        root->remove(k);
        if (root->keys.size() == 0) {
            BTreeNode* tmp = root;
            if (root->isLeaf)
                root = nullptr;
            else
                root = root->children[0];
            delete tmp;
        }
    }
    void traverse() {
        if (root) root->traverse();
    }
};

BTreeNode::BTreeNode(int minDegree, bool isLeaf) : minDegree(minDegree), isLeaf(isLeaf) {
    keys.reserve(2*minDegree-1);
    children.reserve(2*minDegree);
}

void BTreeNode::traverse() {
    int i;
    for (i = 0; i < keys.size(); ++i) {
        if (!isLeaf)
            children[i]->traverse();
        std::cout << keys[i] << " ";
    }
    if (!isLeaf)
        children[i]->traverse();
}

int BTreeNode::findKey(int k) {
    int idx = 0;
    while (idx < keys.size() && keys[idx] < k)
        ++idx;
    return idx;
}

// Insertion
void BTree::insert(int k) {
    if (!root) {
        root = new BTreeNode(minDegree, true);
        root->keys.push_back(k);
        return;
    }

    if (root->keys.size() == 2*minDegree-1) {
        BTreeNode* s = new BTreeNode(minDegree, false);
        s->children.push_back(root);
        s->splitChild(0, root);
        int i = 0;
        if (s->keys[0] < k)
            i++;
        s->children[i]->insertNonFull(k);
        root = s;
    } else {
        root->insertNonFull(k);
    }
}

void BTreeNode::insertNonFull(int k) {
    int i = keys.size() - 1;
    if (isLeaf) {
        keys.push_back(k);
        while (i >= 0 && keys[i] > k) {
            keys[i+1] = keys[i];
            i--;
        }
        keys[i+1] = k;
    } else {
        while (i >= 0 && keys[i] > k)
            i--;
        if (children[i+1]->keys.size() == 2*minDegree-1) {
            splitChild(i+1, children[i+1]);
            if (keys[i+1] < k)
                i++;
        }
        children[i+1]->insertNonFull(k);
    }
}

void BTreeNode::splitChild(int i, BTreeNode* y) {
    BTreeNode* z = new BTreeNode(y->minDegree, y->isLeaf);
    z->keys.assign(y->keys.begin()+minDegree, y->keys.end());
    if (!y->isLeaf)
        z->children.assign(y->children.begin()+minDegree, y->children.end());

    y->keys.erase(y->keys.begin()+minDegree, y->keys.end());
    if (!y->isLeaf)
        y->children.erase(y->children.begin()+minDegree, y->children.end());

    children.insert(children.begin()+i+1, z);
    keys.insert(keys.begin()+i, y->keys[minDegree-1]);
}

// Deletion
void BTreeNode::remove(int k) {
    int idx = findKey(k);

    if (idx < keys.size() && keys[idx] == k) {
        if (isLeaf)
            removeFromLeaf(idx);
        else
            removeFromNonLeaf(idx);
    } else {
        if (isLeaf) {
            std::cout << "The key " << k << " is does not exist in the tree\n";
            return;
        }

        bool flag = ((idx == keys.size()) ? true : false);

        if (children[idx]->keys.size() < minDegree)
            fill(idx);

        if (flag && idx > keys.size())
            children[idx-1]->remove(k);
        else
            children[idx]->remove(k);
    }
}

void BTreeNode::removeFromLeaf(int idx) {
    keys.erase(keys.begin() + idx);
}

void BTreeNode::removeFromNonLeaf(int idx) {
    int k = keys[idx];

    if (children[idx]->keys.size() >= minDegree) {
        int pred = getPred(idx);
        keys[idx] = pred;
        children[idx]->remove(pred);
    } else if (children[idx+1]->keys.size() >= minDegree) {
        int succ = getSucc(idx);
        keys[idx] = succ;
        children[idx+1]->remove(succ);
    } else {
        merge(idx);
        children[idx]->remove(k);
    }
}

int BTreeNode::getPred(int idx) {
    BTreeNode* cur = children[idx];
    while (!cur->isLeaf)
        cur = cur->children[cur->keys.size()];

    return cur->keys[cur->keys.size()-1];
}

int BTreeNode::getSucc(int idx) {
    BTreeNode* cur = children[idx+1];
    while (!cur->isLeaf)
        cur = cur->children[0];

    return cur->keys[0];
}

void BTreeNode::fill(int idx) {
    if (idx != 0 && children[idx-1]->keys.size() >= minDegree)
        borrowFromPrev(idx);
    else if (idx != keys.size() && children[idx+1]->keys.size() >= minDegree)
        borrowFromNext(idx);
    else {
        if (idx != keys.size())
            merge(idx);
        else
            merge(idx-1);
    }
}

void BTreeNode::borrowFromPrev(int idx) {
    BTreeNode* child = children[idx];
    BTreeNode* sibling = children[idx-1];

    child->keys.insert(child->keys.begin(), keys[idx-1]);
    if (!child->isLeaf)
        child->children.insert(child->children.begin(), sibling->children.back());

    keys[idx-1] = sibling->keys.back();
    sibling->keys.pop_back();
     if (!sibling->isLeaf)
        sibling->children.pop_back();
}

void BTreeNode::borrowFromNext(int idx) {
    BTreeNode* child = children[idx];
    BTreeNode* sibling = children[idx+1];

    child->keys.push_back(keys[idx]);

    if (!child->isLeaf) {
        child->children.push_back(sibling->children[0]);
        sibling->children.erase(sibling->children.begin());
    }

    keys[idx] = sibling->keys[0];
    sibling->keys.erase(sibling->keys.begin());
}

void BTreeNode::merge(int idx) {
    BTreeNode* child = children[idx];
    BTreeNode* sibling = children[idx+1];

    child->keys.push_back(keys[idx]);
    for (int i = 0; i < sibling->keys.size(); ++i)
        child->keys.push_back(sibling->keys[i]);

    if (!child->isLeaf) {
        for (int i = 0; i <= sibling->keys.size(); ++i)
            child->children.push_back(sibling->children[i]);
    }

    keys.erase(keys.begin() + idx);
    children.erase(children.begin() + idx + 1);

    delete sibling;
}

int main() {
    int minDegree, choice, key;

    cout << "Enter the minimum degree for the B-tree: ";
    cin >> minDegree;

    BTree t(minDegree);

    while (true) {
        cout << "\nMenu: \n";
        cout << "1. Insert a key\n";
        cout << "2. Delete a key\n";
        cout << "3. Traverse the tree\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter key to insert: ";
            cin >> key;
            t.insert(key);
            break;

        case 2:
            cout << "Enter key to delete: ";
            cin >> key;
            t.remove(key);
            break;

        case 3:
            cout << "Traversal of the tree: ";
            t.traverse();
            cout << std::endl;
            break;

        case 4:
            return 0;

        default:
            cout << "Invalid choice, please try again.\n";
        }
    }

    return 0;
}
