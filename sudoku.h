#ifndef SUDOKU_H
#define SUDOKU_H

#include <random>
#include <vector>
#include <algorithm>

enum Difficulty {
    EASY = 53,
    MEDIUM = 61,
    HARD = 63,
    EXTREME = 68
};

class Sudoku {
    static constexpr int size = 9;
private:
    int map[size][size];
    int solution[size][size];

    Difficulty diff;
    int blanks;

    bool fill(int row, int col);
    void removeNumbers();
    bool isValid(int row, int col, int val);

public:
    Sudoku(Difficulty difficulty);

    void generateFullValidSudoku();
    void generateSudoku();
    void insertNumber(int num, int row, int col);
    bool checkUserSolution();

    void showMap() const;

    [[nodiscard]]int getMapValue(int i, int j) const;
    [[nodiscard]]int getSolutionValue(int i, int j) const;
    [[nodiscard]]static const int getSize();
    [[nodiscard]]int getBlanks() const;
    [[nodiscard]]Difficulty getDiff() const;
};

#endif
