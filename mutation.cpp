#include <iostream>
#include <vector>
using namespace std;

int killed = 0;

int correct(vector<int> testCase) {
    int A = testCase[0];
    int B = testCase[1];
    int C = testCase[2];

    if (A > B)
        if (A > C)
            return A;
        else
            return C;
    else
        if (C > B)
            return C;
        else
            return B;

    return 0;
}

int M1_Code(vector<int> testCase) {
    int A = testCase[0];
    int B = testCase[1];
    int C = testCase[2];

    if (A < B)
        if (A > C)
            return A;
        else
            return C;
    else
        if (C > B)
            return C;
        else
            return B;

    return 0;
}

int M2_Code(vector<int> testCase) {
    int A = testCase[0];
    int B = testCase[1];
    int C = testCase[2];

    if (A > (B + C))
        if (A > C)
            return A;
        else
            return C;
    else
        if (C > B)
            return C;
        else
            return B;

    return 0;
}

int M3_Code(vector<int> testCase) {
    int A = testCase[0];
    int B = testCase[1];
    int C = testCase[2];

    if (A > B)
        if (A < C)
            return A;
        else
            return C;
    else
        if (C > B)
            return C;
        else
            return B;

    return 0;
}

int M4_Code(vector<int> testCase) {
    int A = testCase[0];
    int B = testCase[1];
    int C = testCase[2];

    if (A > B)
        if (A > C)
            return A;
        else
            return C;
    else
        if (C == B)
            return C;
        else
            return B;

    return 0;
}

int M5_Code(vector<int> testCase) {
    int A = testCase[0];
    int B = testCase[1];
    int C = testCase[2];

    if (A > B)
        if (A > C)
            return A;
        else
            return C;
    else
        if (C > B)
            return B;
        else
            return B;

    return 0;
}

void M1(vector<vector<int>> testCases) {
    cout << endl << endl << "---------------------------------------------------- ----   --------------------------\n";
    cout << "   Mutant 1" << endl;
    cout << "\t\t   A\tB\tC\tExpected\t   Actual" << endl;

    bool flag = false;
    for (int i = 0; i < testCases.size(); i++) {
        cout << "Test Case " << i + 1 << "   \t     " << testCases[i][0] << "\t" << testCases[i][1] << "\t" << testCases[i][2] << "\t " << correct(testCases[i]) << "\t\t" << M1_Code(testCases[i]) << endl;
        if (correct(testCases[i]) != M1_Code(testCases[i]) && flag == false) {
            killed++;
            flag = true;
        }
    }

    if (flag == true)
        cout << endl << "Mutant Killed";
    else
        cout << endl << "Mutant not Killed";
}

void M2(vector<vector<int>> testCases) {
    cout << endl << endl << "-----------------------------------------------------   --------------------------\n";
    cout << "   Mutant 2" << endl;
    cout << "\t\t   A\tB\tC\tExpected\t   Actual" << endl;

    bool flag = false;
    for (int i = 0; i < testCases.size(); i++) {
        cout << "Test Case " << i + 1 << "   \t     " << testCases[i][0] << "\t" << testCases[i][1] << "\t" << testCases[i][2] << "\t " << correct(testCases[i]) << "\t\t" << M2_Code(testCases[i]) << endl;
        if (correct(testCases[i]) != M2_Code(testCases[i]) && flag == false) {
            killed++;
            flag = true;
        }
    }

    if (flag == true)
        cout << endl << "Mutant Killed";
    else
        cout << endl << "Mutant not Killed";
}

void M3(vector<vector<int>> testCases) {
    cout << endl << endl << "-----------------------------------------------------   --------------------------\n";
    cout << "   Mutant 3" << endl;
    cout << "\t\t   A\tB\tC\tExpected\t   Actual" << endl;

    bool flag = false;
    for (int i = 0; i < testCases.size(); i++) {
        cout << "Test Case " << i + 1 << "   \t     " << testCases[i][0] << "\t" << testCases[i][1] << "\t" << testCases[i][2] << "\t " << correct(testCases[i]) << "\t\t" << M3_Code(testCases[i]) << endl;
        if (correct(testCases[i]) != M3_Code(testCases[i]) && flag == false) {
            killed++;
            flag = true;
        }
    }

    if (flag == true)
        cout << endl << "Mutant Killed";
    else
        cout << endl << "Mutant not Killed";
}

void M4(vector<vector<int>> testCases) {
    cout << endl << endl << "---------------------------------------------------- ----   --------------------------\n";
    cout << "   Mutant 4" << endl;
    cout << "\t\t   A\tB\tC\tExpected\t   Actual" << endl;

    bool flag = false;
    for (int i = 0; i < testCases.size(); i++) {
        cout << "Test Case " << i + 1 << "   \t     " << testCases[i][0] << "\t" << testCases[i][1] << "\t" << testCases[i][2] << "\t " << correct(testCases[i]) << "\t\t" << M4_Code(testCases[i]) << endl;
        if (correct(testCases[i]) != M4_Code(testCases[i]) && flag == false) {
            killed++;
            flag = true;
        }
    }

    if (flag == true)
        cout << endl << "Mutant Killed";
    else
        cout << endl << "Mutant not Killed";
}

void M5(vector<vector<int>> testCases) {
    cout << endl << endl << "-----------------------------------------------------   --------------------------\n";
    cout << "   Mutant 5" << endl;
    cout << "\t\t   A\tB\tC\tExpected\t   Actual" << endl;

    bool flag = false;
    for (int i = 0; i < testCases.size(); i++) {
        cout << "Test Case " << i + 1 << "   \t     " << testCases[i][0] << "\t" << testCases[i][1] << "\t" << testCases[i][2] << "\t " << correct(testCases[i]) << "\t\t" << M5_Code(testCases[i]) << endl;
        if (correct(testCases[i]) != M5_Code(testCases[i]) && flag == false) {
            killed++;
            flag = true;
        }
    }

    if (flag == true)
        cout << endl << "Mutant Killed";
    else
        cout << endl << "Mutant not Killed";
}

int main() {
    cout << endl << endl << "---------------------------------------------------- ----   --------------------------\n";
    cout << "   MUTATION TESTING" << endl;
    cout << "Enter number of test cases:";
    int N;
    cin >> N;
    vector<vector<int>> testCases(N, vector<int>(3, 0));
    for (int i = 0; i < N; i++) {
        cout << "Enter test case " << i + 1 << " : ";
        cin >> testCases[i][0] >> testCases[i][1] >> testCases[i][2];
    }

    M1(testCases);
    M2(testCases);
    M3(testCases);
    M4(testCases);
    M5(testCases);

    cout << endl << endl << "---------------------------------------------------- ----   --------------------------\n";
    cout << "   MUTATION SCORE" << endl;
    cout << "Total Mutants: " << 5 << endl;
    cout << "Mutants Killed: " << killed << endl;
    cout << "Mutation Score: " << killed / 5.0 << endl;

    return 0;
}