//
// Created by flk on 20-7-1.
//
#include "src.h"
#include "circle.h"

void rotVectorToMatrix(Mat omMat,double *_R)
{
    cout << "[[omMat]]--- "<< omMat << endl;
    Mat R;
    Rodrigues(omMat,R);
    memcpy(_R,R.data,sizeof(double)*9);
    cout<<"*******"<<R<<endl;
}

void mergeImg(Mat & dst,Mat &src1,Mat &src2)
{
    int rows = src1.rows+5;//+src2.rows
    int cols = src1.cols+5+src2.cols;//
    CV_Assert(src1.type () == src2.type ());
    dst.create (rows,cols,src1.type ());
    src1.copyTo (dst(Rect(0,0,src1.cols,src1.rows)));
    src2.copyTo (dst(Rect(src1.cols+5,0,src2.cols,src2.rows)));
}

void shicha(Mat left_img, Mat right_img) {


//    left_img = imread("/home/flk/桌面/yds/1.jpg",1);
//    right_img = imread("/home/flk/桌面/yds/2.jpg",1);

    Mat *p_left_img = &left_img;
    Mat *p_right_img = &right_img;
//    imshow("left", left_img);
//    waitKey(0);
//    imshow("right", right_img);
//    waitKey(0);

//    cout<<left_img.size<<endl<<left_img.cols<<left_img.rows<<endl;
//
    Mat left_disp = Mat::zeros(left_img.rows, left_img.cols, 0);
    Mat *p_left_disp = &left_disp;
//    cout << left_disp.size << endl;

//    //  BM方法
//    CvStereoBMState *BMState = cvCreateStereoBMState();
//
//    int SADWindowSize=15;
//    BMState->SADWindowSize = SADWindowSize > 0 ? SADWindowSize : 9;
//    BMState->minDisparity = 0;
//    BMState->numberOfDisparities = 32;
//    BMState->textureThreshold = 10;
//    BMState->uniquenessRatio = 15;
//    BMState->speckleWindowSize = 100;
//    BMState->speckleRange = 32;
//    BMState->disp12MaxDiff = 1;
//    cvFindStereoCorrespondenceBM( p_left_img, p_right_img, p_left_disp,BMState);
//   // cvNormalize( left_disp_, left_vdisp, 0, 256, CV_MINMAX );

    Mat vdisp, img1r_left, map11_left, map12_left, img1r_right, map11_right, map12_right;
    cv::Ptr<cv::StereoSGBM> stereo = cv::StereoSGBM::create(
            -64, 128, 11, 100, 1000, 32, 0, 15, 1000, 16, cv::StereoSGBM::MODE_HH);// -64, 128, 11, 100, 1000, 32, 0, 15, 1000, 16, cv::StereoSGBM::MODE_HH

//    cv::remap(left_img, img1r_left, map11_left, map12_left, cv::INTER_LINEAR);
//    cv::remap(left_img, img1r_right, map11_right, map12_right, cv::INTER_LINEAR);

    stereo->compute(left_img, right_img, left_disp);

//    cout << "left_disp" << left_disp << endl << "left_disp.size" << left_disp.size << endl;

    cv::normalize(left_disp, vdisp, 0, 256, cv::NORM_MINMAX, CV_8U);

    //   cout << "vdisp" << vdisp << endl << "vdisp.size" << vdisp.size << endl;

    imshow("left_disp", vdisp);
    waitKey(10);
}

bool ReadImage(Mat &left_frame, Mat &right_frame,int i)
{
    // 读取Usb相机视频
//    VideoCapture capture1(2);
//    VideoCapture capture2(1);

    sprintf(str, "/home/flk/桌面/yds/data/left7/left_%d.jpg", i);
    sprintf(str2, "/home/flk/桌面/yds/data/right7/right_%d.jpg", i);
    // 从USB相机中抓取图像帧
//  capture2.read(right_frame_r);
//  capture1.read(left_frame_r);
//  cvtColor(right_frame_r,right_frame,CV_BGR2GRAY);
//  cvtColor(left_frame_r,left_frame,CV_BGR2GRAY);

    left_frame = imread(str, 0);
    right_frame = imread(str2, 0);

    if (left_frame.empty()) {
        cout << "left_frame is empty" << endl;
        return false;
    }
    if(right_frame.empty()) {
        cout << "right_frame is empty" << endl;
        return false;
    }
    //将左右目图片放到一起显示
//        mergeImg(output, left_frame, right_frame);
//        imshow("video", output);
//        waitKey(10);
//        waitKey(0);
//        imshow("right",right_frame);
//        waitKey(0);
//        waitKey(30);
    return true;

}








