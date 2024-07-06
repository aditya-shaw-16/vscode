#include<string>
#include<iostream>
using namespace std;
class bankInfo{
    private:             
        string name;
        string accNo;
        char accType;
        int balance;
    
    public:
        void initialise(){
            cout<<"name:- ";
            cin>>name;

            cout<<"account number: ";
            cin>>accNo;

            cout<<"account type: ";
            cin>>accType;

            cout<<"enter your balance: ";
            cin>>balance;

        }

        void deposit(int q){
            if(q<0){
                cout<<"cant deposit negative quantities";
                return;
            }balance += q;
        }

        void withdraw(int q){
            if(balance < 1000){
                cout<<"not sufficient balance"<<endl;
                return;
            } this->balance -= q;
        }

        void display(){
            cout<<"carrie's Name: "<<name<<endl;
            cout<<"Account Number: "<<accNo<<endl;
            cout<<"Account Type: "<<accType<<endl;
            cout<<"Balance: "<<balance<<endl;
        }
};

int main(){
    class bankInfo a;
    a.initialise();

    int menu = 1;
    while(menu != 0) {
        cout<<"What do you wish to do with ur account? Exit-0, Withdraw-1 deposit-2 display-3\n";
        cin>>menu;
        if(menu == 1) {
            int q; cout<<"Enter the amount to be withdrawn: ";
            cin>>q; a.withdraw(q);
        } else if(menu == 2) {
            int q; cout<<"enter the amount to be deposited?: ";
            cin>>q; a.deposit(q);
        } else if(menu == 3) a.display();
    }
}