//
//  zhu_yuejing_pa4_prim.c
//  HW4
//
//  Created by yuejing zhu on 2017/11/21.
//  Copyright © 2017年 yuejing. All rights reserved.
//

#include<stdio.h>
#include<stdlib.h>
#include <time.h>

#define infinity 9999
#define MAX 20

int G[MAX][MAX],spanning[MAX][MAX],ver;



int prims()
{
    int cost[MAX][MAX];
    int u,v,min_distance,distance[MAX],from[MAX];
    int visited[MAX],no_of_edges,i,min_cost,j;
    
    //create cost[][] matrix,spanning[][]
    for(i=0;i< ver;i++)
        for(j=0;j<ver;j++)
        {
            if(G[i][j]==0)
                cost[i][j]=infinity;
            else
                cost[i][j]=G[i][j];
            spanning[i][j]=0;
        }
    
    //initialise visited[],distance[] and from[]
    distance[0]=0;
    visited[0]=1;
    
    for(i=1;i<ver;i++)
    {
        distance[i]=cost[0][i];
        from[i]=0;
        visited[i]=0;
    }
    
    min_cost=0;        //cost of spanning tree
    no_of_edges=ver - 1;        //no. of edges to be added
    
    while(no_of_edges>0)
    {
        //find the vertex at minimum distance from the tree
        min_distance=infinity;
        for(i=1;i < ver;i++)
            if(visited[i]==0&&distance[i]<min_distance)
            {
                v=i;
                min_distance=distance[i];
            }
        
        u=from[v];
        
        //insert the edge in spanning tree
        spanning[u][v]=distance[v];
        spanning[v][u]=distance[v];
        no_of_edges--;
        visited[v]=1;
        
        //updated the distance[] array
        for(i=1;i<ver;i++)
            if(visited[i]==0&&cost[i][v]<distance[i])
            {
                distance[i]=cost[i][v];
                from[i]=v;
            }
        
        min_cost=min_cost+cost[u][v];
    }
    
    return(min_cost);
}

int main()
{
    int i,j,total_cost;
    srand((int)time(NULL));
    ver = (rand()%6)+5;//5-10
    int x = 0,y = 0;
    //int G[ver][ver];
    
    //给矩阵所有项初值0
    for (int i = 0; i < ver; i++){
        for (int j = 0 ; j < ver ; j++){
            G[i][j] = 0;
            //edge1[i][j] = 0;
        }
    }
    
    //给矩阵赋值，无向图
    for (int i = 0; i < ver; i++) {
        for (int j = x; j < ver; j++) {
            if (i == j) {
                G[i][j] = 0;
            }else{
                G[i][j] = rand()%10 + 1;//1-10
                G[j][i] = G[i][j];
            }
        }
        x++;
    }
    //输出undirected graph
    printf("The G matrix:\n");
    for (int i = 0; i < ver; i++) {
        for (int j = 0 ; j < ver ; j++)
        {
            int num = G[i][j];
            printf("%d  ",num);
        }
        printf("\n");
    }
    printf("\n");
    
    total_cost = prims();
    printf("\nspanning tree matrix:\n");
    
    for(i=0;i<ver;i++)
    {
        printf("\n");
        for(j=0;j<ver;j++)
            printf("%d\t",spanning[i][j]);
    }
    printf("\n");
    for (int i = 0; i < ver; i++) {
        for (int j = y; j < ver; j++) {
            if (spanning[i][j] != 0) {
                printf("Edge[%d,%d], weight = %d\n",i,j,spanning[i][j]);
            }
        }
        y++;
    }
    printf("\n");
    printf("\n\nTotal cost of spanning tree=%d\n",total_cost);
    return 0;
}


