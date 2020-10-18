%require "3.2"
%define api.pure full

%code requires
{
    // note that these are imported at the beginning of parser.tab.h in the generated C file 
    // so you might not need it (in my case I don't but just to clarify)
}
%code
{
    int yylex(YYSTYPE *lvalp);
    void yyerror(const char *error);

    int get_next_token(YYSTYPE *lvalp);

    // note that this is added after including parser.tab.h in parser.tab.c
    #include<stdio.h>
    #include<string.h>

    // TODO delete
    int temp = 1;
}

%token IDENT VAR INT IS


%union {
    // put all the types you want to use here with any identical name
    // then in types section put its name such as 'st' below
    char st[1002];
}

%type<st> IDENT

%%

VariableDeclaration: VAR IDENT IS INT {
    /* this is called a semantic action*/
     printf("defined a variable %s with type int\n", $2);
     }
;

%%

void yyerror(const char *error)
{
    printf("Syntax Error\n");
}

int yylex(YYSTYPE *lvalp)
{
    return get_next_token(lvalp);
}