#include <iostream>

using namespace std;

class employee // Base class
{
protected:
    int id;
    int a = 1234, b = 4321;
    string x = "ADITYA";
    string y = "SHAWIE";
    string name;
    int salary;
    string department = "";
    string work = "";

public:
    void print_data()
    {
        cout << "\nYour id is : " << id << endl;
        cout << "Your name is : " << name << endl;
        cout << "Your salary is : " << salary << endl;
        if (department == "")
        {
            cout << "Your work type is : " << work << endl;
        }
        if (work == "")
        {
            cout << "Your department is : " << department << endl;
        }
    }
};
class faculty : public employee // Derived class
{
public:
    int get_data()
    {
        cout << "Enter id : ";
        cin >> id;
        if (id == a)
        {
            cout << "Enter name : ";
            cin >> name;
            if (name == x)
            {
                cout << "Enter salary : ";
                cin >> salary;
                cout << "Enter the department : ";
                cin >> department;
            }
            else
            {
                cout << "wrong name\ntryagain!!!" << endl;
                return 0;
            }
        }
        else
        {
            cout << "wrong id\ntry again!!!" << endl;
            return 0;
        }
    }
};
class staff : public employee // Derived class
{
public:
    int get_data()
    {
        cout << "Enter id : ";
        cin >> id;
        if (id == b)
        {
            cout << "Enter name : ";
            cin >> name;
            if (name == y)
            {
                cout << "Enter salary : ";
                cin >> salary;
                cout << "Enter the work type : ";
                cin >> work;
            }
            else
            {
                cout << "wrong name\ntryagain!!!" << endl;
                return 0;
            }
        }
        else
        {
            cout << "wrong id \ntry again!!!" << endl;
            return 0;
        }
    }
};
int main()
{
    faculty f1;
    cout << "\nHi, Faculty enter the data : " << endl;
    f1.get_data();

    staff s1;
    cout << "\nHi, Staff enter the data : " << endl;
    s1.get_data();

    cout << "\nFaculty data : " << endl;
    f1.print_data();
    cout << "\nStaff data : " << endl;
    s1.print_data();

    return 0;
}