#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <functional>

using namespace std;

int main() {
    vector<int> column1, column2;
    unordered_map<int, int> counter;
    ifstream file("input");
    int value1, value2;

    while (file >> value1 >> value2) {
        column1.push_back(value1);
        column2.push_back(value2);
    }

    file.close();
    long long diff = 0;
    long long adiff = 0;

    sort(column1.begin(), column1.end());
    sort(column2.begin(), column2.end());
    for (int i = 0; i < column1.size(); i++) {
        if (counter.find(column2[i]) == counter.end()) {
            counter[column2[i]] = 1;
        } else {
            counter[column2[i]] += 1;
        }
        diff += abs(column1[i] - column2[i]);
    }
    for (int i = 0; i < column1.size(); i++) {
        if (counter.find(column1[i]) != counter.end()) {
            adiff += counter[column1[i]]*column1[i];
        }
    }
    cout << "Part 1: " << diff << "\n";
    cout << "Part 2: " << adiff << "\n";

    return 0;
}
