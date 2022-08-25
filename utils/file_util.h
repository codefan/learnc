#ifndef _FILE_UTIL_
#define _FILE_UTIL_
/**
 * 读取文本文件中的 整形数组
 * 第一行 存储 数组的行 和 列的数量
 * 从第二行开始为正式的数据
 */
int **readIntArrayFromFile(const char *fileName);

void writeIntArrayToFile(const char *fileName, int **intArray);

void printIntArray(int **intArray);

void releaseIntArray(int **intArray);

int **readIntMatrixFromFile(const char *fileName, int lines, int columns);

void printIntMatrix(int **intArray, int lines, int columns);

int **allocateMatrix(int lines, int columns);

void copyIntMatrix(int **destArray, int **sourArray, int lines, int columns);

void releaseIntMatrix(int **intMAtrix, int lines);
#endif // _FILE_UTI_