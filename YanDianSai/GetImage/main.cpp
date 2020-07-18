#include <iostream>
#include <string>
#include <opencv2/video.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/highgui.hpp>
#include <thread>
#include "circle.h"
#include "src.h"
#include "stereoRectified.h"


using namespace cv;
using namespace std;

// 恩空格拍照片

Mat left_image_g, right_image_g, Merge, left_image_g_gray, right_image_g_gray;
Mat releft_image_g(480, 640,CV_8UC1,Scalar(255));
Mat reright_image_g(480,640,CV_8UC1,Scalar(255));


string a;
char str3[200];
char str4[200];
int i=0;
bool isinput;


bool waitinput(Mat &left_frame, Mat &right_frame)
{
    while(1)
    {
        sprintf(str3, "/home/flk/桌面/yds/data/left6/left_%d.png", i);
        sprintf(str4, "/home/flk/桌面/yds/data/right6/right_%d.png", i);
        a=cin.get();
        cout<<"frame"<<i<<endl;
        imwrite(str3,left_frame);
        imwrite(str4,right_frame);

        i++;

    }
}

int main() {
    VideoCapture capture1(2);
    VideoCapture capture2(0);
    thread first(waitinput, std::ref(releft_image_g), std::ref(reright_image_g));
    while (1)
    {
        capture1.read(left_image_g);
        capture2.read(right_image_g);

        if(left_image_g.empty() || right_image_g.empty())
        {
            cout<<"image is empty"<<endl;
            break;
        }

        cvtColor(left_image_g, left_image_g_gray, COLOR_BGR2GRAY);
        cvtColor(right_image_g, right_image_g_gray, COLOR_BGR2GRAY);

        Retif(left_image_g_gray, right_image_g_gray, releft_image_g, reright_image_g, Merge, false);

        imshow("left", left_image_g);
        waitKey(5);
        imshow("right", right_image_g);
        waitKey(5);


    }

    first.join();

    std::cout << "Hello, World!" << std::endl;
    return 0;
}
