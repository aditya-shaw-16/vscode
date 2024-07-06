#include <iostream>
#include <vector>

using namespace std;
vector<vector<int>> sides(7, vector<int>(3, 0));
int a, b, c;
string result(int a, int b, int c, vector<vector<int>> arr){
    string ans = "Not a Triangle";
    if (a < arr[0][0] || a > arr[0][1] || b < arr[1][0] || b > arr[1][1] || c < arr[2][0] || c > arr[2][1]){
        ans = "Input values are out of range";
    }
    else if (a < b + c && b < a + c && c < a + b){
        if (a == b && b == c){
            ans = "Equilateral Triangle";
        }
        else if (a == b || b == c || a == c){
            ans = "Isosceles Triangle";
        }
        else{
            ans = "Scalene Triangle";
        }
    }
    return ans;
}
string Build_DT(){
    string str = "\nDECISION TABLE FOR TRIANGLE CLASSIFICATION PROBLEM\n";
    str = str + "----------------------------------------------------------------\n";
    str = str + "Decisions | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10| 11|\n";
    str = str + "----------------------------------------------------------------\n";
    str = str + "C1: a < b + c? | F | T | T | T | T | T | T | T | T | T | T |\n";
    str = str + "C2: b < a + c? | - | F | T | T | T | T | T | T | T | T | T |\n";
    str = str + "C3: c < a + b? | - | - | F | T | T | T | T | T | T | T | T |\n";
    str = str + "C4: a = b ?    | - | - | - | T | T | T | T | F | F | F | F |\n";
    str = str + "C5: a = c ?    | - | - | - | T | T | F | F | T | F | F | F |\n";
    str = str + "C6: b = c ?    | - | - | - | T | F | T | F | F | F | T | F |\n";
    str = str + "----------------------------------------------------------------\n";
    str = str + "Rule count |32 |16 | 8 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 |\n";
    str = str + "----------------------------------------------------------------\n";
    str = str + "A1: Not a triangle | X | X | X |   |   |   |   |   |   |   |   |\n";
    str = str + "A2: Scalene        |   |   |   |   |   |   |   |   |   |   | X |\n";
    str = str + "A3: Isosceles      |   |   |   |   |   |   | X |   | X | X |   |\n";
    str = str + "A4: Equilateral    |   |   |   | X |   |   |   |   |   |   |   |\n";
    str = str + "A5: Impossible     |   |   |   |   | X | X |   | X |   |   |   |\n";
    return str;
}

int not_triangle(int ind, vector<vector<int>> arr){
    a = arr[0][1];
    b = arr[1][2];
    c = arr[2][2];
    while (a < (b + c)){
        b = b / 2;
        c = c / 2;
    }
    sides[0][0] = a;
    sides[0][1] = b;
    sides[0][2] = c;
    ind++;
    a = arr[0][2];
    b = arr[1][1];
    c = arr[2][2];
    while (b < (a + c)){
        a = a / 2;
        c = c / 2;
    }
    sides[1][0] = a;
    sides[1][1] = b;
    sides[1][2] = c;
    ind++;
    a = arr[0][2];
    b = arr[1][2];
    c = arr[2][1];
    while (c < (a + b)){
        a = a / 2;
        b = b / 2;
    }
    sides[2][0] = a;
    sides[2][1] = b;
    sides[2][2] = c;
    ind++;
    return ind;
}

int Equilateral(int ind, vector<vector<int>> arr){
    a = arr[0][3];
    b = arr[1][3];
    c = arr[2][3];
    int min_max = arr[0][0], max_min = arr[0][1], nominal_val;
    for (int i = 0; i < 3; i++){
        if (min_max > arr[i][0])
            min_max = arr[i][0];
        if (max_min > arr[i][1])
            max_min = arr[i][1];
    }
    nominal_val = (min_max + max_min) / 2;
    sides[ind][0] = nominal_val;
    sides[ind][1] = nominal_val;
    sides[ind][2] = nominal_val;
    ind++;
    return ind;
}

int Isosceles(int ind, vector<vector<int>> arr){
    a = arr[0][3];
    b = arr[1][3];
    c = arr[2][3];
    int min_max = arr[0][0], max_min = arr[0][1], nominal_val;
    for (int i = 0; i < 3; i++){
        if (min_max > arr[i][0])
            min_max = arr[i][0];
        if (max_min > arr[i][1])
            max_min = arr[i][1];
    }
    nominal_val = (min_max + max_min) / 2;
    sides[ind][0] = arr[0][0];
    sides[ind][1] = nominal_val;
    sides[ind][2] = nominal_val;
    ind++;
    sides[ind][0] = nominal_val;
    sides[ind][1] = arr[1][0];
    sides[ind][2] = nominal_val;
    ind++;
    sides[ind][0] = nominal_val;
    sides[ind][1] = nominal_val;
    sides[ind][2] = arr[2][0];
    ind++;
    return ind;
}

int impossible(int ind){
    for (int i = 0; i < 3; i++){
        cout << ind + i << "\t?\t?\t?\tImpossible" << endl;
    }
    ind = ind + 3;
    return ind;
}

int main(){
    vector<vector<int>> arr(3, vector<int>(3, 0));
    cout << "Enter the sides of the Triangle:" << endl;
    for (int i = 0; i < 3; i++){
        cout << "Enter min and max values of side " << i + 1 << ": ";
        cin >> arr[i][0] >> arr[i][1];
        arr[i][2] = (arr[i][0] + arr[i][1]) / 2;
        arr[i][3] = arr[i][1] - arr[i][0];
    }
    cout << Build_DT() << endl;
    cout << "DECISION TABLE - TEST CASES" << endl;
    cout << "S.No\ta\tb\tc\tExpected Output" << endl;
    int ind = 0;
    ind = not_triangle(ind, arr);
    ind = Equilateral(ind, arr);
    ind = Isosceles(ind, arr);
    ind = 1;
    for (int i = 0; i < 7; i++){
        a = sides[i][0];
        b = sides[i][1];
        c = sides[i][2];
        cout << ind << "\t" << a << "\t" << b << "\t" << c << "\t" << result(a, b, c, arr) << endl;
        ind++;
    }
    ind = impossible(ind);
    cout << ind << "\t" << arr[0][1] - 1 << "\t" << arr[1][2] << "\t" << arr[2][2] + 2 << "\t" << result(arr[0][1] - 1, arr[1][2], arr[2][2] + 2, arr) << endl;
    return 0;
}
