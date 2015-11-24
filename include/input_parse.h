#ifndef INPUT_PARSE_H
#define INPUT_PARSE_H

#include <fstream>
using namespace std;

class InputContext
{
    fstream * input_file;
    int dot_limit;
    
    public:
        InputContext  (fstream * file, int limit) : input_file(file), dot_limit(limit) {};
        InputContext  () : input_file(NULL), dot_limit(0) {};
        ~InputContext () {input_file->close();};
};


void print_usage(string program_name);
bool parse_input(InputContext * input_context, int argc, char ** argv);

#endif //INPUT_PARSE_H
