#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;
int main() {
    vector<int> arr = {1, 2, 2, 3, 3, 3, 3};
    unordered_map<int, int> mp;

    for (auto i : arr) {
        mp[i]++;
        cout<<i<<endl;
    }  

    // Print the frequencies
    for (const auto &pair : mp) {
        cout << pair.first << " appears " << pair.second << " times\n";
    }

    return 0;
}

