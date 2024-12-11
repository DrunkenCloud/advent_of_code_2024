#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cstring>
#include <unordered_map>

using namespace std;

pair<long long, long long> splitNumber(long long number) {
    string numStr = to_string(number);
    int mid = numStr.length() / 2;
    long long firstHalf = stoi(numStr.substr(0, mid));
    long long secondHalf = stoi(numStr.substr(mid));
    return {firstHalf, secondHalf};
}

unordered_map<long long, long long> blink(const unordered_map<long long, long long>& stones) {
    unordered_map<long long, long long> temp;

    for (const auto& [stone, count] : stones) {
        if (stone == 0) {
            temp[1] += count;
        } else if (to_string(stone).length()%2 == 0) {
            pair<long long, long long> split_num = splitNumber(stone);
            temp[split_num.first] += count;
            temp[split_num.second] += count;
        } else {
            temp[stone*2024] += count; 
        }
    }

    return std::move(temp);
}

long long simulateBlinks(vector<long long>& input, int blinks) {
    unordered_map<long long, long long> stones;
    for (long long stone : input) {
        stones[stone]++;
    }
    for (int i = 0; i < blinks; i++) {
        stones = blink(stones);
    }

    long long totalStones = 0;
    for (const auto& [stone, count] : stones) {
        totalStones += count;
    }

    return totalStones;
}

int main() {
    int part1 = 0, part2 = 0;

    vector<long long> input1 = {2, 54, 992917, 5270417, 2514, 28561, 0, 990};
    vector<long long> input2 = {2, 54, 992917, 5270417, 2514, 28561, 0, 990};

    cout << "Part1: " << simulateBlinks(input1, 25) << endl;
    cout << "Part2: " << simulateBlinks(input2, 75) << endl;

    return 0;
}
