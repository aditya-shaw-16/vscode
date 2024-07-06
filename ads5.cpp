#include <iostream>
#include <vector>

struct Interval{
    int start, end;
    Interval() : start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
};
struct TreeNode{
    Interval *interval;
    int max_end;
    TreeNode *left;
    TreeNode *right;
    TreeNode(Interval *i) : interval(i), max_end(i->end), left(nullptr), right(nullptr) {}
};
class IntervalTree{
public:
    IntervalTree() : root(nullptr) {}
    void insert(Interval i){
        root = insert(root, new Interval(i.start, i.end));
    }
    bool search(Interval i, Interval &out){
        TreeNode *node = search(root, i);
        if (node){
            out = *(node->interval);
            return true;
        }
        return false;
    }
    void preorder(){
        preorder(root);
    }
private:
    TreeNode *root;
    TreeNode *insert(TreeNode *root, Interval *i){
        if (!root)
            return new TreeNode(i);
        if (i->start < root->interval->start){
            root->left = insert(root->left, i);
        }
        else{
            root->right = insert(root->right, i);
        }
        root->max_end = std::max(root->max_end, i->end);
        return root;
    }
    TreeNode *search(TreeNode *root, Interval i){
        if (!root)
            return nullptr;
        if (root->interval->start == i.start && root->interval->end == i.end)
            return root;
        TreeNode *overlappingNode = nullptr;
        if (overlap(*(root->interval), i))
            overlappingNode = root;
        if (root->left && root->left->max_end >= i.start){
            TreeNode *leftSearch = search(root->left, i);
            if (leftSearch)
                return leftSearch;
        }
        TreeNode *rightSearch = search(root->right, i);
        if (rightSearch)
            return rightSearch;
            return overlappingNode;
    }
    bool overlap(Interval i1, Interval i2){
        return i1.start <= i2.end && i2.start <= i1.end;
    }
    void preorder(TreeNode *root){
        if (!root)
            return;
        std::cout << "[" << root->interval->start << ", " << root->interval->end << "] ";
        preorder(root->left);
        preorder(root->right);
    }
};
int main(){
    IntervalTree tree;
    int choice;
    Interval interval, result;
    while (true)
    {
        std::cout << "Choose an operation:\n";
        std::cout << "1. Insert an interval\n";
        std::cout << "2. Search for an interval\n";
        std::cout << "3. Preorder traversal\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;
        switch (choice){
        case 1:
            std::cout << "Enter interval (start end): ";
            std::cin >> interval.start >> interval.end;
            tree.insert(interval);
            break;
        case 2:
            std::cout << "Enter interval to search (start end): ";
            std::cin >> interval.start >> interval.end;
            if (tree.search(interval, result)){
                std::cout << "Interval found: [" << result.start << ", " << result.end << "]" << std::endl;
            }
            else{
                std::cout << "Interval not found." << std::endl;
            }
            break;
        case 3:
            std::cout << "Preorder Traversal: ";
            tree.preorder();
            std::cout << std::endl;
            break;
        case 4:
            return 0;

        default:
            std::cout << "Invalid choice! Try again.\n";
        }
    }

    return 0;
}
