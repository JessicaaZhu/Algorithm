//
//  zhu_yuejing_pa3_lcs.c
//  HW3
//
//  Created by yuejing zhu on 2017/11/4.
//  Copyright © 2017年 yuejing. All rights reserved.
//

#include "zhu_yuejing_pa3_lcs.h"
# define tbllen 1000


int strlength(char haystack[]){
    
    int i = 0;
    while(haystack[i] != '\0')
    {
        i++;
    }
    return i;
}

int LCS(char *arr1, char *arr2){
    int length;
    
    int m = strlength(arr1);
    int n = strlength(arr2);
    int tbl[m+1][n+1];
    for (int i = 1; i <= m; i++) {
        tbl[i][0] = 0;
    }
    for (int j = 1; j <= n; j++) {
        tbl[0][j] = 0;
    }
    
    for (int i = 1; i <= m; i++){
        for (int j = 1; j <= n; j++){
            if (arr1[i] == arr2[j]) {
                tbl[i][j] = tbl[i-1][j-1] + 1;

            } else {
                if (tbl[i-1][j] > tbl[i][j-1]) {
                    tbl[i][j] = tbl[i-1][j];
                } else {
                    tbl[i][j] = tbl[i][j-1];
                }
            }
        }
    }
   
    printf("\n");
    length = tbl[m][n];
    printf("The LSC of your arrays is %d\n",length);
    return length;
}

int main(int argc, const char * argv[]) {
    printf("please enter any array:\n");
    char arr1[tbllen]; //argv[1];
    char arr2[tbllen]; //argv[2];
    scanf("%s",arr1);
    printf("please enter any array again:\n");
    scanf("%s",arr2);
    
    
    LCS(arr1, arr2);
  
}























