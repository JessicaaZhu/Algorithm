//
//  lab1.c
//  575al
//
//  Created by yuejing zhu on 2017/9/26.
//  Copyright © 2017年 yuejing. All rights reserved.
//

#include "lab1.h"
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

//int _input_array[1000];
//int _total_count;
int total_count;

void swap(int *x, int *y){
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}
void printstar(int S[], int size)
{
   
        
    if (size <= 20){
        int snum;
        for (int i =0; i < size; i++)
        {
            snum = S[i];
            for(int j =0; j < snum; j++)
            {
                printf("*");
            }
            printf("\n");
        }
        printf("\n");
        
    }
    
}
void printarr(int S[], int size)
{
    for (int i =0; i < size; i++)
        printf("%d ", S[i]);
    printf("");
    
}
void Insertion_Sort(int n,int arr[])
{
        for (int i=0; i<n; i++){
            for (int j=i;j>=1&&arr[j]<arr[j-1];j--){
                swap(&arr[j],&arr[j-1]);
                printstar(arr, n);
            }
    }
}

void Random_Quick_Sort(int S[],int low, int high){
 //开始 获得输入
    
    if (high>low) {
        int i,j;
        srand((unsigned)time(NULL));
        int ran = low + rand()%(high-low);
        swap(&S[ran], &S[low]);
        int pivot = S[low];
        //把一行数排好
        j = low;
        for (i = low + 1; i<=high; i++){
            if(S[i]< pivot){
                j++;
                swap(&S[i], &S[j]);
                //printstar(S, total_count);  精简*输出
            }
        }
        swap(&S[low], &S[j]);
        printstar(S, total_count);
        //调用自己排列两边
        Random_Quick_Sort(S, low, j-1);
        Random_Quick_Sort(S, j+1, high);
    }
}


void Exchange_Sort(int n,int S[]){
    int i,j;
    for (i=0; i< n; i++){
        for (j=i+1 ;j< n; j++){
            if (S[j] < S[i])
                swap(&S[j], &S[i]);
         printstar(S, n);
        }
    }
}
//merge two subarray of S[]
//First subarray is S[l..m]
//second subarray is S[m+1..r]
void Merge(int l,int m, int r, int S[]){
    int i ,j ,k;
    int n1 = m - l + 1;
    int n2 = r - m;
    
    //create temp arrays
    int  L[n1], R[n2];
    //copy data to temp array L and R
    for (i = 0; i < n1; i++)
        L[i] = S[l + i];
    for (j = 0; j < n2; j++)
        R[j] = S[m + 1 +j];
    
    //merge the temp arrays back into S[l..r]
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if(L[i] <= R[j])
        {
            S[k] = L[i];
            i++;
        }else{
            S[k] = R[j];
            j++;
        }
        k++;
    }
    
    //copy the remaining elements of L[]/R[],if there are any
    while (i < n1)
    {
        S[k] = L[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        S[k] = R[j];
        j++;
        k++;
    }
    printstar(S, total_count);
}
//l is for left index and r is right index of the sub-array of arr to be sorted
void Merge_Sort(int S[], int l, int r)
{
    if (l < r)
    {
        int m = l+(r-l)/2;
        //sort left and right halves
        Merge_Sort(S, l, m);
        Merge_Sort(S, m+1, r);
        Merge(l, m, r, S);
    }
}


void mloop(void){
    do{
    printf("\nselect the sorting algorithm: \nExchange sort(1)\nInsertion sort(2)\nmerge sort(3)\nRandomized quick sort(4)\nYou only need to enter item number\n");
    int algo = 0;
    scanf("%d",&algo);
    printf("input count of numbers n(1-1000):\n");
    scanf("%d",&total_count);
    int input_array[1000];
    int ran_num;
    srand((unsigned)time(NULL));
    for (int i=0; i<total_count; i++) {
        if(total_count <= 20){
            ran_num = rand()%15 + 1;
        }else
            ran_num = rand()%1000;
        input_array[i] = ran_num;
    }
    
    printf("The orignal array is:\n");
        if(total_count <= 20){
            printstar(input_array, total_count);
            printarr(input_array, total_count);
            
        }else{
            printarr(input_array, total_count);
        }
    printf("\n");
    printf("Sorting~\n");
        
    if (algo == 1) {
        Exchange_Sort(total_count, input_array);
        printarr(input_array, total_count);
    }else if(algo == 2){
        Insertion_Sort(total_count, input_array);
        printarr(input_array, total_count);
    }else if(algo == 3){
        Merge_Sort(input_array, 0, total_count-1);
        printarr(input_array, total_count);
    }else if(algo == 4){
        Random_Quick_Sort(input_array, 0, total_count-1);
        printarr(input_array, total_count);
    }else{
        printf("Please enter a correct number!");
    }
    }while(1);
    
}

int main(){
    mloop();
}

