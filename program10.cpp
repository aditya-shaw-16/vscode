#include <iostream>
using namespace std;
class str
{
private:
    char s[100];

public:
    void operator=(str obj)
    {
        int idx = 0;
        while (obj.s[idx] != '\0')
        {
            s[idx] = obj.s[idx];
            idx++;
        }
        s[idx + 1] = '\0';
    }
    bool operator==(const str &obj)
    {
        int idx = 0;
        while (obj.s[idx] != '\0')
        {
            if (s[idx] != obj.s[idx])
                return false;
            idx++;
        }
        return true;
    }
    bool operator<(str obj)
    {
        int idx = 0;
        while (obj.s[idx] != '\0')
        {
            if (s[idx] > obj.s[idx])
                return false;
            idx++;
        }
        return true;
    }
    bool operator>(str obj)
    {
        int idx = 0;
        while (obj.s[idx] != '\0')
        {
            if (s[idx] < obj.s[idx])
                return false;
            idx++;
        }
        return true;
    }
    str operator+(str obj)
    {
        str curr;
        int idx = 0;
        while (s[idx] != '\0')
        {
            curr.s[idx] = s[idx];
            idx++;
        }
        int idx2 = 0;
        while (obj.s[idx2] != '\0')
        {
            curr.s[idx] = obj.s[idx2];
            idx++;
            idx2++;
        }
        return curr;
    }
    void accept_str()
    {
        cin >> s;
    }
    void display()
    {
        cout << s << endl;
    }
};
int main()
{
    str obj1, obj2;
    cout << "Enter your first string ";
    obj1.accept_str();
    cout << "Enter your second string ";
    obj2.accept_str();
    cout << "To check if first < second" << endl;
    if (obj1 < obj2)
        cout << "True" << endl;
    else
        cout << "False" << endl;
    cout << "To check if first > second" << endl;
    if (obj1 > obj2)
        cout << "True" << endl;
    else
        cout << "False" << endl;
    cout << "To check if first = second" << endl;
    if (obj1 == obj2)
        cout << "True" << endl;
    else
        cout << "False" << endl;
    cout << "Assigning second to first" << endl;
    obj1 = obj2;
    cout << "First is now: ";
    obj1.display();
    cout << "Second is now: ";
    obj2.display();
    cout << "To concatenate first and second" << endl;
    str obj3;
    obj3 = obj1 + obj2;
    obj3.display();
}
