#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>

using namespace std;

vector<int> computeHeights(const vector<string>& block, bool isLock) {
    vector<int> heights(5, 0);
    for (int col = 0; col < 5; ++col) {
        if (isLock) {
            for (int row = 0; row < 6; ++row) {
                if (block[row][col] == '#') {
                    heights[col] = row + 1;
                }
            }
        } else {
            for (int row = 5; row >= 0; --row) {
                if (block[row][col] == '#') {
                    heights[col] = 5 - row;
                } else if (block[row][col] == '.') {
                    break;
                }
            }
        }
    }
    return heights;
}



void readFile(const string& filename, vector<vector<int>>& locks, vector<vector<int>>& keys) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Could not open file.");
        exit(0);
    }

    vector<string> block;
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;

        block.push_back(line);
        if (block.size() == 7) {
            char identifier = block[0][0];
            bool isLock = (identifier == '#');

            vector<string> shape(block.begin() + 1, block.end());
            vector<int> heights = computeHeights(shape, isLock);

            if (isLock) {
                locks.push_back(heights);
            } else {
                keys.push_back(heights);
            }

            block.clear();
        }
    }
    file.close();
}

long long getTotalFits(vector<vector<int>>& locks, vector<vector<int>>& keys){
    long long ans = 0;
    for (vector<int>& key : keys) {
        for (vector<int>& lock : locks) {
            bool fit = true;
            for (int i = 0; i < 5; i++) {
                if (key[i] + lock[i] > 5) {
                    fit = false;
                    break;
                }
            }
            if (fit) ans++;
        }
    }
    return ans;
}

int main() {
    vector<vector<int>> locks, keys;
    int fd = 0;
    cout << "Enter file no (0 for trial, 1 for input): ";
    cin >> fd;

    string filename = (fd == 0) ? "trial.txt" : "input.txt";
    readFile(filename, locks, keys);

    long long part1 = getTotalFits(locks, keys);
    cout << "Part1: " << part1 << endl;

    return 0;
}
