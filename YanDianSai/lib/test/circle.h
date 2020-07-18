//
// Created by flk on 20-7-1.
//

#ifndef TEST_CIRCLE_H
#define TEST_CIRCLE_H

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>
#include <string>

using namespace cv;
using namespace std;

const Point textpoint(60,60);
const Scalar color=Scalar(0,0,255);



//textpoint.x=20;
//textpoint.y=20;

void say_hello();
//过滤圆
bool circleFilter(vector<Vec3f> &left_circle_batch,vector<Vec3f> &right_circle_batch, Vec3f &left_circle, Vec3f &rigt_circle);
//检测圆
void detectCircle(Mat& img, vector<Vec3f> &circle_batch);

void drawCircle(Mat &img, Vec3f &circle_, string name, double distance);

void add(int & i);







#endif //TEST_CIRCLE_H




