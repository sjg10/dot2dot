#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <string>
#include "image.h"
using namespace std;

bool image_any_to_line(string input_filename)
{
    
    cv::Mat src, src_gray;
    cv::Mat dst, detected_edges;

    int lowThreshold = 50; //between 0 and 100 .. TODO: tweak
    int ratio = 3;
    int kernel_size = 3;
    const char* window_name = "Edge Map";
 
    /// Load an image
    src = cv::imread(input_filename);

    if( src.empty() )
    {
        cout << "The image was empty!" << endl;
        return false;
    }

    /// Create a matrix of the same type and size as src (for dst)
    dst.create( src.size(), src.type() );

    /// Convert the image to grayscale
    cv::cvtColor( src, src_gray, cv::COLOR_BGR2GRAY );

    /// Create a window
    cv::namedWindow( window_name, cv::WINDOW_AUTOSIZE );
    /// Reduce noise with a kernel 3x3
    cv::blur( src_gray, detected_edges, cv::Size(3,3) );

    /// Canny detector
    cv::Canny( detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size );

    /// Using Canny's output as a mask, we display our result
    dst = cv::Scalar::all(0);

    src.copyTo( dst, detected_edges);
    cv::imshow( window_name, dst );

    /// Wait until user exit program by pressing a key
    cv::waitKey(0);
    //TODO: replace image show with saving image for next processing step

  return true;
}
