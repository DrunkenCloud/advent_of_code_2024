#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <unordered_set>
#include <cstring>

using namespace std;

void dfs1(vector<string>& garden, int i, int j, int m, int n, int& area, int& perimeter, char curr, vector<vector<bool>>& visited) {
    if (i < 0 || j < 0 || i >= m || j >= n || garden[i][j] != curr) {
        perimeter++;
        return;
    }
    if (visited[i][j]) return;
    visited[i][j] = true;
    area += 1;
    dfs1(garden, i+1, j, m, n, area, perimeter, curr, visited);
    dfs1(garden, i, j+1, m, n, area, perimeter, curr, visited);
    dfs1(garden, i-1, j, m, n, area, perimeter, curr, visited);
    dfs1(garden, i, j-1, m, n, area, perimeter, curr, visited);
}

void dfs2(vector<string>& garden, int i, int j, int m, int n, int& area, unordered_set<string>& sides, vector<vector<int>>& sides_list, vector<vector<bool>>& visited) {
    if (visited[i][j]) return;
    area += 1;
    visited[i][j] = true;
    pair<int, int> dirs[4] = {{-1,0}, {0,-1}, {1,0}, {0,1}};
    char curr = garden[i][j];
    if (i-1 < 0 || garden[i-1][j] != curr) {
        sides_list.push_back({i-1, j, 0});
        sides.insert(to_string(i-1) + "#" + to_string(j) + "L");
    } else {
        dfs2(garden, i-1, j, m, n, area, sides, sides_list, visited);
    }
    if (j-1 < 0 || garden[i][j-1] != curr) {
        sides_list.push_back({i, j-1, 1});
        sides.insert(to_string(i) + "#" + to_string(j-1) + "U");
    } else {
        dfs2(garden, i, j-1, m, n, area, sides, sides_list, visited);
    }
    if (i+1 >= m || garden[i+1][j] != curr) {
        sides_list.push_back({i+1, j, 2});
        sides.insert(to_string(i+1) + "#" + to_string(j) + "R");
    } else {
        dfs2(garden, i+1, j, m, n, area, sides, sides_list, visited);
    }
    if (j+1 >= n || garden[i][j+1] != curr) {
        sides_list.push_back({i, j+1, 3});
        sides.insert(to_string(i) + "#" + to_string(j+1) + "D");
    } else {
        dfs2(garden, i, j+1, m, n, area, sides, sides_list, visited);
    }
}

int main() {
    string fileName;
    int fd;
    cout << "Enter input file (0 for trial / 1 for input): ";
    cin >> fd;
    if (fd == 0) fileName = "trial";
    else if (fd == 1) fileName = "input";
    else return 0;
    ifstream file(fileName);
    int part1 = 0, part2 = 0;
    vector<string> lines;
    string line;
    while (getline(file, line)) {
        lines.push_back(line);
    }
    file.close();

    int m = lines.size(), n = lines[0].size();
    vector<vector<bool>> visited1(m, vector<bool>(n, false));
    vector<vector<bool>> visited2(m, vector<bool>(n, false));

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (!visited1[i][j]) {
                int area = 0, perimeter = 0;
                dfs1(lines, i, j, m, n, area, perimeter, lines[i][j], visited1);
                part1 += area*perimeter;
                area = 0;
                unordered_set<string> sides;
                vector<vector<int>> sides_list;
                dfs2(lines, i, j, m, n, area, sides, sides_list, visited2);
                int dupes = 0;
                for (vector<int>& s : sides_list) {
                    int x = s[0], y = s[1], dir = s[2];
                    string key;
                    switch (dir) {
                        case 0:
                            key = to_string(x) + "#" + to_string(y+1) + "L";
                            break;
                        case 1:
                            key = to_string(x+1) + "#" + to_string(y) + "U";
                            break;
                        case 2:
                            key = to_string(x) + "#" + to_string(y+1) + "R";
                            break;
                        case 3:
                            key = to_string(x+1) + "#" + to_string(y) + "D";
                            break;
                        default:
                            break;
                    }
                    if (sides.find(key) != sides.end()) dupes++;
                }
                part2 += area*(sides.size() - dupes);
            }
        }
    }

    cout << "Part1: " << part1 << endl;
    cout << "Part2: " << part2 << endl;
    return 0;
}
