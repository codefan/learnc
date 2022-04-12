
#include <stdio.h>
#include "./utils/file_util.h"

int main() {
    int ** res = readIntArrayFromFile(".\\test\\input.txt");
    printIntArray(res);
    writeIntArrayToFile(".\\test\\output.txt", res);
    releaseIntArray(res);
    return 0;
}


