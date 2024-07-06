#include <iostream>
using namespace std;

inline int add(int a, int b)
{
    return a + b;
}
inline int difference(int a, int b)
{
    return a - b;
}
inline int division(int a, int b)
{
    return a / b;
}
inline int product(int a, int b)
{
    return a * b;
}
inline int modul(int a, int b)
{
    return a % b;
}
int main()
{
    int flag = 'y';
    while (flag == 'y')
    {
        int a, b;

        cout << "enter two integers" << endl;
        cin >> a >> b;
        cout << "what do u want to do\n1. add\n2. subtract\n3. division\n4. multiply\n5. modulus"<<endl;
        int w;
        cin >> w;
        if (w == 1)
        {
            cout <<"sum = "<< add(a, b) << endl;
        }
        else if (w == 2)
        {
            cout <<"difference = "<< difference(a, b) << endl;
        }
        else if (w == 3)
        {
            cout <<"quotient = "<< division(a, b) << endl;
        }
        else if (w == 4)
        {
            cout <<"product = "<< product(a, b) << endl;
        }
        else if (w == 5)
        {
            cout <<"modulus = "<< modul(a, b) << endl;
        }
    }
}
