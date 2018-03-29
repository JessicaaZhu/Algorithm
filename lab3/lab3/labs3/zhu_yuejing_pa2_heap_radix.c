//
//  heapandradix.c
//  lab3
//
//  Created by yuejing zhu on 2017/10/17.
//  Copyright © 2017年 yuejing. All rights reserved.
//

#include "heapandradix.h"
#define TEN 10
#include <stdio.h>
#include <stdlib.h>
#include<time.h>

void printarr(int S[], int size)
{
    for (int i =0; i < size; i++)
        printf("%d ", S[i]);
    printf("\n");
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


void max_heapify(int arr[],int i,int n){//i is root node,n = heapsize
    int child, tem;
    for(tem = arr[i]; n > 2 * i; i = child)
    {
        child = 2 * i + 1;//left child
        //larger child
        if (child != n && arr[child + 1] > arr[child])
        {
            child++;
        }
        //compare parent node and child node, get the larger one
        if (tem < arr[child])
        {
            arr[i] = arr[child];
        }
        else break;
    }
    arr[i] = tem;
}

void Heapsort(int arr[],int n)
{
    int i,tem;
    //build max heap
    for(i = (n - 1)/ 2; i >= 0; i--)
    {
        max_heapify(arr, i, n);
    }
    //sort
    for(i = n - 1; i >= 1; i--)
    {
        tem = arr[0];
        arr[0] = arr[i];
        arr[i] = tem;
        
        max_heapify(arr, 0, i-1);
        printstar(arr, n);
    }
}


int getdight(int a, int d)
{
    int b = a;
    while(d > 0&&a > 0){
        b/=TEN;
        d--;
    }
    return b%TEN;
}

int  count_sort (int *array, int n,int d)
{
    printf("%d\n",d);
    int k[TEN] = {0};
    int *temp,*b;
    int i;
    temp = (int *) malloc (sizeof (int)*n);
    b = (int *) malloc (sizeof (int)*n);
    if (NULL == temp)
        return 0 ;
    for (i=0;i<n;i++)
        b[i] = getdight(array[i], d);
    for (i=0;i<n;i++)
        printf("%d ",b[i]);
    printf("\n");
    for (i = 0; i < n; i++)
        k[b[i]]++;//记录与数组下标相等的数值的个数
    for (i=0;i<10;i++)
        printf("%d ",k[i]);
    printf("\n");
    for (i=1;i<10;i++)
        k[i]+=k[i-1];//储存自己数组下标数值在目标数组对应的位置
    for (i=n-1;i>=0;i--)
        temp[--k[b[i]]]=array[i]; //将原数组按大小顺序储存到另一个数组
    for (i=0;i<n;i++)
        printf("%d ",temp[i]);
    printf("\n");
    for (i = 0; i < n; i++)
        array[i] = temp[i];
    free (temp);
    free (b);
    
    return 1 ;
}

void radix_sort(int arr[],int n,int d)
{
    for (int i=0;i<=d;i++)
        count_sort(arr,n,i);
        printstar(arr, n);
}

void mloop(void){
    do{
        printf("Please select Heap sort or Radix sort:\nIf you choose Heap sort please enter number 1\nIf you choose Radix sort please choose number 2\n");
        int algo = 0;
        scanf("%d",&algo);
        if(algo == 1){
            printf("You selected the Heap sort!\n");
        }else if (algo == 2){
            printf("You selected the Radix sort!\n");
        }else{
            printf("Please enter correct number!\n");
        }
        
        int total_number = 0;
        printf("Please input count of numbers n(1-1000):\n ");
        scanf("%d",&total_number);
        if (total_number < 1 || total_number > 1000) {
            printf("The number is not in 1-1000, please enter again!\n");
        }else{
            printf("\n");
        }
        
        int input_array[1000];
        int ran_num;
        srand((unsigned)time(NULL));
        for (int i=0; i<total_number; i++) {
            if(total_number <= 20){
                ran_num = rand()%15 + 1;
            }else
                ran_num = rand()%1000;
            input_array[i] = ran_num;
        }
        
        printf("The orignal array is:\n");
        if(total_number <= 20){
            printstar(input_array, total_number);
            printarr(input_array, total_number);
            
        }else{
            printarr(input_array, total_number);
        }
        printf("\n");
        printf("Sorting~\n");
        
        if(algo == 1){
           // printf("You selected the Heap sort!\n");
            Heapsort(input_array,total_number);
            printarr(input_array, total_number);
        }else if (algo == 2){
          //  printf("You selected the Radix sort!\n");
            radix_sort(input_array,total_number,3);
            printarr(input_array, total_number);
        }else{
           // printf("Please enter correct number!\n");
        }
        
    }while(1);

}

int main(){
    mloop();
}
