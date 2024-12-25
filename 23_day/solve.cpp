#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <queue>

using namespace std;

void readFile(int fd, unordered_map<string, unordered_set<string>>& map) {
    string file_name = (fd == 0) ? "trial.txt" : "input.txt";
    ifstream file(file_name);
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << file_name << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string part1, part2;

        size_t dashPos = line.find('-');
        if (dashPos != string::npos) {
            part1 = line.substr(0, dashPos);
            part2 = line.substr(dashPos + 1);


            map[part1].insert(part2);
            map[part2].insert(part1);
        } else {
            cerr << "Warning: Invalid line format in file: " << line << endl;
        }
    }

    file.close();
}

string conmbineVector(vector<string>& input) {
    sort(input.begin(), input.end());
    int n = input.size();
    string ans;
    for (int i = 0; i < n-1; i++) {
        ans += input[i] + ",";
    }
    ans += input[n-1];
    return ans;
}

void recur(unordered_set<string>& visited, unordered_map<string, unordered_set<string>>& map, 
           unordered_set<string>& ans, string curr, int depth, int n) {
    if (depth == n) {
        bool t_isthere = (curr[0] == 't');
        for (const auto& v : visited) {
            if (v[0] == 't') t_isthere = true;
            if (map[curr].find(v) == map[curr].end()) return;
        }
        if (!t_isthere) return;
        vector<string> entry(visited.begin(), visited.end());
        entry.push_back(curr);
        ans.insert(conmbineVector(entry));
        return;
    }

    visited.insert(curr);

    for (const string& s : map[curr]) {
        if (visited.find(s) == visited.end()) {
            bool safe = true;
            for (const auto& v : visited) {
                if (map[s].find(v) == map[s].end()) {
                    safe = false;
                    break;
                }
            }
            if (safe) recur(visited, map, ans, s, depth + 1, n);
        }
    }

    visited.erase(curr);
}

int process(unordered_map<string, unordered_set<string>>& map, int n) {
    unordered_set<string> visited;
    unordered_set<string> ans;

    for (const auto& it : map) {
        recur(visited, map, ans, it.first, 1, n);
    }

    return ans.size();
}

string getLargestParty(unordered_map<string, unordered_set<string>>& map) {
    vector<string> nodes;
    queue<string> q;
    for (const auto& it : map) {
        nodes.emplace_back(it.first);
    }
    int n = nodes.size();
    while (nodes.size() != 0 && map[nodes[n-1]].size() != n-1) {
        sort(nodes.begin(), nodes.end(), [&](const string& a, const string& b) {
            return map[a].size() > map[b].size();
        });
        string curr = nodes[n-1];
        nodes.pop_back();
        for (const auto& s : map[curr]) {
            map[s].erase(curr);
        }
        map.erase(curr);
        n-=1;
    }
    
    sort(nodes.begin(), nodes.end());
    return conmbineVector(nodes);
}

int main() {
    int fd;
    cout << "Enter the file (0 for trial | 1 for input): ";
    cin >> fd;

    unordered_map<string, unordered_set<string>> map;

    readFile(fd, map);
    int part1 = process(map, 3);
    string part2 = getLargestParty(map);
    
    cout << "Part1: " << part1 << endl;
    cout << "Part2: " << part2 << endl;

    return 0;
}
