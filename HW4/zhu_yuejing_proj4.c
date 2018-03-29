//
//  main.c
//  HW4
//
//  Created by yuejing zhu on 2017/11/21.
//  Copyright © 2017年 yuejing. All rights reserved.
//

//#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define infinity 9999
#define MAX 20

int G[MAX][MAX],spanning[MAX][MAX],ver; //for prim
int Set[MAX];//for kruskal

struct Edge
{
    int start, end, weight;
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


int Comp(const void* a, const void* b)
{
    struct Edge* a1 = (struct Edge*)a;
    struct Edge* b1 = (struct Edge*)b;
    return a1->weight > b1->weight;
}

void Kruskal(struct Graph* graph)
{
    
    // int V=graph->V;
    int E=graph->E;
    //  struct Edge result[MAXNUM];
    int i,start,end;
    qsort(graph->edge, graph->E, sizeof(graph->edge[0]), Comp);
    for(i=0;i<E;i++)
    {
        Set[i]=-1;
    }
    
    for (int i = 0; i<E; i++)
    {
        start=graph->edge[i].start;
        end=graph->edge[i].end;
        int x=find3(start);
        int y=find3(end);
        
        if (x!=y)
        {
            printf("Edge[%d-%d]\t weight： %d\n",start+1,end+1,graph->edge[i].weight);
            union3(x,y);
        }
    }
    return;
}


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
    
    
    int i,j;
    srand((int)time(NULL));
    ver = (rand()%6)+5;//5-10
    int x = 0,y = 0;
    
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
    printf("Please choose the prim and kruskal:\n");
    printf("1.Prims algorithm\n");
    printf("2.Kruskal algorithm\n");
    
    int choose;
    scanf("%d",&choose);
   
    if (choose == 1) {
        prims();
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
                    printf("Edge[%d,%d]\t weight = %d\n",i,j,spanning[i][j]);
                }
            }
            y++;
        }
        printf("\n");
       // printf("\n\nTotal cost of spanning tree=%d\n",total_cost);
        

    }else if(choose == 2){
        int edgenum=ver *(ver-1);
        struct Graph* graph=create_graph(ver,edgenum);
        
        
        for(int i=0;i<ver;i++)
        {
            for(int j=0;j<ver;j++)
            {
                int num=i*(ver-1)+j;
                graph->edge[num].start = i;
                graph->edge[num].end = j;
                graph->edge[num].weight = G[i][j];
                
            }
        }
        
        Kruskal(graph);
        
    }else{
        printf("You enter uncorrect number!\n");
        exit(1);
    }
    return 0;
}

