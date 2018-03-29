//
//  zhu_yuejing_pa2_strassen.c
//  lab3
//
//  Created by yuejing zhu on 2017/10/19.
//  Copyright © 2017年 yuejing. All rights reserved.
//

#include "zhu_yuejing_pa2_strassen.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

/* 给 int 类型定义别名 datatype */
typedef int datatype;

/* 定义三个矩阵的行列大小 */
int row_a, col_a;
int row_b, col_b;
int row_c, col_c;


//随机生成n*n数组
void get_value(int** Matrix1,int** Matrix2,int size)
{
    int number;
    number = (sqrt(32766/size));
    srand((unsigned)time(NULL));
    for(int i=0;i<size;i++)
    {
        for(int j=0;j<size;j++)
        {
            Matrix1[i][j] = Matrix2[i][j] = rand()%number;
        }
    }
}

void plus(int**  Matrix1,int** Matrix2,int** Matrix3,int size)
{
    for(int i = 0; i < size; i++)
    {
        for(int j = 0;j < size; j++)
        {
            Matrix3[i][j] = Matrix1[i][j] + Matrix2[i][j];
        }
    }
}


void minus(int**  Matrix1,int** Matrix2,int** Matrix3,int size)
{
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            Matrix3[i][j] = Matrix1[i][j] - Matrix2[i][j];
        }
    }
}

void multiply(int** Matrix1,int** Matrix2,int** Matrix3,int size)
{
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            Matrix3[i][j] = 0;
            for(int k = 0; k < size; k++)
                Matrix3[i][j] += Matrix1[i][k] * Matrix2[k][j];
        }
    }
}

int** Create(int size)
{
    int i;
    int **Matrix;
    Matrix = (int **) malloc(sizeof(int *) * size);
    for(i = 0; i < size; i++)
    {
        Matrix[i] = (int *) malloc(sizeof(int) * size);
    }
    return Matrix;
}

/* 释放矩阵内存函数 */
void MatrixFree(int** Matrix, int size)
 {
 int i;
 for(i = 0; i < size; i++)
 {
 free(Matrix[i]);
 }
 free(Matrix);
 }
/* 初始化矩阵函数 */
void Reset(int** Matrix, int n)
 {
 int i,j;
 for(i = 0; i < n; i++)
 {
 for(j = 0; j < n; j++)
 {
 Matrix[i][j] = 0;
 }
 }
 }






void strassenmultiply(int**  Matrix1,int** Matrix2,int** Matrix3,int size)
{
    if(size == 1)
    {
        Matrix3[0][0] = Matrix1[0][0] * Matrix2[0][0];
    }else{
        
        int half_size = size/2;
        int** A11;int** A12;int** A21;int** A22;
        int** B11;int** B12;int** B21;int** B22;
        int** C11;int** C12;int** C21;int** C22;
        int** M1;int** M2;int** M3;int** M4;int** M5;int** M6;int** M7;
        int** MatrixTemp1;int** MatrixTemp2;
        
        A11 = Create(half_size);
        A12 = Create(half_size);
        A21 = Create(half_size);
        A22 = Create(half_size);
        B11 = Create(half_size);
        B12 = Create(half_size);
        B21 = Create(half_size);
        B22 = Create(half_size);
        C11 = Create(half_size);
        C12 = Create(half_size);
        C21 = Create(half_size);
        C22 = Create(half_size);
        
        M1 = Create(half_size);
        M2 = Create(half_size);
        M3 = Create(half_size);
        M4 = Create(half_size);
        M5 = Create(half_size);
        M6 = Create(half_size);
        M7 = Create(half_size);
        
        MatrixTemp1 = Create(half_size);
        MatrixTemp2 = Create(half_size);
        
        Reset(A11, half_size);
        Reset(A12, half_size);
        Reset(A21, half_size);
        Reset(A22, half_size);
        Reset(B11, half_size);
        Reset(B12, half_size);
        Reset(B21, half_size);
        Reset(B22, half_size);
        Reset(C11, half_size);
        Reset(C12, half_size);
        Reset(C21, half_size);
        Reset(C22, half_size);
        
        Reset(M1, half_size);
        Reset(M2, half_size);
        Reset(M3, half_size);
        Reset(M4, half_size);
        Reset(M5, half_size);
        Reset(M6, half_size);
        Reset(M7, half_size);
        
        Reset(MatrixTemp1, half_size);
        Reset(MatrixTemp2, half_size);
        
        for(int i=0;i<half_size;i++)
        {
            for(int j=0;j<half_size;j++)
            {
                A11[i][j] = Matrix1[i][j];
                A12[i][j] = Matrix1[i][j+half_size];
                A21[i][j] = Matrix1[i+half_size][j];
                A22[i][j] = Matrix1[i+half_size][j+half_size];
                
                B11[i][j] = Matrix2[i][j];
                B12[i][j] = Matrix2[i][j+half_size];
                B21[i][j] = Matrix2[i+half_size][j];
                B22[i][j] = Matrix2[i+half_size][j+half_size];
            }
        }

        //M1
        plus(A11, A22, MatrixTemp1, half_size);
        plus(B11,B22,MatrixTemp2, half_size);
        strassenmultiply(MatrixTemp1,MatrixTemp2,M1,half_size);
        //M2
        plus(A21, A22, MatrixTemp1,half_size);
        strassenmultiply(MatrixTemp1, B11, M2, half_size);
        //M3
        minus(B12, B22, MatrixTemp1, half_size);
        strassenmultiply(A22, MatrixTemp1, M3, half_size);
        //M4
        minus(B21, B11, MatrixTemp1, half_size);
        strassenmultiply(A22, MatrixTemp1, M4, half_size);
        //M5
        plus(A11, A12, MatrixTemp1,half_size);
        strassenmultiply(B22, MatrixTemp1, M5, half_size);
        //M6
        minus(A21, A11, MatrixTemp1, half_size);
        plus(B11, B12, MatrixTemp2, half_size);
        strassenmultiply(MatrixTemp1, MatrixTemp2, M6, half_size);
        //M7
        minus(A12, A22, MatrixTemp1, half_size);
        plus(B21, B22, MatrixTemp2, half_size);
        strassenmultiply(MatrixTemp2, MatrixTemp1, M7, half_size);
        
        
        
        for(int i=0;i<half_size;i++)
        {
            for(int j=0;j<half_size;j++)
            {
                Matrix3[i][j] = C11[i][j];
                Matrix3[i][j+half_size] = C12[i][j];
                Matrix3[i+half_size][j] = C21[i][j];
                Matrix3[i+half_size][j+half_size] = C22[i][j];
            }
        }
        
        
        
        MatrixFree(A11, half_size);
        MatrixFree(A12, half_size);
        MatrixFree(A21, half_size);
        MatrixFree(A22, half_size);
        MatrixFree(B11, half_size);
        MatrixFree(B12, half_size);
        MatrixFree(B21, half_size);
        MatrixFree(B22, half_size);
        MatrixFree(C11, half_size);
        MatrixFree(C12, half_size);
        MatrixFree(C21, half_size);
        MatrixFree(C22, half_size);
        MatrixFree(M1, half_size);
        MatrixFree(M2, half_size);
        MatrixFree(M3, half_size);
        MatrixFree(M4, half_size);
        MatrixFree(M5, half_size);
        MatrixFree(M6, half_size);
        MatrixFree(M7, half_size);
        MatrixFree(MatrixTemp1, half_size);
        MatrixFree(MatrixTemp2, half_size);
        
        
        
        
        
    }
}
/*
int Create(int n)
    {
    int i;
    int** Matrix;
    Matrix = (int **) malloc(sizeof(int *) * n);
    for(i = 0; i < n; i++)
    {
        Matrix[i] = (int *) malloc(sizeof(int) * n);
    }
    return Matrix;
}
*/
   /* 初始化矩阵函数 */
/*void Reset(int** Matrix, int n)
{
    int i,j;
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            Matrix[i][j] = 0;
        }
    }
}
*/
/* 读入数据函数 */
/*void Input(int** Matrix, int n)
{
    int i,j;
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            scanf("%d", &Matrix[i][j]);
        }
    }
}
*/
/* 输出数据函数 */
/*void Output(int** Matrix, int n)
{
    int i,j;
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            printf("%d ", Matrix[i][j]);
        }
        printf("\n");
    }
}
*/
/* 矩阵乘法运算函数 */
/*void MatrixMutiply(int** a, int** b, int** c)
{
    int i,j,k;
    for(i = 0; i < row_c; i++)
    {
        for(j = 0; j < col_c; j++)
        {
            for(k = 0; k < col_a; k++)
            {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}
*/
/* 释放矩阵内存函数 */
/*void MatrixFree(int** Matrix, int n)
{
    int i;
    for(i = 0; i < n; i++)
    {
        free(Matrix[i]);
    }
    free(Matrix);
}
*/












int main(){
  //  int i;
    int **a, **b, **c;
    
    /* 创建并读入矩阵a */
    scanf("%d", &row_a);
    a = Create(row_a);
    Input(a,row_a);
    
    /* 创建并读入矩阵b */
    scanf("%d", &row_b);
    b = Create(row_b);
    Input(b,row_b);
    
    
    /* 创建并初始化结果矩阵c */
    c = Create(row_c);
    Reset(c, row_c);
    
    /* 进行矩阵乘法运算 */
    MatrixMutiply(a, b, c);
    
    /* 输出结果矩阵C */
    Output(c, row_c);
    
    
    /* 释放矩阵内存 */
    MatrixFree(a,row_a);
    MatrixFree(b,row_b);
    MatrixFree(c,row_c);
    
    //system("pause");
    return 0;

}

