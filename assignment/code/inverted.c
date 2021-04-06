//
// Created by 王云帆 on 2020/1/13.
//

#include <stdio.h>
#include "readURL.h"


int main(){
    int number=0,i;
    linklist head=NULL;
    head=OrderedreadURL(head);  //read collection.txt
    number=countlinklist(head); //get the number of url
    char **vertexlistwithouttxt;
    char **vertexlist;
    vertexlist=malloc(number* sizeof(char *));
    vertexlistwithouttxt=malloc(number* sizeof(char *));
    for (int i=0;i<number;i++){
        vertexlist[i]=malloc((100)* sizeof(char));
        vertexlistwithouttxt[i]=malloc((100)* sizeof(char));
    }
    copyurltolistwithouttxt(vertexlistwithouttxt,head,number);
    copyurltolist(vertexlist,head,number);  //put urls into vertexlist with .txt

    //Printlist(head);

    Wordlist wordlist=NULL;

    for(i=0;i<number;i++){
        linklist article=NULL;
        article=readString(article,vertexlist[i]);
        article=cutsection2(article);
        wordlist=getIndex(article,wordlist,i,number,vertexlistwithouttxt);
    //  Printlist(article);

      freelist(article);
    }
    //PrintWordlist(wordlist);

    FPrintWordlist(wordlist);

    //free memory
    freelist(head);
    for (int i=0;i<number;i++){
        free(vertexlist[i]);
        free(vertexlistwithouttxt[i]);
    }
    free(vertexlist);
    free(vertexlistwithouttxt);
    freewordlist(wordlist,number);


}