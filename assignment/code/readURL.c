//
// Created by user on 2020/1/13.
//
#include "readURL.h"


linklist readURL(linklist L){
    char link[length],ch;
    int i=0;
    FILE *fp=fopen("collection.txt","r");
    while((ch=fgetc(fp))!=EOF){
        if(isalnum(ch)){
            link[i]=ch;
            i++;
        }else{
            if(i!=0){
                link[i]='\0';
                i=0;
                L=ListInsert(L,link);
                char link[length];

            }
        }

        // printf("===%c\n",ch);
    }

    fclose(fp);
    return L;
}


linklist readString(linklist L,char fname[]){
    char str[length],ch;
    int i=0;
    FILE *fp=fopen(fname,"r");
    while((ch=fgetc(fp))!=EOF) {
        if (isalnum(ch) || ch=='#' || ch=='-') {
            str[i] = tolower(ch);
            i++;
        } else {
            if (i != 0) {
                str[i] = '\0';
                i = 0;
                L=ListInsert(L,str);
                char str[length];

            }
        }

    }

    fclose(fp);
    return L;
}


//next for part b

linklist OrderedreadURL(linklist L){
    char link[length],ch;
    int i=0;
    FILE *fp=fopen("collection.txt","r");
    while((ch=fgetc(fp))!=EOF){
        if(isalnum(ch)){
            link[i]=ch;
            i++;
        }else{
            if(i!=0){
                link[i]='\0';
                i=0;
                L=OrderedListInsert(L,link);
                char link[length];

            }
        }

        // printf("===%c\n",ch);
    }

    fclose(fp);
    return L;
}




//next for part  c

struct pagerank{
    char url[100];
    int outdegree;
    double result;
    struct pagerank *next;
};





PRnode creatPRlist(char *url,int outdegree, double result){
    PRnode new=NULL;
    new=malloc(sizeof(struct pagerank));
    strcpy(new->url,url);
    new->url[strlen(url)]='\0';
    new->outdegree=outdegree;
    new->result=result;
    new->next=NULL;
    return new;
}

PRnode insertPRlist(PRnode prnode,char *url,int outdegree, double result){
    if(prnode==NULL){
        prnode=creatPRlist(url,outdegree,result);
        return prnode;
    }

    PRnode new=creatPRlist(url,outdegree,result);
    new->next=prnode;
    return new;

}


PRnode readPageRank() {
    PRnode head = NULL;
    char ch, url[length];
    char list[3][100];
    int  i = 0,mark=0;

    FILE *fp;
    fp = fopen("pagerankList.txt", "r");
    while ((ch=fgetc(fp)) != EOF) {
        if (ch != '\n') {
            if (isalnum(ch) || ch=='.') {
                url[i] = ch;
                i++;
            } else {
                if (i != 0) {
                    url[i] = '\0';
                    url[i+1] = '\0';
                    strcpy(list[mark],url);
                    list[mark][strlen(url)]='\0';
                    i=0;
                    char url[length];
                    mark++;
                }
            }

        }
        else{
            url[i] = '\0';
            url[i+1] = '\0';
            strcpy(list[mark],url);
            list[mark][strlen(url)]='\0';
            mark=0;
            i=0;
           // printf("**%s,%s,%s\n",list[0],list[1],list[2]);
            head=insertPRlist(head,list[0],atoi(list[1]),atof(list[2]));
            char list[3][100];
            char url[length];
        }
    }
    fclose(fp);
    return head;
}

int NumberOfPages(PRnode head){
    int i=0;
    PRnode temp=head;
    while (temp!=NULL){
        temp=temp->next;
        i++;
    }
    return i;
}


void PrintPageRank(PRnode head){
    PRnode temp=head;
    while(temp!=NULL){
        printf("%s,%d,%.7f\n",temp->url,temp->outdegree,temp->result);
        temp=temp->next;
    }
}

void freePRnode(PRnode head){
    while (head!=NULL){
        PRnode temp=head;
        head=head->next;
        free(temp);

    }
}




double searchPRnode(PRnode head,char url[]){
    PRnode temp=head;
    while(temp!=NULL){
        if(strcmp(temp->url,url)==0)
        {
            return temp->result;
        }
        temp=temp->next;
    }
}

int insertToken(Page pages[],char *token,int point,PRnode head){
    if (point==0){
        strcpy(pages[0].url,token);
        pages[0].url[strlen(token)]='\0';      //linux bug
        pages[0].count=1;
        pages[0].result=searchPRnode(head,token);
        return 1;
    }
    for(int i=0;i<point;i++){
        if(strcmp(pages[i].url,token)==0){
            pages[i].count++;
            return point;
        }
    }

    strcpy(pages[point].url,token);
    pages[point].url[strlen(token)]='\0';      //linux bug
    pages[point].count=1;
    pages[point].result=searchPRnode(head,token);
    point++;
    return point;

}

int inPRnode(PRnode head,char *token){
    PRnode temp=head;
    while(temp!=NULL){
        if(strcmp(temp->url,token)==0){
            return 1;
        }
        temp=temp->next;
    }
    return 0;
}


int readIndex(char *input,Page pages[],PRnode head,int point){
    char line[1000],ch;
    char delim[2]=" ";
    char *token;
    int i=0;
    FILE *fr=fopen("invertedIndex.txt","r");
    while((ch=fgetc(fr))!=EOF){

        if(ch!='\n'){
            line[i]=ch;
            i++;
        }
        if(ch=='\n') {
            line[i] = '\0';
            i=0;
            token = strtok(line, delim);
            if (token != NULL) {
                if (strcmp(token, input) == 0) {
                    token = strtok(NULL, delim);
                    while (token != NULL) {
                        //printf("%s,",token);
                        if (inPRnode(head, token)) {
                            point = insertToken(pages, token, point, head);
                        }
                        token = strtok(NULL, delim);  //token == "urlxx"
                        // printf("%s,%d,%.7f\n",
                        //       pages[point - 1].url, pages[point - 1].count, pages[point - 1].result);
                    }
                    //printf("\n");
                }
            }
        }
    }
    fclose(fr);
    return point;
}



/*
 //can not use in vlab env  as for each line it will read an extra symbol
int readIndex(char *input,Page pages[],PRnode head,int point){
    char line[1000];
    char delim[2]=" ";
    char *token;
    FILE *fr=fopen("invertedIndex.txt","r");
    while(fgets(line,1000,fr)!=NULL){
        line[strlen(line)-1]='\0';
        token=strtok(line,delim);
        if(token!=NULL) {
            if (strcmp(token, input) == 0) {
                token = strtok(NULL, delim);
                while (token != NULL) {
                    //printf("%s,",token);
                    if(inPRnode(head,token)){
                        point = insertToken(pages, token, point, head);
                    }
                    token = strtok(NULL, delim);  //token == "urlxx"
                   // printf("%s,%d,%.7f\n",
                    //       pages[point - 1].url, pages[point - 1].count, pages[point - 1].result);
                }
                //printf("\n");
            }
        }
    }
    fclose(fr);
    return point;
}

 */