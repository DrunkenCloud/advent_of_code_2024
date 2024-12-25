#include <iostream>
#include <vector>
#include <fstream>
#include <string>
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

vector<vector<int>> getPathCount(vector<string>& board) {
    int m = board.size(), n = board[0].size();
    vector<vector<int>> arr(m, vector<int>(n, INT_MAX));
    auto [ei, ej] = getPosition(board, 'E');

    if (ei == -1 || ej == -1) {
        cout << "Error: 'E' not found!" << endl;
        return arr;
    }

    queue<pair<int, int>> q;
    q.push({ei, ej});
    arr[ei][ej] = 0;

    vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        for (auto [dx, dy] : directions) {
            int nx = x + dx, ny = y + dy;

            if (nx >= 0 && nx < m && ny >= 0 && ny < n && board[nx][ny] != '#' && arr[nx][ny] > arr[x][y] + 1) {
                arr[nx][ny] = arr[x][y] + 1;
                q.push({nx, ny});
            }
        }
    }

    return arr;
}

class Solution {
public:
    const vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    int m, n;

    vector<int> getRaceConditionsTime(vector<string>& board, vector<vector<int>>& pathLength) {
        vector<int> newEndTimes;
        int m = board.size(), n = board[0].size();

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] != '#') {
                    for (auto [dx, dy] : directions) {
                        int wallX = i + dx, wallY = j + dy;
                        if (wallX < 0 || wallX >= m || wallY < 0 || wallY >= n || board[wallX][wallY] != '#') continue;

                        for (auto [fx, fy] : directions) {
                            int beyondX = wallX + fx, beyondY = wallY + fy;

                            if (beyondX < 0 || beyondX >= m || beyondY < 0 || beyondY >= n || board[beyondX][beyondY] == '#') continue;

                            int timeSaved = pathLength[i][j] - pathLength[beyondX][beyondY] - 2;
                            if (timeSaved > 0) newEndTimes.push_back(timeSaved);
                        }
                    }
                }
            }
        }

        return newEndTimes;
    }

    long long getKRaceConditionsTime(const vector<string>& board, const vector<vector<int>>& pathLength, int k) {
        if (board.empty() || pathLength.empty()) return 0;

        int m = board.size(), n = board[0].size();
        long long countCheats = 0;

        vector<pair<int, int>> directions = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == '#' || board[i][j] == 'E') continue;

                queue<pair<int, int>> q;
                vector<vector<bool>> visited(m, vector<bool>(n, false));
                q.push({i, j});
                visited[i][j] = true;

                while (!q.empty()) {
                    auto [x, y] = q.front();
                    q.pop();

                    for (auto [dx, dy] : directions) {
                        int nx = x + dx, ny = y + dy;
                        int dist = abs(nx - i) + abs(ny - j);

                        if (nx >= 0 && ny >= 0 && nx < m && ny < n && !visited[nx][ny] && dist <= k) {
                            visited[nx][ny] = true;
                            q.push({nx, ny});

                            if (board[nx][ny] == '#') continue;

                            int saving = pathLength[i][j] - (dist + pathLength[nx][ny]);
                            if (saving >= 100) countCheats++;
                        }
                    }
                }
            }
        }

        return countCheats;
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

    Solution solver;

    vector<vector<int>> pathLength = getPathCount(board);
    vector<int> savedTimes = solver.getRaceConditionsTime(board, pathLength);

    int check = 100, part1 = 0;
    for (int tim : savedTimes) {
        if (tim >= check) part1++;
    }
    cout << "Part1: " << part1 << endl;

    int part2 = solver.getKRaceConditionsTime(board, pathLength, 20);
    cout << "Part2: " << part2 << endl;

    return 0;
}
