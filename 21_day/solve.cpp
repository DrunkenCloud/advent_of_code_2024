#include <iostream>
#include <vector>
#include <string>
#include <climits>
#include <unordered_map>
#include <algorithm>

using namespace std;
typedef pair<int, int> Position;
unordered_map<char, Position> pad_values;
unordered_map<char, Position> move_poses;
unordered_map<string, long long> cache;

void populate_pads() {
    pad_values['7'] = {0, 0};
    pad_values['8'] = {0, 1};
    pad_values['9'] = {0, 2};
    pad_values['4'] = {1, 0};
    pad_values['5'] = {1, 1};
    pad_values['6'] = {1, 2};
    pad_values['1'] = {2, 0};
    pad_values['2'] = {2, 1};
    pad_values['3'] = {2, 2};
    pad_values['X'] = {3, 0};
    pad_values['0'] = {3, 1};
    pad_values['A'] = {3, 2};

    pad_values['x'] = {0, 0};
    pad_values['^'] = {0, 1};
    pad_values['a'] = {0, 2};
    pad_values['<'] = {1, 0};
    pad_values['v'] = {1, 1};
    pad_values['>'] = {1, 2};

    move_poses['^'] = {-1, 0};
    move_poses['v'] = {1, 0};
    move_poses['<'] = {0, -1};
    move_poses['>'] = {0, 1};
}

int get_num(const string& num) {
    int ans = 0;
    for (char c : num) {
        if (isdigit(c)) {
            ans = ans * 10 + (c - '0');
        }
    }
    return ans;
}

vector<string> movesets(const Position& start, const Position& end, const Position& gap) {
    vector<string> sequences;
    auto [sx, sy] = start;
    auto [ex, ey] = end;
    auto [gx, gy] = gap;

    int dx = ex - sx;
    int dy = ey - sy;

    string moves;
    for (int i = 0; i < abs(dx); i++) moves += (dx > 0 ? 'v' : '^');
    for (int i = 0; i < abs(dy); i++) moves += (dy > 0 ? '>' : '<');

    sort(moves.begin(), moves.end());

    do {
        int cx = sx, cy = sy;
        bool valid = true;
        for (char move : moves) {
            auto [mx, my] = move_poses[move];
            cx += mx;
            cy += my;
            if (cx == gx && cy == gy) {
                valid = false;
                break;
            }
        }
        if (valid) {
            sequences.push_back(moves + "a");
        }
    } while (next_permutation(moves.begin(), moves.end()));

    if (sequences.empty()) sequences.push_back("a");
    return sequences;
}

long long solve(const string input, const int curr_depth, const int max_depth) {
    string key = input + "," + to_string(curr_depth) + "," + to_string(max_depth);
    if (cache.find(key) != cache.end()) return cache[key];

    Position gap = (curr_depth == 0) ? pad_values['X'] : pad_values['x'];
    Position start = (curr_depth == 0) ? pad_values['A'] : pad_values['a'];

    long long total_length = 0;
    for (char c : input) {
        Position end = pad_values[c];
        vector<string> moves = movesets(start, end, gap);

        if (curr_depth >= max_depth) {
            long long shortest = LLONG_MAX;
            for (const string& move : moves) {
                shortest = min(shortest, (long long)move.size());
            }
            total_length += shortest;
        } else {
            long long min_moves = LLONG_MAX;
            for (const string& move : moves) {
                min_moves = min(min_moves, solve(move, curr_depth + 1, max_depth));
            }
            total_length += min_moves;
        }
        start = end;
    }

    return cache[key] = total_length;
}

long long getMinMoves(vector<string> codes, int depth) {
    long long result = 0;

    for (string code : codes) {
        long long temp = solve(code, 0, depth);
        long long num = get_num(code);
        result += num*temp;
    }

    return result;
}

int main() {
    vector<string> codes1 = {"029A", "980A", "179A", "456A", "379A"};
    vector<string> codes2 = {"540A", "839A", "682A", "826A", "974A"};

    populate_pads();

    long long result1 = getMinMoves(codes1, 2);
    long long result2 = getMinMoves(codes2, 2);

    cout << "Part 1 Result: " << result1 << endl;
    cout << "Part 2 Result: " << result2 << endl;
    
    result1 = getMinMoves(codes1, 25);
    result2 = getMinMoves(codes2, 25);

    cout << "Part 1 Result: " << result1 << endl;
    cout << "Part 2 Result: " << result2 << endl;

    return 0;
}
