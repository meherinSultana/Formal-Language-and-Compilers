#include<stdio.h>
#include<string.h>

int tablei = 0;
struct sTable
{
    char name[20][20];
    char idType[20][20];
    char dataType[20][20];
    char scope[20][20];
    char value[20][20];
} sTable;

//insert a new entry into the symbol table
void insert(char n[], char iT[], char dT[], char scp[], char v[])
{
    strcpy(sTable.name[tablei],n);
    strcpy(sTable.idType[tablei],iT);
    strcpy(sTable.dataType[tablei],dT);
    strcpy(sTable.scope[tablei],scp);
    strcpy(sTable.value[tablei],v);
    tablei++;
}
//set the value of an identifier in the symbol table
void set_attribute(char n[], char scp[], char v[])
{
    int i;
    for(i=0; i<tablei; i++)
    {
        if(strcmp(sTable.name[i],n)==0 && strcmp(sTable.scope[i],scp)==0)
        {
            strcpy(sTable.value[i],v);
            break;
        }
    }
}
//attempts to free the memory for the name array in the symbol table
void frees()
{
    int i;
    for(i = 0 ; i<tablei ; i++)
    {
        free(sTable.name[i]);
    }
}
//searches for an identifier in the symbol table
int lookUp(char n[],char scp[])
{
    int i;
    for(i = 0; i<tablei; i++)
        if(strcmp(sTable.name[i],n)==0)
        {
            if(strcmp(sTable.idType[i],"func")==0)
            {
                return (i+1);
            }
            else if(strcmp(sTable.scope[i],scp)==0)
            {
                return (i+1);
            }
        }
}
//prints the contents of the symbol table
void display()
{
    printf("\nSl.No.\tName\tId Type\tData Type\tScope\tValue\n-------------------------------------------------------\n");
    for(int i = 0; i<tablei ; i++)
    {
        printf("%d\t|%s\t|%s\t|%s\t\t|%s\t|%s\n",(i+1),sTable.name[i],sTable.idType[i],sTable.dataType[i],sTable.scope[i],sTable.value[i]);
    }
}
int main()
{
    FILE *ptr,*ptr2;
    int inputi=0;
    char input[1500],c;
    char scp[20] = "global";
    int j;
    ptr = fopen("input.txt","r");
    printf("Input file:\n\n");
    while((c=getc(ptr))!=EOF)
    {
        printf("%c",c);
        input[inputi]=c;
        inputi++;
    }
    fclose(ptr);

    ptr2 = fopen("output.txt","w");
    printf("\n\n\nStep 1: Only identifiers are kept\n\n"); //extracts token and prints modified token stream

    for(int i = 0; i<inputi; i++)
    {
        if(input[i] == '[' && input[i+1]== 'i' && input[i+2]=='d' && input[i+3]==' ')
        {
            i+=4;
            j = 0;
            char id[20];
            while(input[i] != ']')
            {
                id[j] = input[i];
                i++;
                j++;
            }
            id[j] = '\0';
            printf("[id %s",id);
            fprintf(ptr2,"[id %s",id);

        }
        if(input[i]=='[')
        {
            printf("[");
            fputc('[',ptr2);
            while(input[i]!=' ')
                i++;
            i++;
        }

        printf("%c",input[i]);
        fputc(input[i],ptr2);
    }
    fclose(ptr2);

    for(int i=0; i<inputi; i++)
    {
        if(input[i] == 'k' && input[i+1] == 'w' && input[i+3]!='r')
        {
            char dT[20],n[20],v[20];
            j=0;
            i+=3;
            while(input[i]!=']')
            {
                dT[j] = input[i];
                j++;
                i++;
            }
            dT[j] = '\0';
            i+=3;
            if(input[i]=='i' && input[i+1] == 'd' && input[i+2] == ' ')
            {
                i+=3;
                j=0;
                while(input[i] !=']')
                {
                    n[j] = input[i];
                    i++;
                    j++;
                }
                n[j] = '\0';

                i+=3;

                if(input[i] == 's' || input[i] == 'o')
                {
                    if(input[i] == 's')
                        insert(n,"var",dT,scp," ");
                    else
                    {
                        i+=10;
                        j = 0;
                        while(input[i] != ']')
                        {
                            v[j] = input[i];
                            j++;
                            i++;
                        }
                        v[j] = '\0';
                        insert(n,"var",dT,scp,v);
                    }
                }
                else
                {
                    i+=4;
                    if(input[i]==')')
                        insert(n,"var",dT,scp," ");
                    else
                    {
                        insert(n,"func",dT,"global"," ");
                        strcpy(scp,n);
                    }
                }
            }
        }
        else if(input[i]=='[' && input[i+1]=='i' && input[i+2] == 'd' && input[i+3]== ' ')
        {
            char n[20],v[20];
            i+=4;
            j = 0;
            while(input[i] != ']')
            {
                n[j] = input[i];
                j++;
                i++;
            }
            n[j]='\0';
            i+=3;
            if(input[i]=='o' && input[i+7] == 'n')
            {
                i+=10;
                j=0;
                while(input[i] != ']')
                {
                    v[j] = input[i];
                    j++;
                    i++;
                }
                v[j] = '\0';
                set_attribute(n,scp,v);
            }
        }
        else if(input[i]=='}')
        {
            strcpy(scp,"global");
        }
    }
    printf("\n\n\nStep 2: Generated symbol table\n");
    display();
    strcpy(scp,"global");
    printf("\n\nStep 4: Modified token stream for Syntax Analysis \n\n");
    ptr2 = fopen("output2.txt","w");
    for(int i = 0; i<inputi; i++)
    {
        if(input[i] == '[' && input[i+1]== 'i' && input[i+2]=='d' && input[i+3]==' ')
        {
            i+=4;
            j = 0;
            char id[20];
            while(input[i] != ']')
            {
                id[j] = input[i];
                i++;
                j++;
            }
            id[j] = '\0';
            printf("[id %d",lookUp(id,scp));
            fprintf(ptr2,"[id %d",lookUp(id,scp));
            if(input[i+3]=='p' && input[i+7]=='(' && strcmp(scp,"global") == 0)
                strcpy(scp,id);
        }
        if(input[i]=='[')
        {
            printf("[");
            fputc('[',ptr2);
            while(input[i]!=' ')
                i++;
            i++;
        }
        if(input[i] == '}')
            strcpy(scp,"global");
        printf("%c",input[i]);
        fputc(input[i],ptr2);
    }
    fclose(ptr2);
    return 0;
}
