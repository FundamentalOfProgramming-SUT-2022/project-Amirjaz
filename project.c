//Amir Jazayeri
//401105786


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdbool.h>
#include <dirent.h>

//#define MAXL 10000;
//#define MAXC 20;
void errors(int n);
void inpstr(char x, char str[]);
void bugslash(char str[]);
void simultecopy(char file[]);
void createfile(char str[]);
void cat(char inp[]);
void insert(char file[],char str[], int line,int pos);
void removestr(char file[],int line, int pos,int length, char option);
void copystr(char file[],int line, int pos,int length, char option);
void cutstr(char file[],int line, int pos,int length, char option);
void pastestr(char file[],int line, int pos);
void tree(char *file, int curdepth, int depth);

char clipboard[10000]={'\0'};

int main()
{
    char command[62],inp[1000];
    scanf("%s", &command);
    if(!(strcmp(command,"exit")))
    {
        return 0;
    }
    else if(!(strcmp(command, "creatfile")))
    {
        getchar();
        scanf("%s",inp);
        char str[10000];
        gets(str);
        createfile(str);
        printf("done");
    }
    else if(!(strcmp(command,"cat")))
    {
        getchar();
        scanf("%s",inp);
        getchar();
        char str[10000];
        gets(str);
        cat(str);
    }
    else if(!(strcmp(command,"insertstr")))
    {
        getchar();
        scanf("%s",inp);
        getchar();
        char file[10000];
        char x = getchar();
        if(x == '"') {
            getchar();
            scanf("%[^\"]s",file);
            getchar();
            }
        else if(x == '/') scanf("%s",file);
        getchar();
        scanf("%s",file);
        getchar();
        char str[10000] = {};
        x = getchar();
        inpstr(x, str);
        scanf("%s",inp);
        int line, pos;
        scanf(" %d:%d",&line ,&pos);
        insert(file,str,line,pos);
        }
    else if(!(strcmp(command,"removestr")))
    {
        getchar();
        scanf("%s",inp);
        getchar();
        char x = getchar();
        char file[10000];
        if(x == '"') {
            getchar();
            scanf("%[^\"]s",file);
            getchar();
        }
        else if(x == '/') {scanf("%s",file);}
        getchar();
        scanf("%s",inp);
        int line, pos;
        scanf(" %d:%d ", &line, &pos);
        scanf("%s",inp);
        int length;
        char option;
        scanf(" %d -%c", &length, &option);
        removestr(file, line, pos, length, option);
    }
     else if (!(strcmp(command, "copystr")))
        {
            getchar();
            scanf("%s", inp);
            getchar();
            char y = getchar();
            char file[10000];
            if (y == '"')
            {
                getchar();
                scanf("%[^\"]s", file);
                getchar();
            }
            else if (y== '/')
                scanf("%s", file);
            getchar();
            scanf("%s", inp);
            int line, pos;
            scanf(" %d:%d ", &line, &pos);
            scanf("%s", inp);
            int length;
            char option;
            scanf(" %d -%c", &length, &option);
            copystr(file, line, pos, length, option);
        }

        else if (!(strcmp(command, "cutstr")))
        {
            getchar();
            scanf("%s", inp);
            getchar();
            char y = getchar();
            char file[10000];
            if (y == '"')
            {
                getchar();
                scanf("%[^\"]s", file);
                getchar();
            }
            else if (y== '/')
                scanf("%s", file);
            getchar();
            scanf("%s", inp);
            int line, pos;
            scanf(" %d:%d ", &line, &pos);
            scanf("%s", inp);
            int length;
            char option;
            scanf(" %d -%c", &length, &option);
            cutstr(file, line, pos, length, option);
        }

        else if (!(strcmp(command, "pastestr")))
        {
            getchar();
            scanf("%s", inp);
            getchar();
            char y = getchar();
            char file[10000];
            if (y == '"')
            {
                getchar();
                scanf("%[^\"]s", file);
                getchar();
            }
            else if (y== '/')
                scanf("%s", file);
            getchar();
            scanf("%s", inp);
            int line, pos;
            scanf(" %d:%d", &line, &pos);
            pastestr(file, line, pos);
        }
        else if(!(strcmp(command, "tree")))
        {
            int depth = 0;
            for(int i = 5; inp[i] != ' ' && inp[i] != '\0'; i++)
            {
                depth *= 10;
                depth += (inp[i] - '0');
            }
            if(inp[5] == '-')
            {
                depth = 1000;
            }
            tree("./root",0, depth);
        }
        else
        {
            printf("Invalid Command!");
        }
}



void errors(int n)
{
    if(n==1)
    {
        printf("This file does not exists");
        return;
    }
    else if(n==2)
    {
        printf("This file already exists");
        return;
    }
    else if(n==3)
    {
        printf("Invalid command");
        return;
    }
    else if(n==4)
    {
        printf("This position does not exists!");
        return;
    }
    else if(n==5)
    {
        printf("There isn't enough characters to remove");
        return;
    }
    else if(n==6)
    {
        printf("Invalid Option!");
        return;
    }
    else if(n==7)
    {
        printf("There isn't enough characters to copy");
        return;
    }
    else if(n==8)
    {
        printf("There isn't enough characters to cut");
        return;
    }
}


void bugslash(char str[])
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == '\\')
        {
            if (str[i + 1] == 'n')
            {
                str[i] = '\n';
                memmove(&str[i + 1], &str[i + 2], strlen(str) - i - 1);
            }
            else if (str[i + 1] == '\\')
            {
                str[i] = '\\';
                memmove(&str[i + 1], &str[i + 2], strlen(str) - i - 1);
            }
            else if (str[i + 1] == '\n')
            {
                str[i] = '"';
                memmove(&str[i + 1], &str[i + 2], strlen(str) - i - 1);
            }
        }
    }
}

void inpstr(char x, char str[])
{
    if (x == '"')
    {
        int n;
        int i = 0;
        x = getchar();
        while (x != '"')
        {
            n = x;
            str[i] = x;
            str[i + 1] = '\0';
            i++;
            x = getchar();
            if (x == '"' && n == '\\')
            {
                x = '\n';
            }
        }
        bugslash(str);
    }
    else
    {
        char str2[1000];
        scanf("%s", str2);
        str[0] = x;
        strcat(str, str2);
    }
    getchar();
}
void simultecopy(char file[])
{
    FILE *newfile;
    FILE *cpy;
    newfile = fopen(file,"r");
    char y;int i=0;char tmp[10000],filecopy[10000]="Random Bullshit";
    while(1)
    {
        y= fgetc(newfile);
        if(y==EOF){break;}
        tmp[i]=y;
        i++;
        tmp[i]='\0';
    }
    strcat(filecopy,file);
    if(fopen(filecopy + 1,"r")==0){createfile(filecopy);}
    cpy = fopen(filecopy + 1,"w");
    fprintf(cpy,"%s",tmp);
    fclose(cpy);
    fclose(newfile);
}

void createfile(char str[])
{
    int x= strlen(str);
    FILE *newfile;
    char tmp[10000];int count;
    if(str[0] = '/'){count=1;}
    else if(str[0] = '"'){count=2;}
    int i=0;
    while(i<x)
    {

        if(str[i]=='/')
        {
            mkdir(tmp);
        }
        if(str[i]!='"')
        {
            tmp[i-count]=str[i];
            tmp[i-count+1]='\0';
        }
        i++;
    }
    if(fopen(newfile,"r")==0)
    {
        fopen(newfile,"w");
        fclose(newfile);
    }
    else
    {
        errors(2);
    }
}


void cat(char inp[])
{
    if(inp[0] == '"'){
        inp[strlen(inp) - 1] = '\0';
        memmove(&inp[0], &inp[2], strlen(inp) - 1);
    }
    else if(inp[0] == '/'){
        memmove(&inp[0], &inp[1], strlen(inp));
    }
    if(fopen(inp,"r") == 0){
        errors(1);
        return;
    }
    FILE *file;
    file = fopen(inp,"r");
    char x;
    int i = 0;
    char filedata[10000];
    while(1){
        x = fgetc(file);
        if(x == EOF){ break;}
        filedata[i] = x;
        i++;
        filedata[i] = '\0';
    }
    fclose(file);
    puts(filedata);
}

void insert(char file[],char str[], int line,int pos)
{
    FILE *newfile;
    newfile= fopen(file,"r");
    if(newfile== NULL)
    {
        errors(1);return;
    }
    int i=1,j=0,x=0;char y;char ghablstr[10000],baadestr[10000];
    while (i!= line || j!=pos)
    {
        y=fgetc(newfile);
        if(y==EOF){errors(4);fclose(newfile);return;}
        j++;
        ghablstr[x]=y;ghablstr[x+1]='\0';
        x++;
        if(y=='\n')
        {
            i++;pos=0;
        }
    }
    x=0;
    while(1)
    {
        y=fgetc(newfile);
        if(y==EOF){break;}
        baadestr[x]=y;baadestr[x+1]='\0';
        x++;
    }
    fclose(newfile);
    newfile=fopen(file,"r");
    fprintf("%s %s %s",ghablstr,str,baadestr);
    fclose(newfile);
}


void removestr(char file[],int line, int pos,int length, char option)
{
    FILE *newfile;
    if(fopen(file,"r")==0){errors(1);}
    newfile= fopen(file,"r");
    if(option=='f')
    {
        int i=1,j=0,z=0;char y;char tmp[10000];
        while (i!= line || j!=pos)
        {
            y=fgetc(newfile);
            if(y==EOF){errors(4);fclose(newfile);return;}
            j++;
            tmp[z]=y;tmp[z+1]='\0';
            z++;
            if(y=='\n')
            {
            i++;pos=0;
            }
        }
        int cot=0;
        while(cot<length)
        {
            y=fgetc(newfile);
            if(y==EOF)
            {
               errors(5);
               fclose(newfile);
            }
            cot++;
        }
        while(1)
        {
            y=fgetc(newfile);
            if(y==EOF){break;}
            tmp[z]=y;tmp[z+1]='\0';z++;
        }
        fclose(newfile);
        newfile=fopen(file,"w");
        fprintf(newfile,"%s",tmp);
        fclose(newfile);
    }
    else if(option=='b')
    {
     int i=1,j=0,z=0;char y;char tmp[10000];
        while (i!= line || j!=pos)
        {
            y=fgetc(newfile);
            if(y==EOF){errors(4);fclose(newfile);return;}
            j++;
            tmp[z]=y;tmp[z+1]='\0';
            z++;
            if(y=='\n')
            {
            i++;pos=0;
            }
        }
        tmp[strlen(tmp)-length]='\0';
        z-=length;
        while(1)
        {
            y=fgetc(newfile);
            if(y==EOF){break;}
            tmp[z]=y;tmp[z+1]='\0';z++;
        }
        fclose(newfile);
        newfile=fopen(file,"w");
        fprintf(newfile,"%s",tmp);
        fclose(newfile);
    }
    else{
        errors(6);
        fclose(newfile);
    }

}



void copystr(char file[],int line, int pos,int length, char option)
{
    FILE *newfile;
    if(fopen(file,"r")==0)
    {
        errors(1);
    }
    newfile=fopen(file,"r");
    if(option=='f')
    {
        int i=1,j=0,z=0;char y;char tmp[10000],copy[10000];
        while (i!= line || j!=pos)
        {
            y=fgetc(newfile);
            if(y==EOF){errors(4);fclose(newfile);return;}
            j++;
            tmp[z]=y;tmp[z+1]='\0';
            z++;
            if(y=='\n')
            {
            i++;pos=0;
            }
        }
        int cot=0;
        while(cot<length)
        {
           y= fgetc(newfile);
           if(y==EOF)
           {
               if(false)
               {
                  printf("Cannot be coppied!");
               }
               else{
                  printf("Cannot be cutted!");
                               }
               fclose(newfile);
               return;
           }
           copy[cot]=y;
           copy[cot+1]='\0';
           cot++;
        }
        fclose(newfile);
        clipboard[0]='\0';
        strcpy(clipboard,copy);
    }
        else if(option=='b')
        {
            int i=1,j=0,z=0;char y;char tmp[10000],copy[10000];
            while (i!= line || j!=pos)
            {
            y=fgetc(newfile);
            if(y==EOF){errors(4);fclose(newfile);return;}
            j++;
            tmp[z]=y;tmp[z+1]='\0';
            z++;
            if(y=='\n')
            {
            i++;pos=0;
            }
            }
        memmove(&copy[0],&copy[strlen(copy)-length],length);
        clipboard[0]='\0';
        fclose(newfile);
        }
    else{
        printf("Option is incorrect!");
        fclose(newfile);
    }
}

void cutstr(char file[],int line, int pos,int length, char option)
{
    simultecopy(file);
    copystr(file,line,pos,length,option);
    removestr(file,line,pos,length,option);
}


void pastestr(char file[],int line, int pos)
{
    simultecopy(file);
    insert(file,clipboard,line,pos);
}

void tree(char *file, int curdepth, int depth)
{
    if (depth == -1) {
        tree(file, curdepth, 1000);
        return;
    }
    if (curdepth> depth) return;
    char inp[1000];
    struct dirent *dp;
    DIR *dir = opendir(file);
    if (!dir) return;
    while ((dp = readdir(dir)) != NULL) {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0) {
            printf("|");
            for (int i = 0; i < curdepth; i++) {
                printf("--");
            }
            printf("%s\n", dp->d_name);
            strcpy(inp, file);
            strcat(inp, "/");
            strcat(inp, dp->d_name);
            tree(inp, curdepth + 1, depth);
        }
    }
    closedir(dir);
    return;
}

