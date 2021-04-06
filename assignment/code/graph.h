//
// Created by Aaron Wang on 2020/1/16.
//

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Graphrep *graph;

typedef int Vertex;

typedef struct Edge{
    Vertex v;
    Vertex w;
} Edge;

graph newGraph(int number);
void insertEdge(graph g,Edge e);
bool adjacent(graph g,Vertex v, Vertex w);
void showGraph(graph g);
void freeGraph(graph g);
void pagerankal(double d, double diffPR, int maxIterations,
                   int number, int outdegree[],graph g, double PR[]);
