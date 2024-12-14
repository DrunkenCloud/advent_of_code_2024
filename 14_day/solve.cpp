#include <iostream>
#include <vector>
#include <utility>
#include <fstream>
#include <sstream>
#include <thread>
#include <chrono>

using namespace std;

bool checkGrid(const vector<pair<int, int>>& positions, int width = 101, int height = 103) {
    vector<vector<bool>> grid(height, vector<bool>(width, false));

    for (const auto& pos : positions) {
        int x = pos.first;
        int y = pos.second;
        if (x >= 0 && x < width && y >= 0 && y < height) {
            grid[y][x] = true;
        }
    }

    for (int i = 0; i < height; i++) {
        int counter = 0;
        for (int j = 0; j < width; j++) {
            if (grid[i][j]) counter++;
            else counter = 0;
            if (counter >= 10) {
                return true;
            }
        }
    }

    return false;
}

void paintGrid(const vector<pair<int, int>>& positions, int width = 101, int height = 103) {
    vector<vector<bool>> grid(height, vector<bool>(width, false));

    for (const auto& pos : positions) {
        grid[pos.second][pos.first] = true;
    }

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            cout << (grid[y][x] ? "*" : ".");
        }
        cout << "\n";
    }
    cout << endl;
}

int main() {
    ifstream file("input");
    if (!file) {
        cerr << "Failed to open the file.\n";
        return 1;
    }

    vector<pair<int, int>> position;
    vector<pair<int, int>> velocity;
    string line;
    int a = 0, b = 0, c = 0, d= 0;

    while (getline(file, line)) {
        int px, py, vx, vy;
        if (sscanf(line.c_str(), "p=%d,%d v=%d,%d", &px, &py, &vx, &vy) == 4) {
            position.emplace_back(px, py);
            velocity.emplace_back(vx, vy);
        }
    }

    int time = 1;
    for (; time < 101; time++) {
        for (int i = 0; i < position.size(); i++) {
            position[i].first = (position[i].first + velocity[i].first + 101) % 101;
            position[i].second = (position[i].second + velocity[i].second + 103) % 103;
        }
        if (checkGrid(position)) {
            cout << "Part2: " << time << endl;
            paintGrid(position);
            break;
        }
    }

    for (int i = 0; i < position.size(); i++) {
        int x = position[i].first, y = position[i].second;
        if (x < 101 / 2 && y < 103 / 2) a++;
        if (x > 101 / 2 && y < 103 / 2) b++;
        if (x < 101 / 2 && y > 103 / 2) c++;
        if (x > 101 / 2 && y > 103 / 2) d++;
    }

    cout << "Part1: " << a*b*c*d <<endl;

    while (true) {
        for (int i = 0; i < position.size(); i++) {
            position[i].first = (position[i].first + velocity[i].first + 101) % 101;
            position[i].second = (position[i].second + velocity[i].second + 103) % 103;
        }

        if (checkGrid(position)) {
            cout << "Part2: " << time << endl;
            paintGrid(position);
            break;
        }

        time++;
    }

    return 0;
}
