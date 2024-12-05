#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

int main() {
    cout << "Enter file (0 for input, 1 for trial): ";
    int choice;
    cin >> choice;
    string fileName = (choice == 0) ? "input" : "trial";
    ifstream inputFile(fileName);
    unordered_map<int, vector<int>> map;
    if (!inputFile) {
        cerr << "Error: Could not open file." << endl;
        return 1;
    }

    string line;
    vector<vector<int>> commaSeparatedData;

    while (getline(inputFile, line)) {
        if (line.find('|') != string::npos) {
            istringstream iss(line);
            string part;
            while (getline(iss, part, '|')) {
                int x = stoi(part);
                getline(iss, part, '|');
                int y = stoi(part);
                map[x].push_back(y);
            }
        } else if (line.find(',') != string::npos) {
            vector<int> row;
            istringstream iss(line);
            string part;
            while (getline(iss, part, ',')) {
                row.push_back(stoi(part));
            }
            commaSeparatedData.push_back(row);
        }
    }

    inputFile.close();
    int part1 = 0, part2 = 0;
    for (auto& row : commaSeparatedData) {
        unordered_set<int> done;
        bool safe = true;
        for (int val : row) {
            for (int num : map[val]) {
                if (done.find(num) != done.end()) {
                    safe = false;
                    break;
                }
            }
            done.insert(val);
        }
        if (safe) {
            part1 += row[row.size()/2];
        } else {
            while (!safe) {
                safe = true;               
                unordered_map<int, int> pos;
                for (int i = 0; i < row.size(); i++) {
                    int val = row[i];
                    for (int num : map[val]) {
                        if (pos.find(num) != pos.end()) {
                            swap(row[i], row[pos[num]]);
                            safe = false;
                            break;
                        }
                    }
                    pos[val] = i;
                    if (!safe) break;
                }
                if (safe) break;
            }
            part2 += row[row.size()/2];
        }
    }
    cout << "Part1: " << part1 << endl;
    cout << "Part2: " << part2 << endl;

    return 0;
}
