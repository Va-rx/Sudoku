#include "Sudoku.h"
#include <iostream>

Sudoku::Sudoku(Difficulty difficulty) {
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            map[i][j] = 0;
            solution[i][j] = 0;
        }
    }
    diff = difficulty;
}

void Sudoku::generateFullValidSudoku() {
    fill(0, 0);
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            solution[i][j] = map[i][j];
        }
    }
}

void Sudoku::generateSudoku() {
    generateFullValidSudoku();
    blanks = static_cast<int>(diff);
    removeNumbers();
}

bool Sudoku::fill(int row, int col) {
    if(row == size) {
        return true;
    }

    if(col == size) {
        return fill(row+1, 0);
    }

    std::vector<int> numbers(size);
    std::iota(numbers.begin(), numbers.end(), 1);
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(numbers.begin(), numbers.end(), g);

    for(int num : numbers) {
        if(isValid(row, col, num)) {
            map[row][col] = num;
            if(fill(row, col+1)) {
                return true;
            }
            map[row][col] = 0;
        }
    }

    return false;
}

bool Sudoku::isValid(int row, int col, int val) {
    for(int i = 0; i < size; i++) {
        if(map[row][i] == val || map[i][col] == val) {
            return false;
        }
    }

    int startRow = (row / 3) * 3;
    int startCol = (col / 3) * 3;

    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(map[i + startRow][j + startCol] == val) {
                return false;
            }
        }
    }

    return true;
}

void Sudoku::insertNumber(int num, int row, int col) {
    map[row][col] = num;
}

bool Sudoku::checkUserSolution() {
    bool secChance = false;

    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            if(map[i][j] == 0) {
                return false;
            }
            if(map[i][j] != solution[i][j]) {
                secChance = true;
                break;
            }
        }
    }

    if(secChance) {
        // wiersze
        for(int i = 0; i < 9; i++) {
            bool digits[10] = {false};
            for(int j = 0; j < 9; j++) {
                if(map[i][j] != 0) {
                    // czy duplikat w wierszu
                    if(digits[map[i][j]]) {
                        return false;
                    }
                    digits[map[i][j]] = true;
                }
            }
        }

        // kolumny
        for(int i = 0; i < 9; i++) {
            bool digits[10] = {false};
            for(int j = 0; j < 9; j++) {
                if(map[j][i] != 0) {
                    // czy duplikat w kolumnie
                    if(digits[map[j][i]]) {
                        return false;
                    }
                    digits[map[j][i]] = true;
                }
            }
        }

        // 3x3
        for(int i = 0; i < 9; i += 3) {
            for(int j = 0; j < 9; j += 3) {
                bool digits[10] = {false};
                for(int k = 0; k < 9; k++) {
                    int row = i + k / 3;
                    int col = j + k % 3;
                    if(map[row][col] != 0) {
                        // czy duplikat w 3x3
                        if(digits[map[row][col]]) {
                            return false;
                        }
                        digits[map[row][col]] = true;
                    }
                }
            }
        }
    }
    return true;
}

void Sudoku::removeNumbers() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::vector<std::pair<int, int>> positions;
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            positions.emplace_back(i, j);
        }
    }

    std::shuffle(positions.begin(), positions.end(), g);

    for(int i = 0; i < blanks; i++) {
        auto [row, col] = positions[i];
        map[row][col] = 0;
    }
}

const int Sudoku::getSize() {
    return size;
}

int Sudoku::getBlanks() const {
    return blanks;
}

Difficulty Sudoku::getDiff() const {
    return diff;
}

void Sudoku::showMap() const {
    for(int i = 0; i < size; i++) {
        if(i % 3 == 0) {
            std::cout << " --------------------------" << std::endl;
        }
        for(int j = 0; j < size; j++) {
            if(j % 3 == 0) {
                std::cout << " | ";
            }
            std::cout << map[i][j] << " ";
        }
        std::cout << " | " << std::endl;
    }
    std::cout << " --------------------------" << std::endl;
}

int Sudoku::getMapValue(int i, int j) const{
    return map[i][j];
}

int Sudoku::getSolutionValue(int i, int j) const{
    return solution[i][j];
}
