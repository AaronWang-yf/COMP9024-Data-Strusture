//
// Created by Aaron Wang on 2020/1/15.
//

#include <stdio.h>
#include "readURL.h"

#include <stdlib.h>

/*
 1.read collection.txt into linklist
 2.get the length, make a ordered array of of url as dict
 3. create a matrix
*/

typedef struct output {
    char url[100];
    int outdegree;
    double pagerank;
}OutPut;

void sortoutput(OutPut *s,int number){
    int i,j;
    OutPut tmp;
    for(i = 0; i< number - 1; i++) {
        for (j = 0; j < number - i - 1; j++) {
            if (s[j].pagerank <= s[j + 1].pagerank) {
                tmp=s[j];
                s[j]=s[j+1];
                s[j+1]=tmp;


                if (s[j].outdegree < s[j + 1].outdegree && s[j].pagerank == s[j+ 1].pagerank) {
                    tmp=s[j];
                    s[j]=s[j+1];
                    s[j+1]=tmp;
                }
            }
        }
    }



}


int main(int argc, char ** argv){

    int number=0;
   // int maxlen=0;
   char **vertexlistwithouttxt;
    char **vertexlist;
    linklist head=NULL;
    head=readURL(head);  //read collection.txt
    number=countlinklist(head);   //get the number of url
   // maxlen=countmaxlen(head);       //just use length 32  in readURL.h
    //printf("==%d=%d\n",number,maxlen);
    //Printlist(head);
    vertexlist=malloc(number* sizeof(char *));
    vertexlistwithouttxt=malloc(number* sizeof(char *));
    for (int i=0;i<number;i++){
        vertexlist[i]=malloc((100)* sizeof(char));
        vertexlistwithouttxt[i]=malloc((100)* sizeof(char));
    }
    copyurltolistwithouttxt(vertexlistwithouttxt,head,number);
    copyurltolist(vertexlist,head,number);  //put urls into vertexlist with .txt

    /*
    for (int i=0;i<number;i++){
        printf("list=%s\n",vertexlist[i]);
    }
     */

/*
    test=readString(test,vertexlist[0]);
    test=cutsection1(test);
    Printlist(test);
    //以上部分完成 url的获取，section1 内容的获取并存储在test中
*/


    //以下部分建立图
    graph g=NULL;
    g=newGraph(number);



    //below realize get out degree and format a graph of urls

    int outdegree[number];
    for(int i=0;i<number;i++){
        linklist neighbour=NULL;
        neighbour=readString(neighbour,vertexlist[i]); //read url.txt
        neighbour=cutsection1(neighbour);  //get section1
        //Printlist(neighbour);
       // printf("---\n");
        int count=0;
        insertneighbour(g,neighbour,vertexlist,i,number);
        count=countnode(neighbour);
        outdegree[i]=count;
        freelist(neighbour);
        //printf("**%d\n",outdegree[i]);
    }

    //showGraph(g);

    double d,diffPR,maxIterations;
    d=atof(argv[1]);
    diffPR=atof(argv[2]);
    maxIterations=atof(argv[3]);

    double PR[number];
    pagerankal(d,diffPR,maxIterations,
            number,outdegree,g,PR);


    OutPut output[number];
    for(int i=0;i<number;i++){
        output[i].outdegree=outdegree[i];
        output[i].pagerank=PR[i];
        strcpy(output[i].url,vertexlistwithouttxt[i]);
        output[i].url[strlen(vertexlistwithouttxt[i])]='\0';
    }

    sortoutput(output,number);

    //for(int i=0;i<number;i++){printf("%s, %d, %.7f\n",output[i].url,output[i].outdegree, output[i].pagerank);}
    FILE *fr;
    fr=fopen("pagerankList.txt","w+");
    for(int i=0;i<number;i++){
        fprintf(fr,"%s, %d, %.7f\n",
                output[i].url,output[i].outdegree, output[i].pagerank);
    }
    fclose(fr);

    //free memory
    //freelist(test);
    freeGraph(g);
    freelist(head);
    for (int i=0;i<number;i++){
        free(vertexlist[i]);
        free(vertexlistwithouttxt[i]);
    }
    free(vertexlist);
    free(vertexlistwithouttxt);
}