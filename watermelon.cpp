#include<iostream>
using namespace std;
int main(){
    int N,X,K,P;
	    cin>>N>>X>>K>>P;
	    int ans=0;
	    if(K<=X){
	        ans = P + (K*10);
	    }
	    else if(K>X){
	        ans = P + (X*10) + ((K-X)*5);
	    }
	    cout<<ans<<endl;
    return 0;
}