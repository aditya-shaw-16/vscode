#include <iostream>
using namespace std;
int absolute(int a)
{
    if (a < 0)
        return (-1) * a;
    return a;
}
float absolute(float a){
    if (a < 0)
        return (-1) * a;
    return a;
}
int main(){
    char flag;
    cout << "Float or Integer? (f/i)" << endl;
    cin >> flag;
    if (flag == 'f'){
        float f;
        cin >> f;
        cout << "Float Absolute: " << absolute(f) << endl;
    }
    else if (flag == 'i'){
        int i;
        cin >> i;
        cout << "Integer Absolute: " << absolute(i) << endl;
    }
}
