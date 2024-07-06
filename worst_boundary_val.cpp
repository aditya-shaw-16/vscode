#include <bits/stdc++.h>
using namespace std;

void patterns(int i, vector<int>& temp,vector<vector<int>> &cases,vector<vector<int>>& ans){
    if(i==cases.size()){
        ans.push_back(temp);
        return;
    }
    for(int j = 0; j<5; j++){
        temp.push_back(cases[i][j]);
        patterns(i+1,temp,cases,ans);
        temp.pop_back();
    }
}
int main(){
    cout<<"Enter No. of variables:- ";
    int n;
    cin>>n;
    vector<pair<int,int>> Ranges;
    for(int i = 0; i<n; i++){
        cout<<"Enter Range:- ";
        int a,b;
        cin>>a>>b;
        Ranges.push_back({a,b});
    }
    vector<vector<int>> cases(n);
    for(int i = 0; i<n; i++){
        cases[i].push_back(Ranges[i].first);
        cases[i].push_back(Ranges[i].first+1);
        cases[i].push_back((Ranges[i].first+Ranges[i].second)/2);
        cases[i].push_back(Ranges[i].second-1);
        cases[i].push_back(Ranges[i].second);
    }
    vector<int> temp;
    vector<vector<int>> ans;
    patterns(0,temp,cases,ans);
    cout<<"S.No."<<" ";
    for(int i = 0; i<n; i++){
        cout<<" Variable"<<i+1<<" ";
    }
    cout<<" Output";
    cout<<endl;
    int tc = 1;
    for(auto i:ans){
        cout<<setw(5)<<tc;
        tc++;
        int maxi = INT_MIN;
        for(auto j:i){
            maxi = max(maxi,j);
            cout<<setw(11)<<j;
        }
        cout<<setw(10)<<maxi;
        cout<<endl;
    }
}
