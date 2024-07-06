#include <iostream>
#include <climits>
using namespace std;
enum Color{
    RED,
    BLACK
};
class RBTreeNode{
public:
    int data;
    RBTreeNode *parent;
    RBTreeNode *left;
    RBTreeNode *right;
    Color color;
};
class RedBlackTree{
private:
    RBTreeNode *root;
    RBTreeNode *TNULL;
    void findBlackHeightUtil(RBTreeNode *node, int currentBlackHeight, int &minBlackHeight){
        if (node == TNULL){
            if (currentBlackHeight < minBlackHeight){
                minBlackHeight = currentBlackHeight;
            }
            return;
        }
        findBlackHeightUtil(node->left, currentBlackHeight + (node->color == BLACK ? 1 : 0),
                            minBlackHeight);
        findBlackHeightUtil(node->right, currentBlackHeight + (node->color == BLACK ? 1 : 0), minBlackHeight);
    }
    void inOrderTraversal(RBTreeNode *node){
        if (node == TNULL){
            return;
        }
        inOrderTraversal(node->left);
        cout << node->data << " ";
        inOrderTraversal(node->right);
    }
    void leftRotate(RBTreeNode *x){
        RBTreeNode *y = x->right;
        x->right = y->left;
        if (y->left != TNULL){
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr){
            this->root = y;
        }
        else if (x == x->parent->left){
            x->parent->left = y;
        }
        else{
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }
    void rightRotate(RBTreeNode *y){
        RBTreeNode *x = y->left;
        y->left = x->right;
        if (x->right != TNULL){
            x->right->parent = y;
        }
        x->parent = y->parent;
        if (y->parent == nullptr){
            this->root = x;
        }
        else if (y == y->parent->left){
            y->parent->left = x;
        }
        else{
            y->parent->right = x;
        }
        x->right = y;
        y->parent = x;
    }
    void fixInsert(RBTreeNode *k){
        RBTreeNode *u;
        while (k->parent->color == RED){
            if (k->parent == k->parent->parent->right){
                u = k->parent->parent->left;
                if (u->color == RED){
                    u->color = BLACK;
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    k = k->parent->parent;
                }
                else{
                    if (k == k->parent->left){
                        k = k->parent;
                        rightRotate(k);
                    }
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    leftRotate(k->parent->parent);
                }
            }
            else{
                u = k->parent->parent->right;
                if (u->color == RED){
                    u->color = BLACK;
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    k = k->parent->parent;
                }
                else{
                    if (k == k->parent->right)
                    {
                        k = k->parent;
                        leftRotate(k);
                    }
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    rightRotate(k->parent->parent);
                }
            }
            if (k == root){
                break;
            }
        }
        root->color = BLACK;
    }
    void insertNodeHelper(RBTreeNode *node){
        RBTreeNode *x = root;
        RBTreeNode *y = nullptr;
        while (x != TNULL){
            y = x;
            if (node->data < x->data){
                x = x->left;
            }
            else{
                x = x->right;
            }
        }
        node->parent = y;
        if (y == nullptr){
            root = node;
        }
        else if (node->data < y->data){
            y->left = node;
        }
        else{
            y->right = node;
        }
        if (node->parent == nullptr){
            node->color = BLACK;
        }
        else if (node->parent->parent != nullptr){
            fixInsert(node);
        }
    }

public:
    RedBlackTree(){
        TNULL = new RBTreeNode;
        TNULL->color = BLACK;
        TNULL->left = nullptr;
        TNULL->right = nullptr;
        root = TNULL;
    }
    void insertNode(int key){
        RBTreeNode *node = new RBTreeNode;
        node->parent = nullptr;
        node->data = key;
        node->left = TNULL;
        node->right = TNULL;
        node->color = RED;
        insertNodeHelper(node);
    }
    int findBlackHeight(){
        if (root == TNULL){
            return 0;
        }
        int minBlackHeight = INT_MAX;
        int currentBlackHeight = 0;
        findBlackHeightUtil(root, currentBlackHeight, minBlackHeight);
        return minBlackHeight;
    }
    void printInOrder(){
        cout << "In-Order Traversal: ";
        inOrderTraversal(root);
        cout << endl;
    }
};
int main()
{
    RedBlackTree rbt;
    rbt.insertNode(10);
    rbt.insertNode(20);
    rbt.insertNode(30);
    rbt.insertNode(40);
    rbt.insertNode(50);
    rbt.insertNode(50);
    rbt.insertNode(25);
    rbt.insertNode(70);
    rbt.insertNode(75);
    int blackHeight = rbt.findBlackHeight();
    cout << "Black Height of the Red-Black Tree: " << blackHeight << endl;
    rbt.printInOrder();
    return 0;
}