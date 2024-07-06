#include <iostream>
#include <queue>
#include <unordered_map>
using namespace std;

class Node {
public:
    char data;
    unsigned freq;
    Node* left;
    Node* right;

    Node(char data, unsigned freq) : data(data), freq(freq), left(nullptr), right(nullptr) {}
};

struct Compare {
    bool operator()(Node* left, Node* right) {
        return left->freq > right->freq;
    }
};

Node* buildHuffmanTree(unordered_map<char, unsigned> freqMap) {
    priority_queue<Node*, vector<Node*>, Compare> minHeap;

    for (const auto& pair : freqMap) {
        minHeap.push(new Node(pair.first, pair.second));
    }

    while (minHeap.size() > 1) {
        Node* left = minHeap.top();
        minHeap.pop();
        Node* right = minHeap.top();
        minHeap.pop();

        Node* newNode = new Node('\0', left->freq + right->freq);
        newNode->left = left;
        newNode->right = right;
        minHeap.push(newNode);
    }

    return minHeap.top();
}

void generateCodes(Node* root, string code, unordered_map<char, string>& codes) {
    if (!root) return;

    if (!root->left && !root->right) {
        codes[root->data] = code;
    }

    generateCodes(root->left, code + "0", codes);
    generateCodes(root->right, code + "1", codes);
}

int main() {
    string text = "hello world";
    unordered_map<char, unsigned> freqMap;

    for (char c : text) {
        freqMap[c]++;
    }

    Node* root = buildHuffmanTree(freqMap);
    unordered_map<char, string> codes;
    generateCodes(root, "", codes);

    cout << "Character\tFrequency\tHuffman Code" << endl;
    for (const auto& pair : codes) {
        cout << pair.first << "\t\t" << freqMap[pair.first] << "\t\t" << pair.second << endl;
    }

    return 0;
}

 