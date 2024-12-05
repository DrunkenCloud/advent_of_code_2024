#include <iostream>
#include <fstream>
#include <vector>
#include <functional>
#include <regex>
#include <string>

using namespace std;

int calculateMulProduct(const std::string& mulExpression) {
    std::regex regex("mul\\((\\d+),(\\d+)\\)");
    std::smatch matches;

    if (std::regex_match(mulExpression, matches, regex)) {
        int num1 = stoi(matches[1].str());
        int num2 = stoi(matches[2].str());

        return num1 * num2;
    } else {
        std::cerr << "Invalid input format" << std::endl;
        return 0;
    }
}

int main() {
    vector<int> column1, column2;
    unordered_map<int, int> counter;
    ifstream file("input");
    string row;
    bool calc = true;
    int ans2 = 0, ans1 = 0;

    while (file >> row) {
        std::regex regex("(mul\\(\\d+,\\d+\\)|do\\(\\)|don't\\(\\))");
        std::smatch matches;
        std::string::const_iterator searchStart(row.cbegin());
        
        while (std::regex_search(searchStart, row.cend(), matches, regex)) {
            if (matches[0] == "do()") calc = true;
            else if (matches[0] == "don't()") calc = false;
            else if (calc) ans2 += calculateMulProduct(matches[0]);
            else ans1 += calculateMulProduct(matches[0]); 
            searchStart = matches.suffix().first;
        }
    }

    cout << "Part1: " << ans1+ans2 << endl;
    cout << "Part2: " << ans2 << endl;

    file.close();

    return 0;
}
