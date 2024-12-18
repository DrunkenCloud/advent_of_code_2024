#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <chrono>
#include <queue>

using namespace std;
using namespace chrono;

void readFiles(vector<pair<int, int>>& board, int f) {
    string line;
    string fd = (f == 1) ? "input.txt" : "trial.txt";
    ifstream file1(fd);
    if (!file1.is_open()) {
        cout << "Failed to open file: " << fd << endl;
        return;
    }
    while (getline(file1, line)) {
        stringstream ss(line);
        int first, second;
        char comma;
        if (ss >> first >> comma >> second && comma == ',') {
            board.emplace_back(first, second);
        } else {
            cout << "Invalid line format: " << line << endl;
        }
    }
    file1.close();
}

void updateBytes(vector<vector<char>>& board, const vector<pair<int, int>>& bytes, int start, int end) {
    for (int i = start; i < end; i++) {
        auto [x, y] = bytes[i];
        board[x][y] = '#';
    }
}
void unsetBytes(vector<vector<char>>& board, const vector<pair<int, int>>& bytes, int start, int end) {
    for (int i = start; i < end; i++) {
        auto [x, y] = bytes[i];
        board[x][y] = '.';
    }
}

int getShortestPath(vector<vector<char>>& board, int target) {
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;
    vector<vector<bool>> visited(target, vector<bool>(target, false));
    pair<int, int> dirs[4] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    pq.push({0, {0, 0}});
    while (!pq.empty()) {
        auto top = pq.top();
        pq.pop();
        int curr = top.first, x = top.second.first, y = top.second.second;
        if (visited[x][y]) continue;
        visited[x][y] = true;
        if (x == target - 1 && y == target - 1) return curr;
        for (auto dir : dirs) {
            int newX = x + dir.first, newY = y + dir.second;
            if (newX < 0 || newX >= target || newY < 0 || newY >= target || visited[newX][newY] || board[newX][newY] == '#') continue;
            pq.push({curr + 1, {newX, newY}});
        }
    }
    return -1;
}

void part2_linear(vector<vector<char>>& board, const vector<pair<int, int>>& bytes, int start, int target) {
    int n = bytes.size();
    for (int i = start; i < n; i++) {
        auto [x, y] = bytes[i];
        board[x][y] = '#';
        if (getShortestPath(board, target) == -1) {
            cout << x << "," << y << " ";
            return;
        }
    }
    cout << "Not Found!!" << endl;
}

void part2_binary(vector<vector<char>>& board, const vector<pair<int, int>>& bytes, int start, int target) {
    int left = start, right = bytes.size() - 1;
    unsetBytes(board, bytes, start, right + 1);

    while (left < right) {
        int mid = left + (right - left) / 2;
        updateBytes(board, bytes, start, mid + 1);
        int res = getShortestPath(board, target);
        if (res == -1) {
            unsetBytes(board, bytes, 0, right + 1);
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    if (left < bytes.size()) {
        cout << bytes[left].first << "," << bytes[left].second << " ";
    } else {
        cout << "Not Found!!" << endl;
    }
}

int main() {
    vector<pair<int, int>> bytes;
    int fd = 1, target;
    cout << "Enter the file (0 for trial | 1 for input): ";
    cin >> fd;
    target = (fd == 0) ? 7 : 71;

    readFiles(bytes, fd);
    if (bytes.empty()) {
        cout << "Reading bytes Error!" << endl;
        return 1;
    }

    vector<vector<char>> board(target, vector<char>(target, '.'));
    updateBytes(board, bytes, 0, (target == 7) ? 12 : 1024);
    int part1 = getShortestPath(board, target);
    cout << "Part1: " << part1 << endl;

    auto start_linear = high_resolution_clock::now();
    cout << "Part2 (Linear): ";
    part2_linear(board, bytes, (target == 7) ? 12 : 1024, target);
    auto end_linear = high_resolution_clock::now();
    cout << " (Time: " << duration_cast<milliseconds>(end_linear - start_linear).count() << " ms)" << endl;

    auto start_binary = high_resolution_clock::now();
    cout << "Part2 (Binary): ";
    part2_binary(board, bytes, 0, target);
    auto end_binary = high_resolution_clock::now();
    cout << " (Time: " << duration_cast<milliseconds>(end_binary - start_binary).count() << " ms)" << endl;

    return 0;
}
