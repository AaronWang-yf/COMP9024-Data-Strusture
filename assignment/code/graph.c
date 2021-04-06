//
// Created by Aaron Wang on 2020/1/16.
//
#include "graph.h"

typedef struct Graphrep{
    int **edges;
    int nV;  //number of vertices
    int nE;   // number of edges
} Graphrep;

graph newGraph(int number){
    if(number<0){printf("number error");exit(1);}
    int i;

    graph g = malloc(sizeof(Graphrep));
   // assert(g != NULL);
    g->nV = number;
    g->nE = 0;

    // allocate memory for each row
    g->edges = malloc(number * sizeof(int *));
   // assert(g->edges != NULL);
    // allocate memory for each column and initialise with 0
    for (i = 0; i < number; i++) {
        g->edges[i] = calloc(number, sizeof(int));
      //  g->edges[i] = malloc(number* sizeof(int));
     //   assert(g->edges[i] != NULL);
    }
/*
    for(i=0;i<number;i++){
        for(int j=0;j<number;j++){
            g->edges[i][j]=0;
        }
    }
*/
    return g;
}
bool validV(graph g, Vertex v){
    return (g != NULL && v >= 0 && v < g->nV);
}


void insertEdge(graph g,Edge e){
    if ((!validV(g,e.v)) && (!validV(g,e.w))){printf("vertex error");
    exit(1);}
    if (!g->edges[e.v][e.w]) {  // edge e not in graph
        g->edges[e.v][e.w] = 1;

        g->nE++;
    }
}

bool adjacent(graph g,Vertex v, Vertex w){
    //assert(g != NULL && validV(g,v) && validV(g,w));

    return (g->edges[v][w] != 0);
}

void showGraph(graph g){
    //assert(g != NULL);
    int i, j;

    printf("Number of vertices: %d\n", g->nV);
    printf("Number of edges: %d\n", g->nE);
    for (i = 0; i < g->nV; i++) {
        printf("\n %d : ", i);
        for (j = 0; j < g->nV; j++)
            printf("%d ", g->edges[i][j]);
    }
    printf("\n");
}

void freeGraph(graph g){
   // assert(g != NULL);

    int i;
    for (i = 0; i < g->nV; i++)
        free(g->edges[i]);
    free(g->edges);
    free(g);
}


double absvalue(double first, double second){
    double result=first-second;
    if(result>0){ return result;}
    else { return -result;}
}

void pagerankal(double d, double diffPR, int maxIterations,
                   int number, int outdegree[],graph g, double PR[]){
   // showGraph(g);
    int count=0;

    double PRpre[number];
    int i=0,iteration=0;
    for(i=0;i<number;i++){
        PR[i]=1/(double)number;
        PRpre[i]=1/(double)number;
    }
    double diff=diffPR;

    while(iteration++<maxIterations && diff>=diffPR){
        count++;
        diff=0;
        double sumM=0;
        for(i=0;i<number;i++){
            sumM=0;
            for(int j=0;j<number;j++) {
                if (g->edges[j][i] == 1) {
                    sumM = sumM + (double)PRpre[j] / (double)outdegree[j];
                }
            }
            PR[i]=(double)(1-d)/(double)number+d*sumM;
         //   printf("sumM:%.7f----count:%d,PR[%d]:%.7f\n",sumM,count,i,PR[i]);
        }
        for(i=0;i<number;i++){
            diff=diff+ absvalue(PR[i],PRpre[i]);
        }
        for (i=0;i<number;i++){
            PRpre[i]=PR[i];
        }
    }
   // printf("count:%d\n",count);
   // for(int i=0;i<number;i++){
   //     printf("**%.7f\n",PR[i]);
   // }

}


