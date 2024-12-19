#include <iostream>
#include <fstream>
#include <unordered_set>
#include <vector>
#include <sstream>
#include <cctype>
#include <unordered_map>

using namespace std;


string cleanWord(const string& word) {
    string cleaned;
    for (char ch : word) {
        if (isalnum(ch)) {
            cleaned += ch;
        }
    }
    return cleaned;
}

void readFiles(unordered_set<string>& wordSet, vector<string>& wordVector, int f) {
    string line;
    string fd = (f == 1) ? "input.txt" : "trial.txt";
    ifstream file(fd);

    if (getline(file, line)) {
        istringstream iss(line);
        string word;
        while (iss >> word) {
            wordSet.insert(cleanWord(word));
        }
    }

    while (getline(file, line)) {
        istringstream iss(line);
        string word;
        while (iss >> word) {
            wordVector.push_back(cleanWord(word));
        }
    }

    file.close();
}

class Solution {
public:
    unordered_map<int, bool> memo;
    unordered_map<int, long long> cache;
    bool recur1(const unordered_set<string>& wordSet, string& word, int pos, int n) {
        if (pos == n) return true;
        
        if (memo.find(pos) != memo.end()) return memo[pos];
        for (int i = 1; i <= (n-pos); i++) {
            string curr = word.substr(pos, i);
            if (wordSet.find(curr) != wordSet.end()) {
                if (recur1(wordSet, word, pos+i, n)) return memo[pos] = true;
            }
        }
        return memo[pos] = false;
    }
    long long recur2(const unordered_set<string>& wordSet, string& word, int pos, int n) {
        if (pos == n) return 1;
        if (cache.find(pos) != cache.end()) return cache[pos];
        
        long long result = 0;
        for (int i = 1; i <= (n-pos); i++) {
            string curr = word.substr(pos, i);
            if (wordSet.find(curr) != wordSet.end()) {
                result += recur2(wordSet, word, pos+i, n);
            }
        }
        return cache[pos] = result;
    }
};

int part_1(const unordered_set<string>& wordSet, const vector<string>& wordVector) {
    Solution solver;
    int ans = 0;
    for (string word : wordVector) {
        solver.memo.clear();
        ans += solver.recur1(wordSet, word, 0, word.size());
    }
    return ans;
}

long long part_2(const unordered_set<string>& wordSet, const vector<string>& wordVector) {
    Solution solver;
    long long ans = 0;
    for (string word : wordVector) {
        solver.cache.clear();
        ans += solver.recur2(wordSet, word, 0, word.size());
    }
    return ans;
}

int main() {
    int fd = 1, target;
    cout << "Enter the file (0 for trial | 1 for input): ";
    cin >> fd;

    unordered_set<string> wordSet;
    vector<string> wordVector;

    readFiles(wordSet, wordVector, fd);

    int part1 = part_1(wordSet, wordVector);
    cout << "Part1: " << part1 << endl;
    long long part2 = part_2(wordSet, wordVector);
    cout << "Part2: " << part2 << endl;

    return 0;
}
