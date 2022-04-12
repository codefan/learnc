#include "file_util.h"
#include <stdio.h>

/**
 * 读取文本文件中的 整形数组
 * 第一行 存储 数组的行 和 列的数量
 * 从第二行开始为正式的数据
 */
int ** readIntArrayFromFile(char * fileName){
    FILE* fpRead = fopen(fileName, "r");
    if (fpRead == NULL)
	{
		return NULL;
	}
    int* firstLine = (int*)malloc(sizeof(int)*2);
    fscanf(fpRead, "%d", &firstLine[0]);
    fscanf(fpRead, "%d", &firstLine[1]);
    int ** result = (int**)malloc(sizeof(int*)* (firstLine[0]+1));
    result[0] = firstLine;
    for(int i=0; i<firstLine[0]; i++){
        int * curLine = (int*)malloc(sizeof(int)*firstLine[1]);
        for(int j=0; j<firstLine[1]; j++){
            fscanf(fpRead, "%d", &curLine[j]);
        }
        result[i+1] = curLine;
    }    
    fclose(fpRead);
    return result;
}

void writeIntArrayToFile(char * fileName,int ** intArray){
    if(fileName == NULL || intArray == NULL){
        return;
    }
    FILE* fpWrite = fopen(fileName, "w");

    fprintf(fpWrite, "%d %d\n",  intArray[0][0], intArray[0][1]);

    for(int i=0; i<intArray[0][0]; i++){        
        for(int j=0; j<intArray[0][1]; j++){
            fprintf(fpWrite, "%d ", intArray[i+1][j]);
        }
        fprintf(fpWrite, "\n");
    }
    fclose(fpWrite);
}

void printIntArray(int ** intArray){
    if(intArray == NULL){
        return;
    }
    printf("%d %d\n",  intArray[0][0], intArray[0][1]);
    for(int i=0; i<intArray[0][0]; i++){        
        for(int j=0; j<intArray[0][1]; j++){
            printf("%d ", intArray[i+1][j]);
        }
        printf("\n");
    }
}

void releaseIntArray(int ** intArray){
    if(intArray == NULL){
        return;
    }
    for(int i=0; i<intArray[0][0]+1; i++){   
        free(intArray[i]);
    }
    free(intArray);
}
