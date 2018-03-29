//
//  knapsack.c
//  HW5
//
//  Created by yuejing zhu on 2017/12/2.
//  Copyright © 2017年 yuejing. All rights reserved.
//

#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


#define max 100
#define Size 11

typedef struct{
    int profit;
    int weight;
}Item;
int Weight;

//Brute force
int maxNum(int a, int b)
{
    return (a>b) ? a : b;
}
//change string to 0/1
int itoa_bin(unsigned int data, char *str)
{
    if (str == NULL)
        return -1;
    
    char *start = str;
    
    while (data)
    {
        if (data & 0x1)
            *str++ = 0x31;
        else
            *str++ = 0x30;
        
        data >>= 1;
    }
    
    *str = 0;
    
    //reverse the order
    char *low, *high, temp;
    low = start;
    high = str - 1;
    
    while (low < high)
    {
        temp = *low;
        *low = *high;
        *high = temp;
        
        ++low;
        --high;
    }
    
    return 0;
}

void bruteforce(int p[], int w[], int num, int C)
{
    int i, j, k, len;
    int maxvalue = 0, maxweight = 0;
    int weight, value;
    int temp[Size], res[Size];
    char a[Size];
    for (i = 0; i < pow(2, num); i++)
    {
        weight = 0;
        value = 0;
        itoa_bin(i, a);
        len = (unsigned)strlen(a);
        memset(temp, 0, sizeof(int)*num);
        for (j = len, k = 0; j >= 1; j--)
        {
            if (a[j-1] == '1')
            {
                weight += w[num - len + j];
                value += p[num - len + j];
                temp[k] = num - len + j;
                k++;
            }
        }
        if (weight <= C && value>maxvalue)
        {
            maxvalue = value;
            maxweight = weight;
            memset(res, 0, sizeof(int)*num);
            memcpy(res, temp, sizeof(int)*num);
        }
    }
    printf("total profit: %d\n",maxvalue);
    printf("total weight: %d\n",maxweight);
    printf("selected items: \n");
   
    for (i = 0; i < k; i++)
    {
        if (res[i] != 0)
            printf("item %d: (%d,%d)\n",res[i],p[res[i]],w[res[i]]);
    }
    
}

//DP

int findprofit(int row, int weight, Item arr[], int rowarr[], int num)
{
    Item item = arr[row - 1];
    
    if (row == 1)
    {
        if (weight >= item.weight)
        {
            rowarr[row] = 1;
            printf("  %d\n",item.profit);
            return item.profit;
            
        }
    }
    else
    {
        int temp1[num + 1];
        int temp2[num + 1];
        for (int i = 0; i<num + 1; i++)
        {
            temp1[i] = 0;
            temp2[i] = 0;
        }
        
        int value1 = findprofit(row - 1, weight, arr, temp1, num);
        if (item.weight <= weight)
        {
            int value2 = findprofit(row - 1, weight - item.weight, arr, temp2, num) + item.profit;
            if (value2>value1)
            {
                for (int i = 1; i<num + 1; i++)
                {
                    if (temp2[i])
                    {
                        rowarr[i] = 1;
                    }
                }
                rowarr[row] = 1;
                printf("  %d  ",value2);
                return value2;
            }
        }
        for (int i = 1; i<num + 1; i++)
        {
            if (temp1[i])
            {
                rowarr[i] = 1;
            }
        }
        printf("  %d  ",value1);
        return value1;
    }
    return 0;
}


void refinementDP(Item arr[], int num)
{
    int rowarr[num + 1];
    for (int i = 0; i<num + 1; i++)
    {
        rowarr[i] = 0;
    }
    printf("Entries calculated in each row: \n");
    int profit = findprofit(num, Weight, arr, rowarr, num);
    printf("\nrefinementDP total profit:%d\nNodes included:", profit);
    int weight = 0;
    for (int row = 1; row<num + 1; row++)
    {
        if (rowarr[row] == 1)
        {
            Item item = arr[row - 1];
            weight += item.weight;
            printf("(%d,%d) ", item.profit, item.weight);
        }
    }
    printf("\nweight: %d\n", weight);
    
}




//Backtracking
void createitems(Item arr[], int p[],int w[],int num,int weight)
{
    int i = 0;
    while (i<num)
    {
        Item item = { p[i + 1], w[i + 1] };
        arr[i] = item;
        i++;
    }
    Weight = weight;
}

void sortitemarr(Item arr[], int num)
{
    for (int i = 0; i<num; i++)
    {
        for (int j = i + 1; j<num; j++)
        {
            Item item1 = arr[i];
            Item item2 = arr[j];
            float p1 = item1.profit*1.0 / item1.weight;
            float p2 = item2.profit*1.0 / item2.weight;
            if (p2>p1)
            {
                arr[i] = item2;
                arr[j] = item1;
            }
        }
    }
}

int kwf2(Item arr[], int num, int index, int weight, int profit)
{
    int bound = profit;
    
    while (weight<Weight && index <= num)
    {
        Item item = arr[index - 1];
        
        if (weight + item.weight <= Weight)
        {
            weight += item.weight;
            bound += item.profit;
        }
        else
        {
            float k = (Weight - weight)*1.0/item.weight;
            weight = Weight;
            bound += (int)(k*item.profit);
        }
        index++;
    }
    return bound;
}

bool Promosing(Item arr[], int num, int index, int weight, int profit, int maxprofit)
{
    if (weight >= Weight)
    {
        return false;
    }
    int bound = kwf2(arr, num, index + 1, weight, profit);
    return bound>maxprofit;
}

void knapSack(Item arr[], int num, int index, int profit, int weight, int *maxprofit, int best[], int include[])
{
    int bound=0;
    if (weight <= Weight && profit>*maxprofit)
    {
        *maxprofit = profit;
        for (int i = 0; i<num; i++)
        {
            best[i] = include[i];
        }
    }
    if (Promosing(arr, num, index, weight, profit, *maxprofit))
    {
        bound = kwf2(arr, num, index + 1, weight, profit);
        printf("node %d weight %d profit %d bound %d\n",index,weight,profit,bound);
        
        
        
        Item item = arr[index];
        include[index] = 1;
        knapSack(arr, num, index + 1, profit + item.profit, weight + item.weight, maxprofit, best, include);
        
        include[index] = 0;
        knapSack(arr, num, index + 1, profit, weight, maxprofit, best, include);// not add item
    }
}


void backtracking(Item arr[], int num)
{
    sortitemarr(arr, num);
    
    int bestset[num];
    int include[num];
    for (int i = 0; i<num; i++)
    {
        bestset[i] = 0;
        include[i] = 0;
    }
    int maxprofit = 0;
    knapSack(arr, num, 0, 0, 0, &maxprofit, bestset, include);
    
    printf("backtracking total profit:%d\nNodes included:", maxprofit);
    int weight = 0;
    for (int i = 0; i<num; i++)
    {
        if (bestset[i] == 1)
        {
            Item item = arr[i];
            weight += item.weight;
            printf("(%d,%d) ", item.profit, item.weight);
        }
    }
    printf("\nweight: %d\n", weight);
    
}


int main()
{
    int items, weight, temp = 0;
    int i;
    
    srand((unsigned)time(NULL));
    items= 4 + rand() % 4;
    
    printf("Create %d items randomly:\n",items);
    printf("\n");
    
    int * w= malloc((items + 1)*sizeof(int));
    memset(w, 0, (items + 1)*sizeof(int));
    int * p = malloc((items + 1)*sizeof(int));
    memset(p, 0, (items + 1)*sizeof(int));
    
    for (i = 1; i <= items; i++)
    {
        printf("item %d:  ",i);
        p[i] = 10 + rand() % 20;
        printf("Profit = %d  ",p[i]);
        w[i] = 5 + rand() % 15;
        printf("Weight = %d\n",w[i]);
        temp += w[i];
    }
    weight = floor(0.6*temp);
    printf("\nCapacity: %d\n",weight);
    Item order[items];
    createitems(order, p, w, items, weight);
    
    printf("\n=====================brute force=====================\n");
    bruteforce(p, w, items, weight);
    printf("\n=====================refinement DP=====================\n");
    refinementDP(order, items);
    printf("\n=====================backtracking=====================\n");
    backtracking(order, items);
    
    free(w);
    free(p);
    return 0;
}
