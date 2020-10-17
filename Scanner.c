#include <stdio.h>
#include <stdlib.h>
#include<string.h>

int main()
{
   FILE* fptr;
   fptr = fopen("input.txt", "r");

   if(fptr == NULL)
   {
       printf("Error reading the file!\n");
       exit(1);
   }
   char c = ' ';
   char s[1002]; // let's suppose this length for a word is enough for now
   int len = 0;
   while(1)
   {
       c = fgetc(fptr);
        if(c == ' ' || c == '\n' || c == EOF) // if the word is finished
        {
            // add NULL termination at the end so that strcmp will know the ending of our array
            s[len] = '\0'; 

            if(strcmp(s,"var") == 0) // the last word is var
                printf("VAR");
            else if(strcmp(s,"integer") == 0)
                printf("INT");
            else if(strcmp(s,"is") == 0)
                printf("IS");
            else if(len > 0)// it means it is some identifier (we don't care about misplacment for now)
                printf("IDENT");

            if(c != EOF)
                printf("%c",c);
            else
                break;
            //reset the char array
            memset(s, 0, sizeof(s));
            len = 0;

        }
        // if we have a letter then add it until we get to case 1 (space or new line)
        else if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) 
        {
            s[len++] = c;
        }
        else
        {
            // we won't stop if we find, just warn the user about it (we have a use of this in the next stage)
            printf("%s + Unknown symbol! ", s);
            //reset the char array
            memset(s, 0, sizeof(s));
            len = 0;
        }    
   }

   fclose(fptr);
   printf("\n");
    return 0;
}