#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

bool is_safe(vector<int>& row) {
    int i = 1, n = row.size(), damp = 0;
    if (n < 2) return false;
    bool increasing = row[1] > row[0];
    for (; i < n; i++) {
        int diff = row[i] - row[i-1];
        if ((increasing && (diff < 1 || diff > 3)) || 
            (!increasing && (-diff < 1 || -diff > 3))) {
            return false;
        }
    }
    return true;
}

int main() {
    ifstream file("input");

    if (!file.is_open()) {
        cerr << "Failed to open the file" << endl;
        return 1;
    }

    vector<vector<int>> data;
    string line;

    while (getline(file, line)) {
        vector<int> row;
        stringstream ss(line);
        int num;

        while (ss >> num) {
            row.push_back(num);
        }
        data.push_back(row);
    }

    file.close();

    int safe_count = 0, damp_count = 0;

    for (vector<int>& row : data) {
        if (is_safe(row)) {
            safe_count++;
        } else {
            int i = 0;
            for (; i < row.size(); i++) {
                vector<int> mod_vec = row;
                mod_vec.erase(mod_vec.begin() + i);
                if (is_safe(mod_vec)) break;
            }
            if (i != row.size()) damp_count++;
        }
    }
    cout << "Part1: " << safe_count << endl;
    cout << "Part2: " << safe_count+damp_count << endl;

    return 0;
}
