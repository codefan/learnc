#ifndef  _FILE_UTIL_
#define _FILE_UTIL_
/**
 * 读取文本文件中的 整形数组
 * 第一行 存储 数组的行 和 列的数量
 * 从第二行开始为正式的数据
 */
int ** readIntArrayFromFile(char * fileName);

void printIntArray(int ** intArray);

void releaseIntArray(int ** intArray);

#endif // _FILE_UTIL_