#include "cv.h"
#include <iostream>
#include "highgui.h"
#include "stereoRectified.h"
#include <string.h>
#include "circle.h"
#include "src.h"
#include <opencv2/highgui.hpp>
#include <fstream>

int main()
{
    // 读取Usb相机视频
    Mat left_frame, right_frame;
    int i=1;
    double distance=0, disparity=0;

    vector<Vec3f> left_circle_batch, right_circle_batch;
    Vec3f left_circle, right_circle;

    bool begain = true;
    bool haveimg;
    ofstream in_disparity, in_distance;
    while(begain)
    {
        //读取图像
        haveimg=ReadImage(left_frame, right_frame, i);
        if(i==1)
        {
            in_disparity.open("disparity_retif.txt", ios::trunc);  //打开文件，打开前将文件清空，若不存在则新建文件
            in_distance.open("distance_retif.txt", ios::trunc);
        }
        in_disparity<<disparity<<"\n";
        in_distance<<distance<<"\n";

        if (haveimg== false)
        {
            cout<<"image load finished"<<endl;
            in_disparity.close();
            in_distance.close();
            break;
        }

        Mat leftRectified(left_frame.rows, left_frame.cols, CV_8UC1, Scalar(255));
        Mat rightRectified(left_frame.rows, left_frame.cols, CV_8UC1, Scalar(255));

        //图像去畸变
        bool isRetif=Retif(left_frame,right_frame,leftRectified,rightRectified, leftRightMerge, true);

        //检测圆形
        detectCircle(leftRectified, left_circle_batch);
        detectCircle(rightRectified, right_circle_batch);

        bool isEmpty=circleFilter(left_circle_batch,right_circle_batch,left_circle,right_circle);
        if(isEmpty)
        {
            putText(left_frame,"cant find circle",textpoint,2,0.5,color,2);
            putText(right_frame,"cant find circle",textpoint,2,0.5,color,2);
            imshow("leftcircle",left_frame);
            imshow("rightcircle",left_frame);
        } else{
//          根据视差计算距离
            cout<<"left_circle[0]"<<left_circle[0]<<endl<<"right_circle[0]"<<right_circle[0]<<endl;
            disparity=abs(left_circle[0]-right_circle[0]);//视差
            distance=(618*98.6044)/disparity;//深度
            drawCircle(leftRectified,left_circle,"leftcircle",distance);
            drawCircle(rightRectified,right_circle,"rightcircle",distance);
        }
 //       shicha(leftRectified,rightRectified);

        i++;
   }
    return 0;
}






























