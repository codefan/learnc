#include "math.h"
#include <stdio.h>

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


/**
 * int x 最大45
 */
int fielachian(int x){
   int f1=1, f2=2;
   printf("1-%d ", f1);
   if(x==1){       
       return f1;
   } 
   printf("2-%d ", f2);
   if(x==2){
       return f2;
   }
   for(int i=2; i<x; i++){
       int f3 = f1+f2;
       printf("%d-%d ", i+1, f3);
       f1 = f2;
       f2 = f3;
   }
   return f2;
}