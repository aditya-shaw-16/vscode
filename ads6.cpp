#include <iostream>
#include <vector>
#include <algorithm>

class Node {
public:
    std::vector<int> keys;
    std::vector<Node*> children;
    
    Node(int key) {
        keys.push_back(key);
    }
};
class TwoThreeTree {
private:
    Node* root = nullptr;
    Node* split(Node*& node) {
        Node* newNode = new Node(node->keys[1]);
        newNode->keys.push_back(node->keys[2]);
        node->keys.resize(1);
        if (!node->children.empty()) {
            newNode->children.push_back(node->children[2]);
            newNode->children.push_back(node->children[3]);
            node->children.resize(2);
        }
        return newNode;
    }
    void insertRecursively(Node*& node, int key, int& midValue, Node*& newNode) {
        if (!node) {
            node = new Node(key);
            return;
        }

        if (node->children.empty()) { // Leaf node
            node->keys.push_back(key);
            std::sort(node->keys.begin(), node->keys.end());
        } else {
            int i;
            for (i = 0; i < node->keys.size(); i++) {
                if (key < node->keys[i]) {
                    break;
                }
            }

            Node* nextNode = nullptr;
            int nextMid;
            insertRecursively(node->children[i], key, nextMid, nextNode);

            if (nextNode) {
                node->keys.push_back(nextMid);
                std::sort(node->keys.begin(), node->keys.end());
                node->children.insert(node->children.begin() + i + 1, nextNode);
            }
        }

        if (node->keys.size() == 3) {
            midValue = node->keys[1];
            newNode = split(node);
        } else {
            newNode = nullptr;
        }
    }

public:
    void insert(int key) {
        Node* newNode = nullptr;
        int midValue;
        insertRecursively(root, key, midValue, newNode);

        if (newNode) {
            Node* newRoot = new Node(midValue);
            newRoot->children.push_back(root);
            newRoot->children.push_back(newNode);
            root = newRoot;
        }
    }
    void print() {
        if (!root) {
            std::cout << "Tree is empty." << std::endl;
            return;
        }
        std::vector<Node*> currentLevel = {root};
        std::vector<Node*> nextLevel;

        while (!currentLevel.empty()) {
            for (Node* node : currentLevel) {
                for (int key : node->keys) {
                    std::cout << key << " ";
                }
                for (Node* child : node->children) {
                    if (child) nextLevel.push_back(child);
                }
            }
            std::cout << std::endl;
            currentLevel = nextLevel;
            nextLevel.clear();
        }
    }
};
int main() {
    TwoThreeTree tree;
    int choice, value;
    do {
        std::cout << "1. Insert\n2. Exit\nEnter your choice: ";
        std::cin >> choice;
        switch (choice) {
            case 1:
                std::cout << "Enter value to insert: ";
                std::cin >> value;
                tree.insert(value);
                std::cout << "Inserted elements: ";
                tree.print();
                break;
            case 2:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }while(choice != 2);
    return 0;
}