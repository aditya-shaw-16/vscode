#include <bits/stdc++.h>
using namespace std;

int num = 1;
void check(int side1, int side2, int side3, int l, int r){
    cout << setw(3) << num << setw(10) << side1 << setw(10) << side2 << setw(10) << side3 << " ";
    num++;
    if (side1 < l || side1 > r || side2 < l || side2 > r || side3 < l || side3 > r)
        cout << "Invalid Input" << endl;
    else if (side1 + side2 <= side3 || side1 + side3 <= side2 || side2 + side3 <= side1)
        cout << "Not a " << endl;
    else{
        if (side1 == side2 && side1 == side3)
            cout << "Equilateral " << endl;
        else if (side1 == side2 || side2 == side3 || side1 == side3)
            cout << "Isosceles " << endl;
        else
            cout << "Scalene " << endl;
    }
}
int main(){
    int left, right;
    cout << "Enter value range for sides: ";
    cin >> left >> right;
    map<int, int> m;
    m[0] = (left + right) / 2;
    m[1] = left - 1;
    m[2] = right + 1;
    cout << "<----------Input Classes----------->";
    cout << "I1 = { 1 <= a <= 100, 1 <= b <= 100, 1 <= c <= 100 } (All inputs are valid)\n";
    cout << "I2 = { a < 1, 1 <= b <= 100, 1 <= c <= 100 } (a is invalid, b is valid, c is valid)\n";
    cout << "I3 = { 1 <= a <= 100, b < 1, 1 <= c <= 100 } (a is valid, b is invalid, c is valid)\n";
    cout << "I4 = { 1 <= a <= 100, 1 <= b <= 100, c < 1 } (a is valid, b is valid, c is invalid)\n";
    cout << "I5 = { a > 100, 1 <= b <= 100, 1 <= c <= 100 } (a is invalid, b is valid, c is valid)\n";
    cout << "I6 = { 1 <= a <= 100, b > 100, 1 <= c <= 100 } (a is valid, b is invalid, c is valid)\n";
    cout << "I7 = { 1 <= a <= 100, 1 <= b <= 100, c > 100 } (a is valid, b is valid, c is invalid)\n";
    cout << "I8 = { a < 1, b < 1, 1 <= c <= 100 } (a is invalid, b is invalid, c is valid)\n";
    cout << "I9 = { 1 <= a <= 100, b < 1, c < 1 } (a is valid, b is invalid, c is invalid)\n";
    cout << "I10 = { a < 1, 1 <= b <= 100, c < 1 } (a is invalid, b is valid, c is invalid)\n";
    cout << "I11 = { a > 100, b > 100, 1 <= c <= 100 } (a is invalid, b is invalid, c is valid)\n";
    cout << "I12 = { 1 <= a <= 100, b > 100, c > 100 } (a is valid, b is invalid, c is invalid)\n";
    cout << "I13 = { a > 100, 1 <= b <= 100, c > 100 } (a is invalid, b is valid, c is invalid)\n";
    cout << "I14 = { a < 1, b > 100, 1 <= c <= 100 } (a is invalid, b is invalid, c is valid)\n";
    cout << "I15 = { a > 100, b < 1, 1 <= c <= 100 } (a is invalid, b is invalid, c is valid)\n";
    cout << "I16 = { 1 <= a <= 100, b < 1, c > 100 } (a is valid, b is invalid, c is invalid)\n";
    cout << "I17 = { 1 <= a <= 100, b > 100, c < 1 } (a is valid, b is invalid, c is invalid)\n";
    cout << "I18 = { a < 1, 1 <= b <= 100, c > 100 } (a is invalid, b is valid, c is invalid)\n";
    cout << "I19 = { a > 100, 1 <= b <= 100, c < 1 } (a is invalid, b is valid, c is invalid)\n";
    cout << "I20 = { a < 1, b < 1, c < 1 } (All inputs are invalid)\n";
    cout << "I21 = { a > 100, b > 100, c > 100 } (All inputs are invalid)\n";
    cout << "I22 = { a < 1, b < 1, c > 100 } (All inputs are invalid)\n";
    cout << "I23 = { a < 1, b > 100, c < 1 } (All inputs are invalid)\n";
    cout << "I24 = { a > 100, b < 1, c < 1 } (All inputs are invalid)\n";
    cout << "I25 = { a > 100, b > 100, c < 1 } (All inputs are invalid)\n";
    cout << "I26 = { a > 100, b < 1, c > 100 } (All inputs are invalid)\n";
    cout << "I27 = { a < 1, b > 100, c > 100 } (All inputs are invalid)\n";

    cout << endl
         << "*******************Equivalence Input Class*******************" << endl;
    cout << "CaseID Side1 Side2 Side3 Output" << endl;
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            for (int k = 0; k < 3; k++){
                check(m[i], m[j], m[k], left, right);
            }
        }
    }
    cout << endl
         << "*******************Equivalence Output Class*******************" << endl;
    cout << "CaseID Side1 Side2 Side3 Output" << endl;
    cout << setw(5) << "O1" << setw(10) << 50 << setw(10) << 50 << setw(10) << 50 << " "
         << "Equilateral " << endl;
    cout << setw(5) << "O2" << setw(10) << 50 << setw(10) << 40 << setw(10) << 50 << " "
         << "Scalene " << endl;
    cout << setw(5) << "O3" << setw(10) << 30 << setw(10) << 40 << setw(10) << 50 << " "
         << "Isosceles " << endl;
    cout << setw(5) << "O4" << setw(10) << 100 << setw(10) << 50 << setw(10) << 50 << " "
         << "Invalid Triangle" << endl;

    return 0;
}
