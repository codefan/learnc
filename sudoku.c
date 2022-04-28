#include <stdio.h>
#include "./utils/file_util.h"

int main() {

    int ** sudoku = readIntMatrixFromFile(".\\test\\sudoku.txt", 6, 6);
 
    int fillNum = 6;
    int hasError = 0;
    while(fillNum>0 && hasError==0){
        fillNum = 0;
        for(int i=0; i<6; i++){
            for(int j=0; j<6; j++){
                if(sudoku[i][j]==0){
                    int checkData[7] = {0,0,0,0,0,0,0};
                    for(int k=0;k<6;k++){
                        //检查行
                        checkData[sudoku[i][k]]++;
                        //检查列
                        checkData[sudoku[k][j]]++;
                    }
                    //检查区域
                    int  ar = i / 2;
                    int  ac = j / 3;
                    for(int c=0; c<3; c++){
                        for(int r=0; r<2; r++){
                            checkData[sudoku[ar*2+r][ac*3+c]]++;
                        }
                    }
                    //找到唯一可以填写的数据
                    int rc=0; int rv=0;
                    for(int k=1;k<7;k++){
                        if(checkData[k]==0){
                            rc++;
                            rv=k;
                        }
                    }
                    if(rc==1){
                        sudoku[i][j] = rv;
                        fillNum ++;
                    }

                    if(rc==0){
                        //出题错误，没有正确的解
                        hasError ++;
                    }
                }            
            }
        }
    }
    
    if(hasError>0){
        printf("出题错误，没有正确的解:\n");
    } else {
        int notSure = 0;
        for(int i=0; i<6; i++){
            for(int j=0; j<6; j++){
                if(sudoku[i][j]==0){
                    notSure ++;
                }
            }
        }
        if(notSure == 0){
            printf("找到唯一解:\n");
        } else {
            printf("不是唯一解，有%d个待确定的宫格:\n", notSure);
        }
    }
    printIntMatrix(sudoku, 6, 6);

    releaseIntMatrix(sudoku, 6);

    return 0;

}
