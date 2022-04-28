#include <stdio.h>
#include "./utils/file_util.h"

int main() {

    int ** sudoku = readIntMatrixFromFile(".\\test\\sudoku.txt", 6, 6);
 
    printIntMatrix(sudoku, 6, 6);

    releaseIntMatrix(sudoku, 6);
    return 0;

}
