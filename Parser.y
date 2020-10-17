%require "3.2"
%define api.pure full

%code requires
{
    // note that these are imported before parser.tab.h in the generated C file 
    // so you might not need it (in my case I don't but just to clarify)
}
%code
{
    // note that this is added after including parser.tab.h 

    #include<stdio.h>
    void yyerror(const char *error);
    int yylex(YYSTYPE *lvalp);
}


%union {
    // put all the types you want to use here with any identical name
    // then in types section put its name such as 'st' below
    char st[1002];
}

%token IDENT VAR INT IS

%type<st> IDENT

%% 
VariableDeclaration: VAR IDENT IS INT {
    /* this is called an action*/
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
	return YYEOF;
}