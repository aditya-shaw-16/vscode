#include<iostream>
using namespace std;
class node{
    public:
        int data;
        node* next;
        node(){
            this->next = nullptr;
        }
        node(int data){
            this->data = data;
            this->next = nullptr;
        }
};

void push(node* Head, int data){
    node* newnode = new node(data);
    if(Head == nullptr){
        Head = newnode;
    }
    else{
        node* temp = Head;
        while(temp->next != nullptr){
            temp = temp->next;
        }
        temp->next = newnode;
    }
}

void printlist(node* Head){
    while(Head->next != nullptr){
        cout<<Head->data<<" -> ";
        Head = Head->next;
    }
    cout<<endl;
}

node* Midptr(node* Head){
    node* temp = Head;
    while(Head->next != nullptr && Head != nullptr){
        Head = Head->next->next;
        temp = temp->next;
    }
    return temp;
}

// node* ispallindrome(node* Head){

// }
int main(){
    node* Head = new node;
    for(int i = 0; i < 9; i++){
        push(Head,i);
    }
    printlist(Head);
    return 0;
}