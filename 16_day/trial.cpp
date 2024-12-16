#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <unordered_set>
#include <cstring>
#include <queue>
#include <functional>
#include <climits>
#include <iomanip>

using namespace std;

void readFiles(vector<string>& board, int f) {
    string line;
    string fd = (f == 1) ? "input.txt" : "trial.txt";
    ifstream file1(fd);
    while (getline(file1, line)) board.push_back(line);
    file1.close();
}

pair<int, int> getPosition(vector<string>& board, char target) {
    int m = board.size(), n = board[0].size();
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i][j] == target) return {i, j};
        }
    }
    return {-1,-1};
}

int getCheapestPath(vector<string>& board, int x, int y) {
    int m = board.size(), n = board[0].size();

    priority_queue<pair<pair<int, int>, pair<int, int>>, vector<pair<pair<int, int>, pair<int, int>>>, greater<pair<pair<int, int>, pair<int, int>>>> pq;
    vector<vector<vector<bool>>> visited(m, vector<vector<bool>>(n, vector<bool>(4, false)));
    pair<int, int> dirs[4] = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};

    pq.push({{0, 2}, {x, y}});
    int count = 0;

    while (!pq.empty()) {
        auto top = pq.top();
        pq.pop();
        auto [curr_cost, curr_dir] = top.first;
        auto [i, j] = top.second;

        if (visited[i][j][curr_dir]) continue;
        visited[i][j][curr_dir] = true;
        count++;

        if (board[i][j] == 'S') return curr_cost;

        for (int d = 0; d < 4; d++) {
            auto [dx, dy] = dirs[d];
            int new_i = i + dx, new_j = j + dy;

            if (board[new_i][new_j] != '#') {
                if (curr_dir != d) pq.push({{curr_cost + 1000, d}, {i, j}});
                else pq.push({{curr_cost + 1, d}, {new_i, new_j}});
            }
        }
    }

    return -1;
}

class Solution {
private:
    pair<int, int> dirs[4] = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};
    vector<vector<vector<bool>>> visited;
public:
    void recur(vector<string>& board, int i, int j, int m, int n, vector<vector<pair<int, int>>>& paths, vector<pair<int, int>>& path, int curr_cost, int max_cost, int curr_dir) {
        cout << i << " " << j << " " << curr_dir << endl;
        if (board[i][j] == 'S') {
            path.push_back({i, j});
            paths.push_back(path);
            return;
        }
        if (visited[i][j][curr_dir] || curr_cost >= max_cost) return;
        visited[i][j][curr_dir] = true;
        for (int d = 0; d < 4; d++) {
            auto [dx, dy] = dirs[d];
            int new_i = i + dx, new_j = j + dy;
            if (visited[new_i][new_j][0] || visited[new_i][new_j][1] || visited[new_i][new_j][2] || visited[new_i][new_j][3]) continue;

            if (board[new_i][new_j] != '#') {
                if (curr_dir != d) recur(board, i, j, m, n, paths, path, curr_cost+1000, max_cost, d);
                else {
                    path.push_back({new_i, new_j});
                    recur(board, new_i, new_j, m, n, paths, path, curr_cost+1, max_cost, d);
                    path.pop_back();
                }
            }
        }
    }
    int getCheapestPathCount(vector<string>& board, int x, int y, int max_cost) {
        vector<vector<pair<int, int>>> paths;
        vector<pair<int, int>> p = {{x, y}};
        unordered_set<string> tiles;
        int m = board.size(), n = board[0].size();
        visited = vector<vector<vector<bool>>>(m, vector<vector<bool>>(n, vector<bool>(4, false)));
        recur(board, x, y, m, n, paths, p, 0, max_cost, 2);
        for (auto& path : paths) {
            for (auto& [i, j] : path) {
                string key = to_string(i) + "#" + to_string(j);
                tiles.insert(key);
            }
        }
        return tiles.size();
    }
};

int main() {
    vector<string> board;
    int fd;
    cout << "Enter the file (0 for trial | 1 for input): ";
    cin >> fd;

    readFiles(board, fd);
    if (board.size() == 0) {
        cout << "Reading board Error!" << endl;
        return 1;
    }

    auto [x,y] = getPosition(board, 'E');
    if (x == -1 && y == -1) {
        cout << "Cant find starting point!" << endl;
        return 1;
    }
    
    Solution solver;
    int part1 = getCheapestPath(board, x, y);
    cout << "Part1: " << part1 << endl;
    cout << "Part2: " << solver.getCheapestPathCount(board, x, y, part1) << endl;

    return 0;
}
