#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

void parseInput(const string& filePath, unordered_map<string, bool>& variables, vector<vector<string>>& equations) {
    ifstream file(filePath);
    string line;

    while (getline(file, line)) {
        line.erase(remove(line.begin(), line.end(), '\n'), line.end());
        line.erase(remove(line.begin(), line.end(), '\r'), line.end());

        if (line.empty()) continue;

        stringstream ss(line);
        string var1, op, var2, arrow, result;

        if (line.find("->") != string::npos) {
            ss >> var1 >> op >> var2 >> arrow >> result;
            equations.push_back({var1, op, var2, result});
        } else {
            string variable;
            bool value;
            ss >> variable >> value;
            variable.pop_back();
            variables[variable] = value;
        }
    }
    file.close();
}

void evaluateEquations(unordered_map<string, bool>& variables, vector<vector<string>>& equations) {
    int m = equations.size();

    while (m != 0) {
        for (auto it = equations.begin(); it != equations.end();) {
            string var1 = (*it)[0];
            string op = (*it)[1];
            string var2 = (*it)[2];
            string result = (*it)[3];

            if (variables.count(var1) && variables.count(var2)) {
                int val1 = variables[var1];
                int val2 = variables[var2];
                int res;

                if (op == "AND") {
                    res = val1 & val2;
                } else if (op == "OR") {
                    res = val1 | val2;
                } else if (op == "XOR") {
                    res = val1 ^ val2;
                } else {
                    cerr << "Unknown operator: " << op << endl;
                    return;
                }

                variables[result] = res;

                it = equations.erase(it);
                --m;
            } else {
                ++it;
            }
        }
    }
}

long long getZvalue(unordered_map<string, bool>& variables) {
    vector<string> values;
    long long ans = 0;
    for (const auto& [key, value] : variables) {
        if (key[0] != 'z') continue;
        values.push_back(key);
    }
    sort(values.begin(), values.end(), greater<string>());
    for (const auto& v : values) {
        ans <<= 1;
        ans += variables[v];
    }
    return ans;
}

long long getSwaps(unordered_map<string, bool>& variables) {
    long long totalSwaps = 0;
    int carry = 0;

    for (int i = 0; i <= 44; i++) {
        string xi = (i < 10) ? "x0" + to_string(i) : "x" + to_string(i);
        string yi = (i < 10) ? "y0" + to_string(i) : "y" + to_string(i);
        string zi = (i < 10) ? "z0" + to_string(i) : "z" + to_string(i);

        int x = variables[xi];
        int y = variables[yi];

        int sum = x + y + carry;

        int z = sum & 1;
        carry = sum / 2;

        if (variables[zi] != z) {
            totalSwaps++;
            cout << "Swap at " << i << endl;
        }
    }

    string z45 = "z45";
    if (variables[z45] != carry) {
        totalSwaps++;
        cout << "Swap at 45" << endl;
    }

    return totalSwaps;
}


int main() {
    int fd = 0;
    cout << "Enter file number (0 for trial / 1 for input): ";
    cin >> fd;
    
    string filePath = (fd == 0) ? "trial.txt" : "input2.txt";

    unordered_map<string, bool> variables;
    vector<vector<string>> equations;

    parseInput(filePath, variables, equations);
    evaluateEquations(variables, equations);
    
    long long part1 = getZvalue(variables);
    cout << "Part1: " << part1 << endl;
    
    long long part2 = getSwaps(variables);

    return 0;
}
