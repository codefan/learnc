#include <stdio.h>
#include "./utils/file_util.h"

void sudokuSolution(int matrix, int row, int col)
{
    if (col * row != matrix || matrix > 16)
    {
        printf("输入的参数不正确！\n");
        return;
    }

    int **sudoku = readIntMatrixFromFile(".\\test\\sudoku.txt", matrix, matrix);

    int fillNum = 6;
    int hasError = 0;
    while (fillNum > 0 && hasError == 0)
    {
        fillNum = 0;
        for (int i = 0; i < matrix; i++)
        {
            for (int j = 0; j < matrix; j++)
            {
                if (sudoku[i][j] == 0)
                {
                    int checkData[20] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
                    for (int k = 0; k < matrix; k++)
                    {
                        //检查行
                        checkData[sudoku[i][k]]++;
                        //检查列
                        checkData[sudoku[k][j]]++;
                    }
                    //检查区域
                    int ar = i / row;
                    int ac = j / col;
                    for (int r = 0; r < row; r++)
                    {
                        for (int c = 0; c < col; c++)
                        {
                            checkData[sudoku[ar * row + r][ac * col + c]]++;
                        }
                    }
                    //找到唯一可以填写的数据
                    int rc = 0;
                    int rv = 0;
                    for (int k = 1; k < matrix + 1; k++)
                    {
                        if (checkData[k] == 0)
                        {
                            rc++;
                            rv = k;
                        }
                    }
                    if (rc == 1)
                    {
                        sudoku[i][j] = rv;
                        fillNum++;
                    }

                    if (rc == 0)
                    {
                        //出题错误，没有正确的解
                        hasError++;
                    }
                }
            }
        }
    }

    if (hasError > 0)
    {
        printf("出题错误，没有正确的解:\n");
    }
    else
    {
        int notSure = 0;
        for (int i = 0; i < matrix; i++)
        {
            for (int j = 0; j < matrix; j++)
            {
                if (sudoku[i][j] == 0)
                {
                    notSure++;
                }
            }
        }
        if (notSure == 0)
        {
            printf("找到唯一解:\n");
        }
        else
        {
            printf("不是唯一解，有%d个待确定的宫格:\n", notSure);
        }
    }
    printIntMatrix(sudoku, matrix, matrix);

    releaseIntMatrix(sudoku, matrix);
}

int main()
{
    sudokuSolution(9, 3, 3);
    return 0;
}
