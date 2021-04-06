#include <stdio.h>
#include <stdbool.h>
#include "graph.h"
#define length 100





typedef struct Lnode *linklist;

linklist ListInit(char data[]);

linklist ListInsert(linklist L, char data[]);

int countlinklist(linklist L);

//int countmaxlen(linklist L);
void copyurltolistwithouttxt(char **vertexlist,linklist L,int number);

void copyurltolist(char **vertexlist,linklist L,int number);

linklist cutsection1(linklist L);

void Printlist(linklist L);

void  freelist(linklist L);

int countnode(linklist L);

void insertneighbour(graph g,linklist neighbour,char **vertexlist,int i,int maxnumber);

// for part b

linklist OrderedListInsert(linklist L, char e[]);

typedef struct wordnode *Wordlist;


linklist cutsection2(linklist L);

Wordlist getIndex(linklist article, Wordlist wordlist,
                  int i,int number,char **vertexlist);


void PrintWordlist(Wordlist wordlist);

void freewordlist(Wordlist wordlist,int number);

void FPrintWordlist(Wordlist wordlist);
