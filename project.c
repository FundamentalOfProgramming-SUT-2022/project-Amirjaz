//Amir Jazayeri
//401105786


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

//#define MAXL 10000;
//#define MAXC 20;
void errors(int n);
void inpstr(char x, char str[]);
void bugslash(char str[]);
void createfile(char str[]);
void cat(char inp[]);
void insert(char file[],char str[], int line,int pos);


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
    }



void errors(int n)
{
    if(n==1)
    {
        printf("This file does not exists");
        return;
    }
    if(n==2)
    {
        printf("This file already exists");
        return;
    }
    if(n==3)
    {
        printf("Invalid command");
        return;
    }
    if(n==4)
    {
        printf("This position does not exists!");
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
