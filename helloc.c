#include <stdio.h>
#include "./utils/math.h"
#include "./utils/file_util.h"

int main() {
    //fielachian(8);
    //printf("\r\n");
    
    int ** res = readIntArrayFromFile("./test/sudoku.txt");
    for(int i=1; i<=res[0][0]; i++){
        sortInt(res[0][1], res[i]);
    }
    printIntArray(res);
    writeIntArrayToFile("./test/output.txt", res);
    releaseIntArray(res);
    return 0;
}
