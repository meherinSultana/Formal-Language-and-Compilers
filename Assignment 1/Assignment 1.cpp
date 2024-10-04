#include <stdio.h>
#include <stdbool.h>

int main(void)
{
    FILE *p1,*p2;
    char c;
    p1 = fopen("input1.c", "r");
    p2 = fopen("output.txt","w");

    if(!p1)
        printf ("\nFile can't be opened!");

    else
    {
        bool flag1 = false;
        bool flag2 = false;
        bool flag3 = false;

        while((c = fgetc(p1)) != EOF)
        {
            if(c!=' ')
            {
                flag3 = false;
            }

            if(c=='/')
            {
                if(((c = fgetc(p1)) != EOF))
                {
                    if(c=='/')
                    {
                        flag1 = true;
                    }
                    if(c=='*')
                    {
                        flag2 = true;
                    }
                }
            }
            else if(c!='\n' && c!='\t' && flag1 == false && flag2 == false && flag3 == false)
            {
                fputc(c, p2);
            }
            else if(flag1==true && c=='\n')
            {
                flag1=false;
            }
            else if(flag2==true && c=='*')
            {
                if((c = fgetc(p1)) != EOF && c=='/')
                {
                    flag2=false;
                }
            }
            if(c==' ' && flag3 == false)
            {
                flag3=true;
            }
        }
    }

    fclose(p1);
    fclose(p2);

    printf ("Input :\n\n");
    p1 = fopen("input1.c", "r");
    while ((c = fgetc(p1)) != EOF)
        printf("%c",c);

    fclose(p1);

    printf("\nOutput :\n\n");

    p2 = fopen("output.txt","r");

    while((c=fgetc(p2))!=EOF)
        printf("%c",c);

    printf("\n");
    fclose(p2);
    return 0;
}
