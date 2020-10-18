#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "parser.tab.h"
FILE* fptr;

// returns 0 when the file is completely read
int get_next_token()
{
    char s[1002], c;
    int len = 0;

    while(1)
    {
        c = getc(fptr);

        if(c == ' ' || c == '\n' || c == EOF)
        {
            if(len == 0) // we only have this character
            {
                if(c == EOF)
                    return 0;

                // we can print it
                printf("%c",c);
                return 1;
            }
            else
            {
            // add NULL termination at the end so that strcmp will know the ending of our array
             s[len] = '\0'; 

             if(strcmp(s,"var") == 0) // the last word is var
                printf("VAR");
             else if(strcmp(s,"integer") == 0)
                printf("INT");
             else if(strcmp(s,"is") == 0)
                printf("IS");
             else if(len > 0)// it means it is some identifier (if there's misplacment the grammar will discover it :D )
                printf("IDENT");
            // now we need to put the pointer exactly after the word (undo last step to reread ONLY the 'non letter or underscore')
             ungetc(c, fptr);
            //reset the char array
             memset(s, 0, sizeof(s));
             len = 0;
             return 1;
            }
        }
        else if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_') // reading some name
        {
            s[len++] = c;
        }
        else
        {
            printf("%s + Unknown symbol! ", s);
            //reset the char array
            memset(s, 0, sizeof(s));
            len = 0;
            // stop everything 
            return 0;
        }    
    }
}
int main()
{
    fptr = fopen("input.txt", "r+");

    while(get_next_token() != 0);

    int x = yyparse();

    printf("\n%d", x);

    return 0;
}