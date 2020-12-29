#include<iostream>
#include<fstream>
#include<string>

// I know that global variables are often bad. Forgive me I wanna just explain the idea ((
std::ifstream fin;

std::string get_next_token()
{
    std::string s;
    char c;

    while (true)
    {
        // could be done better but organized it like this to edit only assignments and returns when using Bison API
        if (!fin.eof())
            fin.get(c);// get one character
        else
            return "";

        if (c == ' ' || c == '\n' || fin.eof())
        {
            if (s.empty()) // we only have this character
            {
                if (fin.eof())
                    return "";
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
                    return s;
                if (s == "integer")
                    return s;
                if (s == "is")
                    return s;
                if (!s.empty())// it means it is some identifier name
                    return  "Identifier";
            }
        }
        else if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_') // reading some name
        {
            s += c; // add the char to the string
        }
        else
        {
            // we don't know what's that
            return "ERROR";
        }
    }
}
int main()
{

    fin.open("input.txt");
    std::string temp = get_next_token();
    while (!temp.empty())
    {
        // printing a space since our example is only one line for now
        std::cout << temp << " ";
        temp = get_next_token();

    }
    return 0;
}