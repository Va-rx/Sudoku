#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QMessageBox>
#include <Qlabel>
#include "Sudoku.h"

Sudoku sudoku(Difficulty::EASY);

void addValueButton(int row, int col, QPushButton* button);
void showInstruction();
void showSolution();

const int TILE_SIZE = 50;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QWidget window;
    window.setWindowTitle("Sudoku");

    sudoku.generateSudoku();

    QGridLayout *layout = new QGridLayout(&window);

    QPushButton *buttons[9][9];
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            buttons[row][col] = new QPushButton(QString::number(sudoku.getMapValue(row, col)));
            buttons[row][col]->setFixedSize(TILE_SIZE, TILE_SIZE);
            layout->addWidget(buttons[row][col], row, col);

            if(sudoku.getMapValue(row, col) != 0) {
                buttons[row][col]->setStyleSheet("background-color: gray;");
                buttons[row][col]->setEnabled(false);
            } else {
                buttons[row][col]->setStyleSheet("background-color: white;");
                QObject::connect(buttons[row][col], &QPushButton::clicked, [=]() {
                    addValueButton(row, col, buttons[row][col]);
                });
            }
        }
    }


    QPushButton *instructionButton = new QPushButton("Instrukcja");
                                  layout->addWidget(instructionButton, 9, 0, 1, 9);
    QObject::connect(instructionButton, &QPushButton::clicked, showInstruction);

    QPushButton *solutionButton = new QPushButton("Podejrzyj rozwiązanie");
    layout->addWidget(solutionButton, 10, 0, 1, 9);
    QObject::connect(solutionButton, &QPushButton::clicked, showSolution);

    window.show();

    return app.exec();
}

void addValueButton(int row, int col, QPushButton* button) {
    int currentValue = sudoku.getMapValue(row, col);
    sudoku.insertNumber(((currentValue + 1) % 10), row, col);
    button->setText(QString::number(sudoku.getMapValue(row, col)));

    if (sudoku.checkUserSolution()) {
        QMessageBox::information(nullptr, "GRATULACJE!", "Sudoku zostało rozwiązane!");
    }
}

void showSolution() {
    QWidget *solutionWindow = new QWidget;
    solutionWindow->setWindowTitle("Rozwiązanie");

    QGridLayout *layout = new QGridLayout(solutionWindow);

    for(int row = 0; row < 9; row++) {
        for(int col = 0; col < 9; col++) {
            QPushButton *button = new QPushButton(QString::number(sudoku.getSolutionValue(row, col)));
            button->setFixedSize(TILE_SIZE, TILE_SIZE);
            button->setEnabled(false);
            layout->addWidget(button, row, col);
        }
    }

    solutionWindow->show();
}

void showInstruction() {
    QMessageBox::information(nullptr, "Instrukcja", "Szare pola są wygenerowane i nie można zmieniać ich wartości. Klikaj na białe pola aby zmienić ich wartość. Rozwiązań jest parę i gdy Ci się uda to wyskoczy stosowny komunikat");
}
