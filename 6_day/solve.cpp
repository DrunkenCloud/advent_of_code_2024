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
    int x, y, i = 0, j = 0;
    cin >> choice;
    string fileName = (choice == 0) ? "input" : "trial";
    ifstream inputFile(fileName);
    if (!inputFile) {
        cerr << "Error: Could not open file." << endl;
        return 1;
    }

    vector<string> rows;
    string row;

    while (getline(inputFile, row)) {
        rows.push_back(row);
        for (j = 0; j < row.size(); j++) {
            if (row[j] == '^') {
                x = i;
                y = j;
            }
        }
        i++;
    }

    vector<string> tempRows(rows.begin(), rows.end());
    pair<int, int> dirs[4] = {{-1,0}, {0,1}, {1,0}, {0,-1}};
    int dir = 0, part1 = 0, m = rows.size(), n = rows[0].size(), permX = x, permY = y;

    while (1) {
        if (rows[x][y] != 'X') part1++;
        rows[x][y] = 'X';
        int newX = x + dirs[dir].first;
        int newY = y + dirs[dir].second;
        if (newX == -1 || newY == -1 || newX == m || newY == n) break;
        if (rows[newX][newY] == '#') {
            dir = (dir+1)%4;
        } else {
            x = newX;
            y = newY;
        }
    }

    int part2 = 0;
    rows = move(tempRows);

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (rows[i][j] != '.') continue;
            int x = permX;
            int y = permY;
            dir = 0;
            unordered_set<string> done;
            rows[i][j] = '#';
            while (1) {
                string move = to_string(x) + '#' + to_string(y) + '#' + to_string(dir);
                if (done.find(move) != done.end()) break;
                done.insert(move);
                int newX = x + dirs[dir].first;
                int newY = y + dirs[dir].second;
                if (newX == -1 || newY == -1 || newX == m || newY == n) break;
                if (rows[newX][newY] == '#') {
                    dir = (dir+1)%4;
                } else {
                    x = newX;
                    y = newY;
                }
            }
            rows[i][j] = '.';
            if (x == 0 || y == 0 || x == m-1 || y == n-1) continue;
            part2++;
        }
    }
    cout << "Part1: " << part1 << endl;
    cout << "Part2: " << part2 << endl;

    return 0;
}