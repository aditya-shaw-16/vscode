#include <iostream>
#include <unordered_map>
using namespace std;
class TrieNode{
public:
    unordered_map<char, TrieNode *> children;
    bool isEndOfWord;
    TrieNode(){
        isEndOfWord = false;
    }
};
class Trie{
public:
    TrieNode *root;
    Trie(){
        root = new TrieNode();
    }
    void insert(string word){
        TrieNode *current = root;
        for (char c : word){
            if (current->children.find(c) == current->children.end()){
                current->children[c] = new TrieNode();
            }
            current = current->children[c];
        }
        current->isEndOfWord = true;
    }
    bool searchPrefix(string prefix){
        TrieNode *current = root;
        for (char c : prefix){
            if (current->children.find(c) == current->children.end()){
                return false;
            }
            current = current->children[c];
        }
        return true;
    }
};
int main(){
    Trie trie;
    string sentence = "the quick brown fox jumps over the lazy dog";
    string wordToCheck = "dog";
    for (auto c : sentence){
        if (c == ' '){
            trie.insert(wordToCheck);
            wordToCheck = "";
        }
        else{
            wordToCheck += c;
        }
    }
    if (trie.searchPrefix(wordToCheck)){
        cout << "The word '" << wordToCheck << "' occurs as a prefix of a word in the sentence." << endl;
    }
    else{
        cout << "The word '" << wordToCheck << "' does not occur as a prefix of any word in the sentence." << endl;
    }
    return 0;
}
