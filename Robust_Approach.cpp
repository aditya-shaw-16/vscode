#include <bits/stdc++.h>
using namespace std;
int main(){
    cout << "Enter No. of variables:- ";
    int n;
    cin >> n;
    vector<pair<int, int>> Ranges;
    for (int i = 0; i < n; i++){
        cout << "Enter Range:- ";
        int a, b;
        cin >> a >> b;
        Ranges.push_back({a, b});
    }
    vector<vector<int>> ans;
    for (int i = 0; i < n; i++){
        vector<int> temp(n);
        for (int j = 0; j < 6; j++){
            for (int k = 0; k < n; k++){
                if (i != k){
                    temp[k] = (Ranges[k].first + Ranges[k].second) / 2;
                }
                else{
                    if (j == 0)
                        temp[k] = Ranges[i].first - 1;
                    else if (j == 1)
                        temp[k] = Ranges[i].first;
                    else if (j == 2)
                        temp[k] = Ranges[i].first + 1;
                    else if (j == 3)
                        temp[k] = Ranges[i].second - 1;
                    else if (j == 4)
                        temp[k] = Ranges[i].second;
                    else
                        temp[k] = Ranges[i].second + 1;
                }
            }
            ans.push_back(temp);
        }
    }
    vector<int> temp(n);
    for (int i = 0; i < n; i++){
        temp[i] = (Ranges[i].first + Ranges[i].second) / 2;
    }
    ans.push_back(temp);
    cout << "S.No."
         << " ";
    for (int i = 0; i < n; i++){
        cout << " Variable" << i + 1 << " ";
    }
    cout << " Output";
    cout << endl;
    int tc = 1;
    for (int i = 0; i < ans.size(); i++){
        cout << setw(5) << tc;
        tc++;
        int maxi = INT_MIN;
        for (auto j : ans[i]){
            maxi = max(maxi, j);
            cout << setw(11) << j;
        }
        if (i == 6 * n)
            cout << setw(10) << maxi;
        else if (i % (2 * n) == 0 || i % (2 * n) == ((2 * n) - 1))
            cout << " InValid";
        else
            cout << setw(10) << maxi;
        cout << endl;
    }
}
