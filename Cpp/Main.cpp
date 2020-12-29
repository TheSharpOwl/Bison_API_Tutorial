#include<iostream>
#include<fstream>
#include<string>
#include "parser.tab.hpp"
// I know that global variables are often bad. Forgive me I wanna just explain the idea ((
std::ifstream fin;

yy::parser::symbol_type get_next_token()
{
    std::string s;
    char c;
    while (true)
    {
        // could be done better but organized it like this to edit only assignments and returns when using Bison API
        if (!fin.eof())
            fin.get(c);// get one character
        else // return the end of the file so the parser will stop
            return yy::parser::make_YYEOF();

        if (c == ' ' || c == '\n' || fin.eof())
        {
            if (s.empty()) // we only have this character
            {
                if (fin.eof())
                    return yy::parser::make_YYEOF();
                    
                //otherwise go and see what's next
                return get_next_token();
            }
            else
            {
                if (!fin.eof())
                {
                   // now we need to put the pointer exactly after the word (undo the last step)
                   fin.unget();
                }

                if (s == "var") // the last word is var
                    return yy::parser::make_VAR();
                if (s == "integer")
                    return yy::parser::make_INT();
                if (s == "is")
                   return yy::parser::make_IS();
                if (!s.empty())// it means it is some identifier name 
                   return yy::parser::make_IDENT(s); // don't forget to pass the identifier name stored in the string
            }
        }
        else if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_') // reading some name
        {
            s += c; // add the char to the string
        }
        else
        {
            // we don't know what's that so return undefined token
            return yy::parser::make_YYUNDEF();
        }
    }
}
int main()
{
    fin.open("input.txt");
    yy::parser p;
	p.parse();
    return 0;
}

namespace yy
{
    parser::symbol_type yylex()
    {
        return get_next_token();
    }
}