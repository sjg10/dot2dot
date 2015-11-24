#include <iostream>
#include <string>
#include "input_parse.h"
#include "image.h"
using namespace std;

#define VERIFY_PTR(ptr) do {if(ptr == nullptr) {cout << "malloc failed at" << __FILE__ << " " << __LINE__;}} while(0)

static InputContext * g_input_context;

int main(int argc, char ** argv)
{
    int retval;
    bool valid_input;

    g_input_context = new InputContext();
    VERIFY_PTR(g_input_context);

    valid_input = parse_input(g_input_context, argc, argv);
    if(!valid_input)
    {
        retval = -1;
    }
    else
    {
        retval = image_any_to_line(g_input_context->input_filename);
        // TODO: then do contour search
        // approximate contours with lines
        // begin dot2dot-ification
    }
    //delete(g_input_context); //TODO: free cleanly...why wont it delete?
    return retval;
}
