#include <iostream>
#include <vector>
#include <string>
#include <climits>

using namespace std;

void run(int regA, const vector<int>& Prog, vector<int>& Output) {
    int RegA = regA, RegB = 0, RegC = 0, IP = 0;

    while (IP < Prog.size()) {
        int instr = Prog[IP],operand = Prog[IP+1];
        int operand_value = (operand < 4) ? operand : (operand == 4 ? RegA : (operand == 5 ? RegB : RegC));

        switch (instr) {
            case 0:
                RegA >>= operand_value;
                break;
            case 1:
                RegB ^= operand;
                break;
            case 2:
                RegB = operand_value % 8;
                break;
            case 3:
                if (RegA != 0) IP = operand - 2;
                break;
            case 4:
                RegB ^= RegC;
                break;
            case 5:
                Output.push_back(operand_value % 8);
                RegB = operand_value % 8;
                break;
            case 6:
                RegB = RegA >> operand_value;
                break;
            case 7:
                RegC = RegA >> operand_value;
                break;
            default:
                cout << "Invalid instruction!" << endl;
                return;
        }

        IP += 2;
    }
}

string part1(int regA, const vector<int>& Prog) {
    vector<int> Output;
    run(regA, Prog, Output);
    string result;
    for (size_t i = 0; i < Output.size(); i++) {
        result += to_string(Output[i]);
        if (i < Output.size() - 1) result += ",";
    }
    return result;
}

long long part2(const vector<int>& prog, long long curr, int i) {
    if (i == -1) return curr;
    for (int j = 0; j < 8; j++) {
        long long RegA = (8*curr)+j, RegB = 0;

        RegB = ((RegA%8)^1);
        long long temp = (RegA >> RegB);
        RegB ^= (5 ^ temp);

        if (RegB%8 == prog[i]) {
            long long result = part2(prog, RegA, i-1);
            if (result) return result;
        }
    }
    return 0;
}

int main() {
    int regA = 46323429;
    vector<int> Prog_Vector = {2,4,1,1,7,5,1,5,4,3,0,3,5,5,3,0};

    std::cout << "Part1: " << part1(regA, Prog_Vector) << endl;
    std::cout << "Part2: " << part2(Prog_Vector, 0, Prog_Vector.size()-1) << endl;

    return 0;
}