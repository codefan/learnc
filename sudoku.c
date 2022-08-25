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

/**
 * 模拟人工填写数独的思路，先找唯一值直接填写，
 * 再通过排除法找到唯一可以填写的单元格，如此往复。
 */
int analyseSolution(int **sudoku, int matrix, int row, int col)
{
    int success = 0;
    int step = 0;
    int fillCount = 0;
    while (step < 2 || fillCount > 0)
    { // step<2 确保两种方法都执行一次
        if (step % 2 == 0)
        { // 先找只有一种可能的空格，填起来
            fillCount = fillAssuredItem(sudoku, matrix, row, col);
            // printIntMatrix(sudoku, matrix, matrix);
        }
        else
        { // 再通过排除法，找到只能填写到一个单元格的数字
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
    return success == 1 ? step : -1;
}
/**
 * 回溯法，暴力求解，代码很简洁
 */
int violenceSolution(int **sudoku, int matrix, int row, int col)
{
    // 找到第一个空格
    int findSpace = 0;
    int success = 0;
    int spaceR, spaceC;
    for (int i = 0; i < matrix; i++)
    {
        for (int j = 0; j < matrix; j++)
        {
            if (sudoku[i][j] == 0)
            {
                findSpace = 1;
                spaceR = i;
                spaceC = j;
                break;
            }
        }
        if (findSpace == 1)
        {
            break;
        }
    }
    if (findSpace == 0)
    { //没有空格，填写完成
        printIntMatrix(sudoku, matrix, matrix);
        return 1;
    }

    //检查一下这个点可以填写多少个值
    int checkData[20] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    for (int k = 0; k < matrix; k++)
    {
        //检查行
        checkData[sudoku[spaceR][k]]++;
        //检查列
        checkData[sudoku[k][spaceC]]++;
    }
    //检查区域
    int ar = spaceR / row;
    int ac = spaceC / col;
    for (int r = 0; r < row; r++)
    {
        for (int c = 0; c < col; c++)
        {
            checkData[sudoku[ar * row + r][ac * col + c]]++;
        }
    }
    //找到唯一可以填写的数据
    int rc = 0;
    int rv[20] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    for (int k = 1; k < matrix + 1; k++)
    {
        if (checkData[k] == 0)
        {
            rv[rc] = k;
            rc++;
        }
    }
    if (rc == 1)
    { // 只有一种情况，填写这个空格后继续
        sudoku[spaceR][spaceC] = rv[0];
        //继续填写下一个空格
        return violenceSolution(sudoku, matrix, row, col);
    }

    if (rc == 0)
    { // 猜测的数据有问题，需要回溯
        return 0;
    }

    //复制一份当前状态
    int **copySudoku = allocateMatrix(matrix, matrix);
    copyIntMatrix(copySudoku, sudoku, matrix, matrix);
    for (int i = 0; i < rc; i++)
    {
        sudoku[spaceR][spaceC] = rv[i];
        int nRes = violenceSolution(sudoku, matrix, row, col);
        if (nRes == 1)
        {
            releaseIntMatrix(copySudoku, matrix);
            // return 1;
        }
        //恢复数独
        copyIntMatrix(sudoku, copySudoku, matrix, matrix);
    }
    releaseIntMatrix(copySudoku, matrix);
    //没有找到有效的解， 需要回溯
    return 0;
}

/**
 * 数独求解算法，从文本文件中读取数独方阵，比如 9*9， 6*6， 4*4等等 matrix
 * row、col 定义数独的宫格大小，比如 3*3 ，2*3 ，2*2 等等
 * 这个文件中有两种求解法，一种模拟人工填写数独的思路，先找唯一值直接填写，
 * 再通过排除法找到唯一可以填写的单元格，如此往复。
 * 另一中算法为回溯法，先找到第一个空格，检查可以填写的值，如果是一个直接填写
 * 如果有多个可以填写，先随便填写一个（选最小的）然后继续，如果后续冲突（找不到解）
 * 就试下一个值（回溯）。
 */
void sudokuSolution(const char *filename, int matrix, int row, int col)
{
    if (col * row != matrix || matrix > 16)
    {
        printf("输入的参数不正确！\n");
        return;
    }

    int **sudoku = readIntMatrixFromFile(filename, matrix, matrix);
    // violenceSolution analyseSolution
    int success = violenceSolution(sudoku, matrix, row, col);
    if (success > 0)
    {
        printf("成功找到解,难度系数为%d\n", success);
    }
    else
    {
        printf("没有找到解, 可能出题错误或者有多个解。\n");
    }
    //printIntMatrix(sudoku, matrix, matrix);
    releaseIntMatrix(sudoku, matrix);
}

/*
int main()
{
    sudokuSolution("./test/sudoku.txt", 6, 2, 3);
    return 0;
}
*/
