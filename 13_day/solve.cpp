#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <utility>
#include <unordered_map>
#include <cmath>
#include <iomanip>

using namespace std;

void readFile(ifstream& file, vector<pair<pair<long long, long long>, pair<long long, long long>>>& buttons, vector<pair<long long, long long>>& prizes) {
    string line;
    while (getline(file, line)) {
        if (line.find("Button A") != string::npos) {
            pair<long long, long long> buttonA, buttonB;
            pair<long long, long long> prize;

            long long ax, ay;
            istringstream buttonAStream(line);
            buttonAStream.ignore(100, '+');
            buttonAStream >> ax;
            buttonAStream.ignore(100, '+');
            buttonAStream >> ay;
            buttonA = {ax, ay};

            getline(file, line);
            long long bx, by;
            istringstream buttonBStream(line);
            buttonBStream.ignore(100, '+');
            buttonBStream >> bx;
            buttonBStream.ignore(100, '+');
            buttonBStream >> by;
            buttonB = {bx, by};

            getline(file, line);
            long long px, py;
            istringstream prizeStream(line);
            prizeStream.ignore(100, '=');
            prizeStream >> px;
            prizeStream.ignore(100, '=');
            prizeStream >> py;
            prize = {px, py};

            buttons.emplace_back(buttonA, buttonB);
            prizes.push_back(prize);
        }
    }
}

bool hasDecimals(double n) {
    int i = static_cast<int>(n);
    return n-i > 0;
}

class Solution {
public:
    unordered_map<string, long long> memo;

    long long recurSolve(long long currX, long long currY, long long targetX, long long targetY, pair<long long, long long>& A, pair<long long, long long>& B) {
        string key = to_string(currX) + "#" + to_string(currY);

        if (memo.find(key) != memo.end()) return memo[key];

        if (currX == targetX && currY == targetY) return 0;
        if (currX > targetX || currY > targetY) return -1;

        long long result;

        if (currX + B.first <= targetX && currY + B.second <= targetY) {
            result = recurSolve(currX + B.first, currY + B.second, targetX, targetY, A, B);
            if (result >= 0) return memo[key] = result += 1;
        }

        if (currX + A.first <= targetX && currY + A.second <= targetY) {
            result = recurSolve(currX + A.first, currY + A.second, targetX, targetY, A, B);
            if (result >= 0) return memo[key] = result += 3;
        }

        return memo[key] = -1;
    }

    long long linesIntersectionBruteForceSolution(long long targetX, long long targetY, long long Ax, long long Ay, long long Bx, long long By) {
        for (long long n = 0; (n * Ax <= targetX && n * Ay <= targetY); n++) {
            long long remainingX = targetX - n * Ax;
            long long remainingY = targetY - n * Ay;

            if (remainingX % Bx == 0 && remainingY % By == 0 && remainingX/Bx == remainingY/By) {
                return n * 3 + remainingX / Bx;
            }
        }
        return 0;
    }

    long long linesIntersectionEquationSolution(long long targetX, long long targetY, long long Ax, long long Ay, long long Bx, long long By) {
        const double epsilon = 1e-2;
        double m1 = Ay*1.0/Ax;
        double m2 = By*1.0/Bx;

        double tempX = (targetY - (m2*targetX))/(m1 - m2);
        double tempY = m1*tempX;
        long long x = static_cast<long long>(tempX + epsilon);
        long long y = static_cast<long long>(tempY + epsilon);

        return (x%Ax == 0 && y%Ay == 0 && (targetX-x)%Bx == 0 && (targetY-y)%By == 0 && x < targetX && y < targetY) ? ((x*3/Ax) + (targetX-x)/Bx) : 0;
    }
};

int main() {
    ifstream file("input");
    if (!file) {
        cerr << "Failed to open the file.\n";
        return 1;
    }

    vector<pair<pair<long long, long long>, pair<long long, long long>>> buttons;
    vector<pair<long long, long long>> prizes;
    long long part1 = 0, part2 = 0;
    readFile(file, buttons, prizes);
    Solution solver;

    for (size_t i = 0; i < buttons.size(); i++) {
        long long result = solver.linesIntersectionEquationSolution(prizes[i].first, prizes[i].second, buttons[i].first.first, buttons[i].first.second, buttons[i].second.first, buttons[i].second.second);
        part1 += result;
        result = solver.linesIntersectionEquationSolution(prizes[i].first + 10000000000000, prizes[i].second + 10000000000000, buttons[i].first.first, buttons[i].first.second, buttons[i].second.first, buttons[i].second.second);
        part2 += result;
    }

    cout << "Part1: " << part1 << endl;
    cout << "Part2: " << part2 << endl;

    return 0;
}
