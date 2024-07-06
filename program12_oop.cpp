#include<iostream>
using namespace std;

class searchArray{
    int arr[100];
    int a;

    public:
    void create_array(){
        cout<<"enter the no. of elements u want in your array"<<endl;
        cin>>a;
        cout<<"enter your array"<<endl;
        for (int i = 0; i < a; i++)
        {
            cin>>arr[i];
        }
        
    }
    void search(int item){
        for (int i = 0; i < a; i++)
        {
            if (arr[i] == item){
                cout<<item<<"found at index"<<endl;
                return;
            }
            
        }
        cout<<item<<"not found"<<endl;
        
    }
};
int main(){
    searchArray obj;
    obj.create_array();
    obj.search(5);
}