//
//  zhuyuejing_kruskal.c
//  HW4
//
//  Created by yuejing zhu on 2017/11/21.
//  Copyright © 2017年 yuejing. All rights reserved.
//

#include "zhuyuejing_kruskal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAXNUM 1024

int Set[MAXNUM];

struct Edge
{
    int begin, end, weight;
};

struct Graph
{
    int V, E;
    struct Edge* edge;
};


struct Graph* create_graph(int V, int E)
{
    struct Graph* graph = malloc(sizeof(struct Graph));
    graph->V = V;
    graph->E = E;
    
    graph->edge =malloc(sizeof(struct Edge[E]));
    
    return graph;
}



int find3(int x)
{
    int root=x;
    while(root!=Set[root]&&Set[root]>=0)
    {
        root=Set[root];
    }
    
    int node=x;
    while(node!=root)
    {
        int father=Set[node];
        Set[node]=root;
        node=father;
    }
    return root;
}

void union3(int xroot, int yroot)
{
    /* int xroot = find3(x);
     int yroot = find3(y);
     */
    int height=Set[xroot]+Set[yroot];
    if (Set[xroot] > Set[yroot]){
        Set[xroot] = yroot;
        Set[yroot] = height;
    }
    else{
        Set[yroot] = xroot;
        Set[xroot] = height;
    }
}


int myComp(const void* a, const void* b)
{
    struct Edge* a1 = (struct Edge*)a;
    struct Edge* b1 = (struct Edge*)b;
    return a1->weight > b1->weight;
}

void KruskalMST(struct Graph* graph)
{
    
   // int V=graph->V;
    int E=graph->E;
  //  struct Edge result[MAXNUM];
    int i,begin,end;
    qsort(graph->edge, graph->E, sizeof(graph->edge[0]), myComp);
    for(i=0;i<E;i++)
    {
        Set[i]=-1;
    }
    
    for (int i = 0; i<E; i++)
    {
        begin=graph->edge[i].begin;
        end=graph->edge[i].end;
        int x=find3(begin);
        int y=find3(end);
        
        if (x!=y)
        {
            printf("(%d-%d) \t weight： %d\n",begin+1,end+1,graph->edge[i].weight);
            union3(x,y);
        }
    }
    return;
}

int main()
{
    int A[MAXNUM][MAXNUM];
    srand((int)time(NULL));
    //srand(time(NULL));
    int vertex=4;//rand()  % (10 - 5) + 5;
    printf("Vertices is:%d\n",vertex);
    
    for(int i=0;i<vertex;i++)
    {
        for(int j=i;j<vertex;j++)
        {
            if(i==j)
            {A[i][j]=0;}
            else
            {
                A[i][j]=rand()% 10+1;
                A[j][i]=A[i][j];
            }
        }
    }
    for(int i=0;i<vertex;i++){
        for(int j=0;j<vertex;j++){
            printf("%d\t",A[i][j]);
        }
        printf("\n");}
    
    int edge_num=vertex*(vertex-1);
    struct Graph* graph=create_graph(vertex,edge_num);
    
    
    for(int i=0;i<vertex;i++)
    {
        for(int j=0;j<vertex;j++)
        {
            int test_num=i*(vertex-1)+j;
            graph->edge[test_num].begin = i;
            graph->edge[test_num].end = j;
            graph->edge[test_num].weight = A[i][j];
            
        }
    }
    
    KruskalMST(graph);
    
    return 0;
}


