#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

int dfs(vector<string>& board, char pos, int m, int n, int i, int j, vector<vector<bool>>& visited) {
    if (i >= m || j >= n || i < 0 || j < 0 || board[i][j] != pos) return 0;
    if (pos == '9' && !visited[i][j]) {
        visited[i][j] = true;
        return 1;
    }
    
    int count = dfs(board, pos + 1, m, n, i + 1, j, visited) +
                dfs(board, pos + 1, m, n, i - 1, j, visited) +
                dfs(board, pos + 1, m, n, i, j + 1, visited) +
                dfs(board, pos + 1, m, n, i, j - 1, visited);
    return count;
}

int dfs2(vector<string>& board, char pos, int m, int n, int i, int j) {
    if (i >= m || j >= n || i < 0 || j < 0 || board[i][j] != pos) return 0;
    if (pos == '9') {
        return 1;
    }
    
    int count = dfs2(board, pos + 1, m, n, i + 1, j) +
                dfs2(board, pos + 1, m, n, i - 1, j) +
                dfs2(board, pos + 1, m, n, i, j + 1) +
                dfs2(board, pos + 1, m, n, i, j - 1);
    return count;
}

int main() {
    ifstream file("input");
    int part1 = 0, part2 = 0;
    vector<string> lines;
    string line;
    while (getline(file, line)) {
        lines.push_back(line);
    }
    file.close();

    int m = lines.size(), n = lines[0].size();

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (lines[i][j] == '0') {
                vector<vector<bool>> visited(m, vector<bool>(n, false));
                part1 += dfs(lines, '0', m, n, i, j, visited);
                part2 += dfs2(lines, '0', m, n, i, j);
            }
        }
    }

    cout << "Part1: " << part1 << endl;
    cout << "Part2: " << part2 << endl;
    return 0;
}
