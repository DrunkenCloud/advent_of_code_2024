#include <iostream>
#include <vector>
#include <string>

void constructChristmasTree(int height, int width) {
    int middle = width / 2;
    int maxStars = width / 2;
    int startStars = 1;

    for (int i = 0; i < height; ++i) {
        int numStars = startStars + 2 * i;
        if (numStars > maxStars) break;

        std::string row(width, '.');
        int leftIndex = middle - numStars / 2;
        int rightIndex = middle + numStars / 2;
        for (int j = leftIndex; j <= rightIndex; ++j) {
            row[j] = '*';
        }

        std::cout << row << std::endl;
    }
}

int main() {
    int height = 101;
    int width = 103;
    constructChristmasTree(height, width);
    return 0;
}
