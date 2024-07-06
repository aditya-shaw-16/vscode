#include<iostream>
using namespace std;

void zero_smaller(int &a, int &b){
    if(a<b){
        a=0;
    }
    else if(b<a){
        b=0;
    }
}

int main(){
    int a;
    cout<<"enter A-"; 
    cin>>a;
    int b;
    cout<<"enter B-";
    cin>>b;
    zero_smaller(a, b);
    cout<<a;
    cout<<b; 
}