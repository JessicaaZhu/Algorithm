//
//  zhu_yuejing_pa3_floyd.c
//  HW3
//
//  Created by yuejing zhu on 2017/11/4.
//  Copyright © 2017年 yuejing. All rights reserved.
//

#include "zhu_yuejing_pa3_floyd.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//output intermediate nodes
void path(int i,int j,int *P,int wid){
    if (P[i*wid+j]!= 0) {
        path(i, P[i*wid+j], P,wid);
        printf("V%d->",P[i*wid+j]);
        path(P[i*wid+j], j, P,wid);
    }
}

int main(){
    srand((int)time(NULL));
    int ver = (rand()%6)+5;//5-10
    int x = 0;
    int D[ver][ver];
    int P[ver][ver];
    
    //给矩阵所有项初值0
    for (int i = 0; i < ver; i++){
        for (int j = 0 ; j < ver ; j++){
            D[i][j] = 0;
            //edge1[i][j] = 0;
        }
    }
    for (int i = 0; i < ver; i++){
        for (int j = 0 ; j < ver ; j++){
            P[i][j] = 0;
        }
    }
    //给矩阵赋值，无向图
    for (int i = 0; i < ver; i++) {
        for (int j = x; j < ver; j++) {
            if (i == j) {
                D[i][j] = 0;
            }else{
                D[i][j] = rand()%10 + 1;//1-10
                D[j][i] = D[i][j];
            }
        }
        x++;
    }
    //输出undirected graph
    printf("The D0 matrix:\n");
    for (int i = 0; i < ver; i++) {
        for (int j = 0 ; j < ver ; j++)
        {
           int num = D[i][j];
            printf("%d  ",num);
        }
        printf("\n");
    }
    printf("\n");
//folyd
    int i,j,k;
    for (k = 0 ; k < ver; k++) {
        for (i = 0; i < ver; i++) {
            for (j = 0 ; j < ver ; j++) {
                if (D[i][j] > D[i][k] + D[k][j]) {
                    D[i][j] = D[i][k] + D[k][j];
                    P[i][j] = k;
                }else{
                    D[i][j] = D[i][j];
                }
            }
        }
    }
   //output matrixs
    printf("The D%d matrix is:\n",ver);
    int num = 0;
    for (i = 0; i < ver; i++) {
         for (j = 0 ; j < ver ; j++)
         {
             num = D[i][j];
             printf("%d  ",num);
         }
         printf("\n");
    }
    printf("\n");
    printf("The P matrix is: \n");
    int node = 0;
    for (i = 0; i < ver; i++) {
        for (j = 0 ; j < ver ; j++)
        {
            node = P[i][j];
            printf("%d  ",node);
        }
        printf("\n");
    }
   printf("\n");
    //output
    int length,intermediate;
    for (i = 0; i < ver; i++) {
        for (j = 0 ; j < ver ; j++)
        {
            length = D[i][j];
            intermediate = P[i][j];
            //int inter1,inter2;
            if (length != 0) {
                if (intermediate == 0) {
                    //no intermediate nodes
                    printf("(%d,%d) = V%d->V%d  length = %d\n",i,j,i,j,length);
                }else{
                   /* inter1 = P[i][intermediate];
                    inter2 = P[intermediate][j];
                    
                    if (inter1 != 0 && inter2 == 0) {
                        printf("The shortest path from V%d to V%d is V%d - V%d - V%d - V%d, the length is %d\n",i,j,i,inter1,intermediate,j,length);
                    } else if(inter2 != 0 && inter1 == 0) {
                        printf("The shortest path from V%d to V%d is V%d - V%d - V%d - V%d, the length is %d\n",i,j,i,intermediate,inter2,j,length);
                    }else{
                        printf("The shortest path from V%d to V%d is V%d - V%d - V%d, the length is %d\n",i,j,i,intermediate,j,length);
                    }*/
                    printf("(%d,%d) = V%d->",i,j,i);
                    path(i, j, (int*)P,ver);
                    printf("V%d length = %d\n",j,length);
                }
            }
        }
        printf("\n");
    }
}

