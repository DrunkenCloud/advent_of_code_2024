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
    return {-1, -1};
}

pair<int, int> findPathsAndCount(vector<string>& board) {
    int m = board.size(), n = board[0].size();
    auto [startX, startY] = getPosition(board, 'S');
    auto [endX, endY] = getPosition(board, 'E');

    if (startX == -1 || startY == -1 || endX == -1 || endY == -1) {
        return {-1, -1};
    }

    priority_queue<pair<pair<int, int>, pair<int, int>>, vector<pair<pair<int, int>, pair<int, int>>>, greater<pair<pair<int, int>, pair<int, int>>>> pq;
    vector<vector<vector<bool>>> visited(m, vector<vector<bool>>(n, vector<bool>(4, false)));
    vector<vector<int>> cost(m, vector<int>(n, INT_MAX));
    vector<vector<bool>> seen(m, vector<bool>(n, false));
    pair<int, int> dirs[4] = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};

    pq.push({{0, 2}, {endX, endY}});

    while (!pq.empty()) {
        auto top = pq.top();
        pq.pop();
        auto [curr_cost, curr_dir] = top.first;
        auto [i, j] = top.second;

        if (visited[i][j][curr_dir]) continue;
        visited[i][j][curr_dir] = true;
        cost[i][j] = min(curr_cost, cost[i][j]);

        for (int d = 0; d < 4; d++) {
            auto [dx, dy] = dirs[d];
            int new_i = i + dx, new_j = j + dy;

            if (new_i >= 0 && new_j >= 0 && new_i < m && new_j < n && board[new_i][new_j] != '#') {
                if (curr_dir != d) pq.push({{curr_cost + 1000, d}, {i, j}});
                else pq.push({{curr_cost + 1, d}, {new_i, new_j}});
            }
        }
    }

    int count = 1, maxCost = cost[startX][startY];
    for (int d = 0; d < 4; d++) {
        auto [dx, dy] = dirs[d];
        int new_i = startX + dx, new_j = startY + dy;

        if (new_i >= 0 && new_j >= 0 && new_i < m && new_j < n && board[new_i][new_j] != '#') {
            pq.push({{1, d}, {new_i, new_j}});
        }
    }

    while (!pq.empty()) {
        auto top = pq.top();
        pq.pop();
        auto [curr_cost, curr_dir] = top.first;
        auto [i, j] = top.second;

        if (seen[i][j] || curr_cost + cost[i][j] > maxCost) continue;
        seen[i][j] = true;
        count++;

        for (int d = 0; d < 4; d++) {
            auto [dx, dy] = dirs[d];
            int new_i = i + dx, new_j = j + dy;

            if (new_i >= 0 && new_j >= 0 && new_i < m && new_j < n && !seen[new_i][new_j] && board[new_i][new_j] != '#') {
                if (curr_dir != d && (curr_dir & 1) != (d & 1)) {
                    pq.push({{curr_cost + 1001, d}, {new_i, new_j}});
                } else if (curr_dir != d) {
                    pq.push({{curr_cost + 2001, d}, {new_i, new_j}});
                } else {
                    pq.push({{curr_cost + 1, d}, {new_i, new_j}});
                }
            }
        }
    }

    return {cost[startX][startY], count};
}

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

    auto [part1, part2] = findPathsAndCount(board);
    cout << "Part1: " << part1 << endl;

    auto [_, count] = findPathsAndCount(board);
    cout << "Part2: " << count << endl;

    return 0;
}