
#include <stdio.h>
#include "./utils/file_util.h"

void sortInt(int len, int * array){
    //冒泡
    for(int i=len-1;i>0; i--){
        int sorted = 1;
        for(int j=0; j<i; j++){
            if(array[j] > array[j+1]){
                sorted = 0;
                int a = array[j+1];
                array[j+1] = array[j];
                array[j] = a;
            }
        }
        if(sorted ==1){
            break;
        }
    }
}

int main() {
    int ** res = readIntArrayFromFile(".\\test\\input.txt");
    for(int i=1; i<=res[0][0]; i++){
        sortInt(res[0][1], res[i]);
    }
    printIntArray(res);
    writeIntArrayToFile(".\\test\\output.txt", res);
    releaseIntArray(res);
    return 0;
}


