#ifndef INPUT_PARSE_H
#define INPUT_PARSE_H

#include <string>

class InputContext
{
    public:
        std::string input_filename;
        int dot_limit;
        InputContext  (std::string filename, int limit) : input_filename(filename), dot_limit(limit) {};
        InputContext  () : input_filename(""), dot_limit(0) {};
};


void print_usage(std::string program_name);
bool parse_input(InputContext * input_context, int argc, char ** argv);

#endif //INPUT_PARSE_H
