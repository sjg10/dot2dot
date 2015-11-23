#include <iostream>
#include <string>
#include <stdexcept>
#include "input_parse.h"
using namespace std;

void print_usage(string program_name)
{
    cerr << "Usage: "
         << program_name
         << " [-l dot_limit]"
         << " input_file"
         << endl;
}

bool parse_input(InputContext * input_context, int argc, char ** argv)
{
    string temp;
    char * filename = NULL;
    int dot_limit = 0;

    bool retval = false;
    for (int i = 1; i < argc; i++)
    {
        temp = string(argv[i]);
        if (temp == "-l")
        {
            i++;
            if (i < argc)
            {
                try
                {
                    dot_limit = stoi(string(argv[i]));
                }
                catch (const invalid_argument& ia) 
                {
                    cerr << "Invalid dot limit argument: " << argv[i] << " is NaN." << endl;
                    retval = false;
                    break;
                }
            }
            else
            {
                retval = false;
                break;
            }
        }
        else
        {
            if (filename == NULL)
            {
                filename = argv[i];
                retval = true;
            }
            else
            {
                retval = false;
                break;
            }
        }
    }
    if (retval)
    {
        fstream * f = new fstream();
        f->open(filename, fstream::in);
        if (!f->is_open())
        {
            cerr << "File " << filename << " does not exist." << endl;
            retval = false;
        }
        else
        {
            *input_context = InputContext(f, dot_limit);
        }
    }
    else
    {
        print_usage(argv[0]);
    }
    return retval;
}
