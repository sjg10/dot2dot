#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <string>
#include "image.h"
using namespace std;

cv::Mat image_in_to_image_cannied(cv::Mat src)
{

    cv::Mat src_gray, detected_edges;
    int lowThreshold      = 50; //between 0 and 100 .. TODO: tweak
    int const ratio       = 3;
    int const kernel_size = 3;

    /// Convert the image to grayscale
    cv::cvtColor( src, src_gray, cv::COLOR_BGR2GRAY );

    /// Reduce noise with a kernel 3x3
    cv::blur( src_gray, detected_edges, cv::Size(3,3) );

    /// Canny detector
    cv::Canny( detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size );


  return detected_edges;
}


vector<vector<cv::Point>> image_cannied_to_image_contours(cv::Mat cannied)
{
    vector<vector<cv::Point>> contours;
    cv::findContours(cannied, contours, cv::RETR_LIST, cv::CHAIN_APPROX_TC89_L1, cv::Point(0, 0));
    return contours;
}

vector<vector<cv::Point>> image_contours_to_image_polygons(vector<vector<cv::Point>> contours)
{
    vector<vector<cv::Point>> polygons(contours.size());
    for( unsigned int i = 0; i < contours.size(); i++ )
    {
        double epsilon = 0.1 * cv::arcLength(contours[i], true); //TODO: is this an appropriate epsilon? Does it depend on dot limit?
        cv::approxPolyDP(contours[i], polygons[i], epsilon, false); //TODO: should this be close/open (true/false)
    }
    return polygons;
}

void debug_display_cannied(cv::Mat cannied)
{
    /// Display image
    cv::namedWindow( "Cannied Image", cv::WINDOW_AUTOSIZE );
    cv::imshow( "Cannied Image", cannied);
    /// Wait until user exit program by pressing a key
    cv::waitKey(0);
}

void debug_display_contours(cv::Mat src, vector<vector<cv::Point>> contours)
{
    /// Draw contours
    cv::Mat drawing = cv::Mat::ones(src.size(), CV_8UC3);
    cv::Scalar color = cv::Scalar(0xFF, 0xFF, 0xFF);
    for( unsigned int i = 0; i< contours.size(); i++ )
    {
        cv::drawContours(drawing, contours, i, color);
    }

    /// Show in a window
    cv::namedWindow( "Contours", CV_WINDOW_AUTOSIZE );
    cv::imshow( "Contours", drawing );
    /// Wait until user exit program by pressing a key
    cv::waitKey(0);
}

bool image_any_to_line(string input_filename)
{
    cv::Mat src, cannied;
    vector<vector<cv::Point>> contours, polygons;
    
    /// Load an image
    src = cv::imread(input_filename);

    if( src.empty() )
    {
        cout << "The image was empty!" << endl;
        return false;
    }

    //TODO: compile out debug when done
    cannied = image_in_to_image_cannied(src);
    debug_display_cannied(cannied);

    contours = image_cannied_to_image_contours(cannied);
    debug_display_contours(src, contours);

    polygons = image_contours_to_image_polygons(contours);
    debug_display_contours(src, polygons);

    //TODO: connect the polygons, produce image of corners, number them

    return true;
}
