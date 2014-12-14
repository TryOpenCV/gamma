#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/nonfree/features2d.hpp>
#include <opencv2/legacy/legacy.hpp>
#include "opencv2/nonfree/nonfree.hpp"

using namespace std;
using namespace cv;

void cv_Gamma(IplImage* src, IplImage* dst, double gamma){

    int i;
    uchar LUT[256];
    for (i = 0; i < 256; i++)
    {
        LUT[i] = (int)(pow((double)i / 255.0, 1.0 / gamma) * 255.0);
    }

    CvMat lut_mat = cvMat(1, 256, CV_8UC1, LUT);
    cvLUT(src, dst, &lut_mat);
}

int main(int argc, const char* argv[])
{
    IplImage* src = cvLoadImage(argv[1], CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_ANYCOLOR);
    if (src == NULL){
        return 0;
    }

    cvNamedWindow("src");
    cvNamedWindow("dst");

    IplImage* dst = cvCreateImage(cvGetSize(src), src->depth, src->nChannels);


    cv_Gamma(src, dst, 2.0);

    cvShowImage ("src", src);
    cvShowImage ("dst", dst);

    cvWaitKey (0);
    cvDestroyAllWindows();

    cvReleaseImage(&src);
    cvReleaseImage(&dst);

    return 0;
}
