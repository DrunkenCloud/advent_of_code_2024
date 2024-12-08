#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <string>
#include <cctype>
#include <string.h>
#include <algorithm>

using namespace std;

int getGCD(int dx, int dy) {
    if (dx < 0) dx = -dx;
    if (dy < 0) dy = -dy;
    return __gcd(dx, dy);
}

double distance(int x1, int y1, int x2, int y2) {
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

int main() {
    cout << "Enter file (0 for input, 1 for trial): ";
    int choice;
    cin >> choice;
    string fileName = (choice == 0) ? "input" : "trial";
    ifstream file(fileName);
    if (!file) {
        cerr << "Error: Could not open file." << endl;
        return 1;
    }

    int part1 = 0, part2 = 0;
    vector<string> lines;
    string line;
    while (getline(file, line)) {
        lines.push_back(line);
    }
    file.close();

    int m = lines.size();
    int n = lines[0].size();
    string antennas = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    bool dp[m][n];
    memset(dp, false, sizeof(dp));

    for (char antenna : antennas) {
        vector<pair<int, int>> points;

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (lines[i][j] == antenna) {
                    points.emplace_back(i, j);
                }
            }
        }

        if (points.size() == 0) continue;
        cout << antenna << ": ";
        for (auto& point : points) {
            cout << '[' << point.first << ", " << point.second << "], ";
        }
        cout << " :\n";
        
        if (points.size() == 1) continue;
        for (auto& point : points) {
            if (!dp[point.first][point.second]) {
                part2++;
                dp[point.first][point.second] = true;
            }
        }

        for (int i = 0; i < points.size(); i++) {
            for (int j = 0; j < points.size(); j++) {
                if (i == j) continue;
                int x1 = points[i].first, y1 = points[i].second;
                int x2 = points[j].first, y2 = points[j].second;

                int dx = x2 - x1;
                int dy = y2 - y1;
                int gcd = getGCD(dx, dy);
                dx /= gcd;
                dy /= gcd;
                
                int anti_node_x = x1 - dx;
                int anti_node_y = y1 - dy;
                while (anti_node_x >= 0 && anti_node_x < m && anti_node_y >= 0 && anti_node_y < n) {
                    if (!dp[anti_node_x][anti_node_y]) {
                        part2++;
                        dp[anti_node_x][anti_node_y] = true;
                    }
                    anti_node_x -= dx;
                    anti_node_y -= dy;
                }
                cout << "\n";
            }
        }
    }

    cout << "Part2: " << part1 << endl;
    return 0;
}