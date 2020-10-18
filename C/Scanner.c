#include<stdio.h>
#include<stdlib.h>
#include<string.h>
// include parser header so we can use the enums
#include "parser.tab.h"
FILE* fptr;

// returns 0 when the file is completely read
int get_next_token(YYSTYPE *lvalp)
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
                    return YYEOF;
                //otherwise return the next token because there's no enum for new lines or spaces
                return get_next_token(lvalp);
            }
            else
            {
            // add NULL termination at the end so that strcmp will know the ending of our array
             s[len] = '\0'; 

             if(strcmp(s,"var") == 0) // the last word is var
                return VAR;
             else if(strcmp(s,"integer") == 0)
                return INT;
             else if(strcmp(s,"is") == 0)
                return IS;
             else if(len > 0)// it means it is some identifier (if there's misplacment the grammar will discover it :D )
                {
                    // put the value and return the correct token
                    strcpy(lvalp->st, s);
                    return IDENT;
                }
            // now we need to put the pointer exactly after the word (undo last step to reread ONLY the 'non letter or underscore')
                ungetc(c, fptr);
            //reset the char array
             memset(s, 0, sizeof(s));
             len = 0;
             // go to the next one
             return get_next_token(lvalp);;
            }
        }
        else if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_') // reading some name
        {
            s[len++] = c;
        }
        else
        {
            //reset the char array
            memset(s, 0, sizeof(s));
            len = 0;
            // stop everything 
            return YYUNDEF;
        }    
    }
    return YYUNDEF;
}
int main()
{
    fptr = fopen("input.txt", "r+");

    int x = yyparse();

    printf("\n%d", x);

    return 0;
}