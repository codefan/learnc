#include <stdio.h>
#include "./utils/file_util.h"

/**
 * 填充所有可以确定的单元，一般对应初级难度的数独可以完成。
 * @param sudoku 是一个二维数组，表示数独内容， 0 表示没有确定的数就是空
 * @param matrix 数据的维度，比如6宫 9宫
 * @param row 表示宫的行数
 * @param col 表示宫的列数
 */
int fillAssuredItem(int **sudoku, int matrix, int row, int col)
{
    int fillTotal = 0; // 总共填写的数字
    int hasError = 0;
    int fillNum; //记录本次循环找到的数字
    do
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
        fillTotal = fillTotal + fillNum;
    } while (fillNum > 0 && hasError == 0);

    if (hasError > 0)
    {
        return 0 - hasError;
    }
    return fillTotal;
}

/**
 * 检查数独是否已经全部填好，还有几个空格
 * @param sudoku 是一个二维数组，表示数独内容， 0 表示没有确定的数就是空
 * @param matrix 数据的维度，比如6宫 9宫
 * @param row 表示宫的行数
 * @param col 表示宫的列数
 */
int checkNotSureItems(int **sudoku, int matrix, int row, int col)
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
    return notSure;
}

/**
 * 排除法来填充数独， 行、列、宫内三种情况
 * @param sudoku 是一个二维数组，表示数独内容， 0 表示没有确定的数就是空
 * @param matrix 数据的维度，比如6宫 9宫
 * @param row 表示宫的行数
 * @param col 表示宫的列数
 */
int inPalaceExclusion(int **sudoku, int matrix, int row, int col)
{
    int fillTotal = 0; // 总共填写的数字
    int fillNum;       //记录每次循环填写的数字
    do
    {
        fillNum = 0;
        //宫内排除
        for (int i = 0; i < col; i++)
        {
            for (int j = 0; j < row; j++)
            {
                //找到功能还没有确定的数
                int checkData[20] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
                for (int r = 0; r < row; r++)
                {
                    for (int c = 0; c < col; c++)
                    {
                        checkData[sudoku[i * row + r][j * col + c]]++;
                    }
                }
                //对每一个空缺的数字，在空格中是填，检查是否有冲突
                for (int v = 1; v < matrix + 1; v++)
                {
                    if (checkData[v] == 0)
                    {
                        int canFillSum = 0;
                        int fillRow, fillCol;
                        for (int r = 0; r < row; r++)
                        {
                            for (int c = 0; c < col; c++)
                            {
                                if (sudoku[i * row + r][j * col + c] == 0)
                                {
                                    int conflict = 0;
                                    //检查对用的列和行
                                    for (int k = 0; k < matrix; k++)
                                    {
                                        if (sudoku[k][j * col + c] == v || sudoku[i * row + r][k] == v)
                                        {
                                            conflict = 1;
                                            break;
                                        }
                                    }
                                    if (conflict == 0)
                                    {
                                        canFillSum++;
                                        fillRow = i * row + r;
                                        fillCol = j * col + c;
                                    }
                                }
                            }
                        }
                        //找到唯一可以填写的地方
                        if (canFillSum == 1)
                        {
                            sudoku[fillRow][fillCol] = v;
                            fillNum++;
                        }
                    }
                }
            }
        }
        // 行排除
        for (int i = 0; i < matrix; i++)
        {
            //找到功能还没有确定的数
            int checkData[20] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
            for (int j = 0; j < matrix; j++)
            {
                checkData[sudoku[i][j]]++;
            }

            for (int v = 1; v < matrix + 1; v++)
            {
                if (checkData[v] == 0)
                {
                    int canFillSum = 0;
                    int fillRow, fillCol;
                    for (int j = 0; j < matrix; j++)
                    {
                        if (sudoku[i][j] != 0)
                            continue;
                        int conflict = 0;
                        //检查对应列
                        for (int k = 0; k < matrix; k++)
                        {
                            if (sudoku[k][j] == v)
                            {
                                conflict = 1;
                                break;
                            }
                        }
                        if (conflict > 0)
                        {
                            continue;
                        }
                        //检查宫内
                        int ar = i / row;
                        int ac = j / col;
                        for (int r = 0; r < row; r++)
                        {
                            for (int c = 0; c < col; c++)
                            {
                                if (sudoku[ar * row + r][ac * col + c] == v)
                                {
                                    conflict = 1;
                                    break;
                                }
                            }
                            if (conflict > 0)
                            {
                                break;
                            }
                        }

                        if (conflict == 0)
                        {
                            canFillSum++;
                            fillRow = i;
                            fillCol = j;
                        }
                    }
                    //找到唯一可以填写的地方
                    if (canFillSum == 1)
                    {
                        sudoku[fillRow][fillCol] = v;
                        fillNum++;
                    }
                }
            }
        }

        // 列排除
        for (int j = 0; j < matrix; j++)
        {
            //找到功能还没有确定的数
            int checkData[20] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
            for (int i = 0; i < matrix; i++)
            {
                checkData[sudoku[i][j]]++;
            }

            for (int v = 1; v < matrix + 1; v++)
            {
                if (checkData[v] == 0)
                {
                    int canFillSum = 0;
                    int fillRow, fillCol;
                    for (int i = 0; i < matrix; i++)
                    {
                        if (sudoku[i][j] != 0)
                            continue;

                        int conflict = 0;
                        //检查对应行
                        for (int k = 0; k < matrix; k++)
                        {
                            if (sudoku[i][k] == v)
                            {
                                conflict = 1;
                                break;
                            }
                        }
                        if (conflict > 0)
                        {
                            continue;
                        }
                        //检查宫内
                        int ar = i / row;
                        int ac = j / col;
                        for (int r = 0; r < row; r++)
                        {
                            for (int c = 0; c < col; c++)
                            {
                                if (sudoku[ar * row + r][ac * col + c] == v)
                                {
                                    conflict = 1;
                                    break;
                                }
                            }
                            if (conflict > 0)
                            {
                                break;
                            }
                        }

                        if (conflict == 0)
                        {
                            canFillSum++;
                            fillRow = i;
                            fillCol = j;
                        }
                    }
                    //找到唯一可以填写的地方
                    if (canFillSum == 1)
                    {
                        sudoku[fillRow][fillCol] = v;
                        fillNum++;
                    }
                }
            }
        }

        fillTotal = fillTotal + fillNum;
    } while (fillNum > 0); //如果一轮循环一个也没有找到，则推出循环
    return fillTotal;
}

void sudokuSolution(char *filename, int matrix, int row, int col)
{
    if (col * row != matrix || matrix > 16)
    {
        printf("输入的参数不正确！\n");
        return;
    }

    int **sudoku = readIntMatrixFromFile(filename, matrix, matrix);
    int success = 0;
    int step = 0;
    int fillCount = 0;
    while (step < 2 || fillCount > 0)
    {
        if (step % 2 == 0)
        {
            fillCount = fillAssuredItem(sudoku, matrix, row, col);
            // printIntMatrix(sudoku, matrix, matrix);
        }
        else
        {
            fillCount = inPalaceExclusion(sudoku, matrix, row, col);
        }
        if (fillCount < 0)
        {
            break;
        }

        int notSure = checkNotSureItems(sudoku, matrix, row, col);
        if (notSure == 0)
        {
            success = 1;
            break;
        }

        step++;
    }
    if (success)
    {
        printf("成功找到解\n");
    }
    else
    {
        printf("没有找到解\n");
    }
    printIntMatrix(sudoku, matrix, matrix);

    releaseIntMatrix(sudoku, matrix);
}

int main()
{
    sudokuSolution(".\\test\\sudoku.txt", 9, 3, 3);
    return 0;
}
