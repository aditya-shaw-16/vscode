#include <bits/stdc++.h>
using namespace std;

class CyclomaticComplexityCalculator {
public:
    int calculate(const vector<string>& sourceCode) {
        int edges = 0;
        int nodes = 0;

        for (const string& line : sourceCode) {
            nodes++; // Count the nodes (statements or decision points)
            edges += countControlFlows(line);
        }

        int complexity = edges - nodes + 1;
        return complexity;
    }

private:
    int countControlFlows(const string& line) {
        int controlFlows = 1;

        // Simplified rules for control flow counting (you might need more complex rules)
        if (line.find("if") != string::npos || line.find("else if") != string::npos)
            controlFlows++;
        if (line.find("for") != string::npos || line.find("while") != string::npos)
            controlFlows++;
        if (line.find("case") != string::npos)
            controlFlows++;

        return controlFlows;
    }
};

int main() {
    // Example C++ source code (each line is a statement)
    ifstream inputFile("source_code.txt");

    // Check if the file was opened successfully
    if (!inputFile.is_open()) {
        cerr << "Failed to open the source_code.txt file." << endl;
        return 1;
    }

    // Read the content of the file into a vector of strings
    vector<string> sourceCode;
    string line;
    while (getline(inputFile, line)) {
        sourceCode.push_back(line);
    }

    // Close the input file
    inputFile.close();
    for(auto i:sourceCode){
        cout<<i<<endl;
    }

    CyclomaticComplexityCalculator calculator;
    int complexity = calculator.calculate(sourceCode);

    cout << "Cyclomatic Complexity: " << complexity << endl;

    return 0;
}