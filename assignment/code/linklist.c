//
// Created by user on 2020/1/9.
//


#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "linklist.h"

//sss
struct Lnode{
    char data[length];
    struct Lnode *next;
};

linklist ListInit(char data[]){
    linklist L=NULL;
    L=malloc(sizeof(struct Lnode));
    if (L==NULL){
        printf("no memory");
        exit(1);
    }
    strcpy(L->data,data);
    L->data[strlen(data)]='\0';
    L->next=NULL;
    return L;
}


//插入e
linklist ListInsert(linklist L, char e[]){
    if (L==NULL){
        L=ListInit(e);
        return L;
    }
    linklist new=ListInit(e);

    linklist first=L;
    while(first->next!=NULL){
        first=first->next;
    }
    first->next=new;
    return L;

}

void Printlist(linklist L){
    if(L!=NULL) {
        linklist temp = L;
        while (temp != NULL) {
            printf("===%s\n", temp->data);
            temp = temp->next;
        }
    }
}

int countlinklist(linklist L){
    int i=0;
    int len=0;
    if(L==NULL){ return i;}
    i++;
    while(L->next!=NULL){
        L=L->next;
        len=(len>strlen(L->data)?len:strlen(L->data));
        i++;
    }
    return i;
}

int countmaxlen(linklist L){

    int len=0;
    if(L==NULL){ return 0;}

    while(L->next!=NULL){
        L=L->next;
        len=(len>strlen(L->data)?len:strlen(L->data));

    }
    return len;
}

void copyurltolist(char **vertexlist,linklist L,int number){
    linklist temp=L;
    for(int i=0;i<number;i++){
        char second[]=".txt";
        strcat(temp->data,second);
        strcpy(vertexlist[i],temp->data);
        vertexlist[i][strlen(temp->data)]='\0';
        temp=temp->next;
    }
}

void copyurltolistwithouttxt(char **vertexlist,linklist L,int number){
    linklist temp=L;
    for(int i=0;i<number;i++){
        strcpy(vertexlist[i],temp->data);
        vertexlist[i][strlen(temp->data)]='\0';
        temp=temp->next;
    }
}

void  freelist(linklist L){
    while (L!=NULL){
        linklist temp=L;
        L=L->next;
        free(temp);

    }

}
linklist findprev(linklist L, char s[]){
    linklist temp=L;
    while(strcmp(temp->next->data,s)!=0 && temp->next->next!=NULL){
        temp=temp->next;
    }
    if(strcmp(temp->next->data,s)==0){
        return temp;
    } else{printf("error no value");
        return  NULL;}
}

linklist cutsection1(linklist L){
    linklist temp=L;
    char section1[]="section-1";
    char end[]="#end";
    int i;
    if(L==NULL){printf("memory error"); exit(1);}
    while( i = strcmp(temp->data,section1)!=0 && L->next!=NULL){
        L=temp->next;
        free(temp);
        temp=L;
    }
    temp=L;
    L=L->next;
    free(temp);

    linklist back=NULL;
    back=findprev(L,end);
    freelist(back->next);
    back->next=NULL;

    return L;
}


int countnode(linklist L){
    linklist tmp=L;
    int count=0;
    if(tmp==NULL) {
        return 0;
    }
    while(tmp->next!=NULL){
        count++;
        tmp=tmp->next;
    }
    count++;
    return count;
}

void insertneighbour(graph g,linklist neighbour,char **vertexlist,int i,int maxnumber){
    linklist temp=neighbour;
    while(temp!=NULL){
        int j=0;
        char com[100];
        strcpy(com,strcat(temp->data,".txt"));
        com[strlen(temp->data)]='\0';
        for (j=0;j<maxnumber;j++){
            char second[100];
            strcpy(second,vertexlist[j]);
            second[strlen(vertexlist[j])]='\0';
            if(strcmp(com,second)==0){
                Edge e;
                e.v=i;
                e.w=j;
                insertEdge(g,e);
                //printf("*%d-%\n",i,j);d*
            }
        }
        temp=temp->next;
    }

}

// next part for part b

linklist OrderedListInsert(linklist L, char e[]){
    if (L==NULL){
        L=ListInit(e);
        return L;
    }
    linklist new=ListInit(e);

    linklist first=L,mark=L;
    if(strcmp(e,first->data)<0){
        new->next=first;
        return new;
    }

    while(first->next!=NULL && strcmp(e,first->data)>0){
        mark=first;
        first=first->next;
    }
    if (first->next==NULL && strcmp(e,first->data)>0){
        first->next=new;
        return L;
    }
    if(strcmp(e,mark->data)>0 && mark!=first)
    {mark->next=new;
        new->next=first;}
    else{
        first->next=new;
    }
    //Printlist(L);
    //printf("-----\n");
    return L;

}



struct wordnode{
    char word[length];
    char **urls;
    int count;
    struct  wordnode *next;
};


linklist cutsection2(linklist L){
    linklist temp=L;
    char section1[]="section-2";
    char end[]="#end";
    int i;
    if(L==NULL){printf("memory error"); exit(1);}
    while( i = strcmp(temp->data,section1)!=0 && L->next!=NULL){
        L=temp->next;
        free(temp);
        temp=L;
    }
    temp=L;
    L=L->next;
    free(temp);

    linklist back=NULL;
    back=findprev(L,end);
    freelist(back->next);
    back->next=NULL;

    return L;
}

Wordlist createWordlist(char word[],char url[],int number){
    Wordlist new;
    new=malloc(sizeof(struct wordnode));
    strcpy(new->word,word);
    new->word[strlen(word)]='\0';
    new->count=1;
    new->urls=malloc(number * sizeof(char *));
    for(int i=0;i<number;i++){
        new->urls[i]=malloc(length * sizeof(char));
    }
    strcpy(new->urls[new->count-1],url);
    new->urls[new->count-1][strlen(url)]='\0';
    new->next=NULL;
    return new;
}

Wordlist OrderedWordInsert(Wordlist L, char word[], char url[], int number){
    if (L==NULL){
        L=createWordlist(word,url,number);
        return L;
    }
    Wordlist new=createWordlist(word,url,number);

    Wordlist first=L,mark=L;
    if(strcmp(word,first->word)<0){
        new->next=first;
        return new;
    }

    if(strcmp(word,first->word)==0){
        freewordlist(new,number);
        if(strcmp(first->urls[first->count-1],url)!=0) {
            first->count=first->count+1;

            strcpy(first->urls[first->count - 1], url);
            first->urls[first->count-1][strlen(url)]='\0';
        }
        return L;
    }
    while(first!=NULL){
        if(strcmp(word,first->word)<0){
            mark->next=new;
            new->next=first;
            return L;
        }

        if(strcmp(word,first->word)==0){
            freewordlist(new,number);
            if(strcmp(first->urls[first->count-1],url)!=0) {
                first->count=first->count+1;

                strcpy(first->urls[first->count - 1], url);
                first->urls[first->count-1][strlen(url)]='\0';
            }
            return L;
        }
        mark=first;
        first=first->next;
    }

    mark->next=new;
    return L;
    }




Wordlist getIndex(linklist article, Wordlist wordlist,
        int i,int number,char **vertexlist){
    linklist node=article;
    while(node!=NULL){
        wordlist=OrderedWordInsert(wordlist,node->data,vertexlist[i],number);
        node=node->next;
    }
    return wordlist;
}


void PrintWordlist(Wordlist wordlist){
    if (wordlist==NULL){printf("wordlist NULL\n"); exit(0);}
    Wordlist tmp=wordlist;
    while(tmp!=NULL){
        printf("%s ",tmp->word);
        for(int i=0;i<tmp->count;i++){
            printf("%s ",tmp->urls[i]);
        }
        tmp=tmp->next;
        printf("\n");
    }

}

void FPrintWordlist(Wordlist wordlist){
    FILE *fr=NULL;
    fr=fopen("invertedIndex.txt","w+");
    Wordlist tmp=wordlist;
    while(tmp!=NULL){
        fprintf(fr,"%s",tmp->word);
        for(int i=0;i<tmp->count;i++){
            fprintf(fr," %s",tmp->urls[i]);
        }
        tmp=tmp->next;
        fprintf(fr,"\n");
    }
    fclose(fr);
}


void freewordlist(Wordlist wordlist,int number){
    while(wordlist!=NULL){
        Wordlist temp=wordlist;
        wordlist=wordlist->next;
        for(int i=0;i<number;i++){
            free(temp->urls[i]);
        }
        free(temp->urls);
        free(temp);
    }

}