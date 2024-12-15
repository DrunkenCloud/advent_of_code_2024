#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <unordered_set>
#include <cstring>
#include <queue>

using namespace std;

pair<int, int> readFiles(vector<string>& board, string& moves, int f) {
    string line;
    string fd = (f == 1) ? "input" : "trial";
    ifstream file1(fd+"_board.txt");
    while (getline(file1, line)) board.push_back(line);
    file1.close();
    
    ifstream file2(fd+"_bot_move.txt");
    while (getline(file2, line)) moves += line;
    file2.close();
    return {board.size(), board[0].size()};
}

pair<int, int> getRobotPosition(vector<string>& board, int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i][j] == '@') return {i, j};
        }
    }
    return {-1,-1};
}

int getDir(char c) {
    switch (c) {
        case '<': return 0;
        case '^': return 1;
        case '>': return 2;
        case 'v': return 3;
        default: return -1;
    }
    return -1;
}

void drawBoard(vector<string>& board) {
    for (string& b : board) {
        cout << b << endl;
    }
}

void moveBot(vector<string>& board, string& moves, int x, int y, int m, int n) {
    vector<pair<int, int>> dirs = {{0,-1}, {-1,0}, {0,1}, {1,0}};
    for (char m : moves) {
        int dir = getDir(m);
        if (dir == -1) {
            cout << "Error in reading moves file!" << endl;
            exit(1);
        }

        pair<int, int> move = dirs[dir];
        int newX = x+move.first, newY = y+move.second;
        if (newX < 0 || newX >= m || newY < 0 || newY >= n) continue;
        
        if (board[newX][newY] == '#') continue;
        if (board[newX][newY] == '.') {
            swap(board[x][y], board[newX][newY]);
            x = newX; y = newY;
            continue;
        }
        while (board[newX][newY] == 'O') {
            newX += move.first;
            newY += move.second;
        }
        if (board[newX][newY] == '#') continue;
        while (newX != x || newY != y) {
            swap(board[newX-move.first][newY-move.second], board[newX][newY]);
            newX-=move.first;
            newY-=move.second;
        }
        x += move.first;
        y += move.second;
    }
}

void moveExpandedBot(vector<string>& board, string& moves, int x, int y, int m, int n) {
    vector<pair<int, int>> dirs = {{0,-1}, {-1,0}, {0,1}, {1,0}};
    for (char m : moves) {
        int dir = getDir(m);
        if (dir == -1) {
            cout << "Error in reading moves file!" << endl;
            exit(1);
        }

        pair<int, int> move = dirs[dir];
        int newX = x + move.first, newY = y + move.second;

        if (newX < 0 || newX >= m || newY < 0 || newY >= n) continue;

        if (board[newX][newY] == '#') continue;

        if (board[newX][newY] == '.') {
            swap(board[x][y], board[newX][newY]);
            x = newX;
            y = newY;
            continue;
        }

        if ((dir & 1) == 0) {
            while (board[newX][newY] == '[' || board[newX][newY] == ']') {
                newX += move.first;
                newY += move.second;
            }
            if (board[newX][newY] == '#') continue;
            while (newX != x || newY != y) {
                swap(board[newX - move.first][newY - move.second], board[newX][newY]);
                newX -= move.first;
                newY -= move.second;
            }
            x += move.first;
            y += move.second;
        } else {
            queue<pair<int, int>> q;
            vector<pair<int, int>> blocks;
            unordered_set<string> visited;
            q.push({x, y});
            bool valid = true;

            while (!q.empty()) {
                auto [currX, currY] = q.front();
                q.pop();
                string curr = to_string(currX) + "#" + to_string(currY);
                if (visited.find(curr) != visited.end()) continue;
                visited.insert(curr);
                blocks.push_back({currX, currY});

                int checkX = currX + move.first, checkY = currY + move.second;

                if (board[checkX][checkY] == '#') {
                    valid = false;
                    break;
                }
                if (board[checkX][checkY] == '.') continue;


                q.push({checkX, checkY});
                if (board[checkX][checkY] == '[') q.push({checkX, checkY+1});
                if (board[checkX][checkY] == ']') q.push({checkX, checkY-1});
            }
            if (valid) {
                for (auto i = blocks.rbegin(); i != blocks.rend(); i++) {
                    auto [blockX, blockY] = *i;
                    swap(board[blockX][blockY], board[blockX+move.first][blockY+move.second]);
                }
                x += move.first;
                y += move.second;
            }
        }
    }
}

long long getScore(vector<string>& board, int m, int n) {
    long long score = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i][j] == 'O') score += (i*100)+j;
        }
    }
    return score;
}

long long getExpandedScore(vector<string>& board, int m, int n) {
    long long score = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i][j] == '[') score += (i*100)+j;
        }
    }
    return score;
}

vector<string> convertBoard(vector<string> board, int m, int n) {
    vector<string> newBoard;
    for (int i = 0; i < m; i++) {
        string temp = "";
        for (int j = 0; j < n; j++) {
            switch (board[i][j]) {
                case '#':
                    temp += "##";
                    break;
                case '@':
                    temp += "@.";
                    break;
                case 'O':
                    temp += "[]";
                    break;
                default:
                    temp += "..";
                    break;
            }
        }
        newBoard.push_back(temp);
    }
    return newBoard;
}

int main() {
    string moves;
    vector<string> board;
    int fd;
    cout << "Enter the file (0 for trial | 1 for input) :";
    cin >> fd;

    auto [m,n] = readFiles(board, moves, fd);
    if (m == -1 && n == -1) {
        cout << "Reading board Error!" << endl;
        return 1;
    }

    auto [x,y] = getRobotPosition(board, m, n);
    if (x == -1 && y == -1) {
        cout << "Robot not found in board!" << endl;
        return 1;
    }

    vector<string> expandedBoard = convertBoard(board, m, n);

    cout << endl;
    drawBoard(board);
    moveBot(board, moves, x, y, m, n);
    drawBoard(board);

    n *= 2;
    auto [x1,y1] = getRobotPosition(expandedBoard, m, n);
    if (x1 == -1 && y1 == -1) {
        cout << "Robot not found in board!" << endl;
        return 1;
    }
    
    cout << endl;
    drawBoard(expandedBoard);
    moveExpandedBot(expandedBoard, moves, x1, y1, m, n);
    drawBoard(expandedBoard);
    cout << endl;
    
    cout << "Part1: " << getScore(board, m, n) << endl;
    cout << "Part2: " << getExpandedScore(expandedBoard, m, n) << endl;

    return 0;
}
