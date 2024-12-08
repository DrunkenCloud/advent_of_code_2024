#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <string.h>

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
    pair<int, int> dirs[4] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    int dir = 0, part1 = 0, m = rows.size(), n = rows[0].size(), permX = x, permY = y;
    bool dp[m][n][4];

    while (true) {
        if (rows[x][y] != 'X') part1++;
        rows[x][y] = 'X';
        int newX = x + dirs[dir].first;
        int newY = y + dirs[dir].second;
        if (newX < 0 || newY < 0 || newX >= m || newY >= n) break;
        if (rows[newX][newY] == '#') {
            dir = (dir + 1) % 4;
        } else {
            x = newX;
            y = newY;
        }
    }

    int part2 = 0;
    rows[permX][permY] = '^';

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (rows[i][j] != 'X') continue;
            int x = permX;
            int y = permY;
            dir = 0;
            unordered_set<string> done;
            tempRows[i][j] = '#';
            memset(dp, false, sizeof(dp));
            int count = 0;
            while (count < m*n) {
                count++;
                int newX = x + dirs[dir].first;
                int newY = y + dirs[dir].second;
                if (newX < 0 || newY < 0 || newX >= m || newY >= n) break;
                if (tempRows[newX][newY] == '#') {
                    dir = (dir + 1) % 4;
                } else {
                    x = newX;
                    y = newY;
                }
            }
            tempRows[i][j] = '.';
            if (count < m*n) part2++;
        }
    }

    // Output results
    cout << "Part1: " << part1 << endl;
    cout << "Part2: " << part2 << endl;

    return 0;
}
