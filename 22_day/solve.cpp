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

void readFiles(vector<long long>& nums, int f) {
    string line;
    string fd = (f == 1) ? "input.txt" : "trial.txt";
    ifstream file1(fd);
    while (getline(file1, line)) nums.push_back(stoll(line));
    file1.close();
}

void simulate_rounds(vector<long long>& nums, int n, int p, vector<vector<int>>& sellerDiffs, vector<vector<int>>& sellerPrices) {
    int m = nums.size();
    for (int i = 0; i < m; i++) {
        long long curr = nums[i];
        long long prev = curr%10;

        for (int j = 0; j < n; j++) {
            curr ^= (curr << 6);
            curr = curr % p;
            curr ^= (curr >> 5);
            curr = curr % p;
            curr ^= (curr << 11);
            curr = curr % p;

            sellerDiffs[i][j] = (curr%10) - prev;
            prev = (curr%10);
            sellerPrices[i][j] = prev;

        }

        nums[i] = curr;
    }
}


void simulate_selling(vector<vector<int>>& sellerDiffs, vector<vector<int>>& sellerPrices, int m, unordered_map<string, long long>& sequenceToProfits, int n) {
    for (int i = 0; i < m; i++) {
        unordered_map<string, int> temp;
        int cycle[4];

        for (int j = 0; j < 3; j++) {
            cycle[j] = sellerDiffs[i][j];
        }

        for (int j = 3; j < n; j++) {
            cycle[j % 4] = sellerDiffs[i][j];
            string key = to_string(cycle[(j - 3) % 4]) + "#" + to_string(cycle[(j - 2) % 4]) + "#" + to_string(cycle[(j - 1) % 4]) + "#" + to_string(cycle[j % 4]);

            if (temp.find(key) == temp.end()) {
                temp[key] = sellerPrices[i][j];
            }
        }

        for (const auto& it : temp) {
            sequenceToProfits[it.first] += it.second;
        }
    }
}


int main() {
    vector<long long> nums;
    int fd;
    cout << "Enter the file (0 for trial | 1 for input): ";
    cin >> fd;

    readFiles(nums, fd);
    vector<vector<int>> sellerDiffs(nums.size(), vector<int>(2000));
    vector<vector<int>> sellerPrices(nums.size(), vector<int>(2000));
    unordered_map<string, long long> sequenceToProfit;

    long long part1 = 0;

    simulate_rounds(nums, 2000, 16777216, sellerDiffs, sellerPrices);
    for (int num : nums) {
        part1 += num;
    }
    simulate_selling(sellerDiffs, sellerPrices, nums.size(), sequenceToProfit, 2000);
    long long part2 = 0;
    for (auto it : sequenceToProfit) {
        part2 = max(part2, it.second);
    }
    cout << "Part1: " << part1 << endl;
    cout << "Part2: " << part2 << endl;

    return 0;
}
