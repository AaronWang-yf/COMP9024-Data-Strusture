//
// Created by user on 2020/1/19.
//

#include <stdio.h>
#include "readURL.h"


int main(int argc,char ** argv){
    PRnode head=NULL;
    int nURl=0,point=0;
    head= readPageRank();
    nURl=NumberOfPages(head); //get the number of urls
    //printf("number:%d\n",nURl);
    //PrintPageRank(head);
    Page pages[nURl];
    for(int i=1;i<argc;i++) {
        point=readIndex(argv[i],pages,head,point);
    }

    int i,j;
    Page tmp;
    for(i = 0; i< point-1; i++) {
        for (j = 0; j < point - i - 1; j++) {
            if (pages[j].count <= pages[j + 1].count) {
                tmp=pages[j];
                pages[j]=pages[j+1];
                pages[j+1]=tmp;


                if (pages[j].result < pages[j + 1].result && pages[j].count == pages[j+ 1].count) {
                    tmp=pages[j];
                    pages[j]=pages[j+1];
                    pages[j+1]=tmp;
                }
            }
        }
    }
   // printf("point:%d\n",point);
/*

    for(int i=0;i<point;i++){
        printf("%s,%d,%.7f\n",
               pages[i].url, pages[i].count, pages[i].result);
    }

*/
    if(point>30)
        point=30;
    for(int i=0;i<point;i++){
        printf("%s\n",pages[i].url);
    }


    //free memory
    freePRnode(head);
}