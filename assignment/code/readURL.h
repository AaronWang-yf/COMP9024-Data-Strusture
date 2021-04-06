//
// Created by user on 2020/1/13.
//

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "linklist.h"



linklist readURL(linklist L);
linklist readString(linklist L,char fname[]);


//next for part b
linklist OrderedreadURL(linklist L);



//next for part  c

typedef struct pagerank *PRnode;

typedef struct page{
    char url[length];
    int count;
    double result;
} Page;   // when get the number of urls from pagerank.txt, an array can store the struct

PRnode readPageRank();

void PrintPageRank(PRnode head);

int NumberOfPages(PRnode head);

void freePRnode(PRnode head);

int readIndex(char *input,Page pages[],PRnode head,int point);