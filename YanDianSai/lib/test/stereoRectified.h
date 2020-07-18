#ifndef stereoRectified_H
#define stereoRectified_H

#include "cv.h"
#include "highgui.h"
#include <iostream>
#include "cv.h"
#include <opencv2/imgproc.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

//     双目相机平移向量
//double _T[3] = {-106.6355, 12.1477, 22.1561};   //用640分辨率之前的的相机标定参数

//double _T[3] = {0, 0, 0};
double T_[3] = {-98.7024, -3.7097, 14.8240};   // small_2的相机参数


//	double _R[9] = {0.9990,-0.0122,0.0427,
//                    0.0102,0.9989,0.0467,
//                    -0.0432,-0.0463,0.9980};
//      双目相机旋转向量
//double _R[9] = {1, 0, 0,
//                0, 1, 0,
//                0, 0, 1
//};
double R_[9] = {0.9990,-0.0099,-0.0092,
                0.0102,0.9995,0.0314,    // small_2的相机参数
                0.0089,-0.0315,0.9995};


//double _R[9] = {0.9987, -0.0110, 0.0503,//用640分辨率之前的的相机标定参数
//                0.0112, 0.9999, -0.0050,
//                -0.0503, 0.0055, 0.9987
//
//};

//      相机内参
//double _camMatrixLeft[9] = {993.859, 0, 501.8442,//用640分辨率之前的的相机标定参数
//                            0, 995.7985, 388.8382,
//                            0, 0, 1};
double camMatrixLeft_[9] = {614.0770, 0, 317.8487,// small_2的相机参数
                            0, 614.0770, 243.0592,
                            0, 0, 1};


//double _camMatrixRight[9] = {984.2425, 0, 478.9360,//用640分辨率之前的的相机标定参数
//                             0, 988.6344, 393.1457,
//                             0, 0, 1};

double camMatrixRight_[9] = {616.5016, 0, 304.7407,/// small_2的相机参数
                             0, 616.5016, 244.5297,
                             0, 0, 1};

//      相机畸变参数
//double _distCoeffLeft[4] = {-0.4127, 0.1722, 0, 0};   //用640分辨率之前的的相机标定参数
//double _distCoeffRight[4] = {-0.4038, 0.1574, 0, 0};  //用640分辨率之前的的相机标定参数

double distCoeffLeft_[4] = {-0.4311, 0.2105, 0, 0};   // small_2的相机参数
double distCoeffRight_[4] = {-0.4234, 0.2093, 0, 0};  // small_2的相机参数

Mat leftRightMerge;


class StereoRetifier
{
public:
	Mat camMatrixLeft;
	Mat camMatrixRight;

	Mat distCoeffLeft;
	Mat distCoeffRight;

	Mat map1Left;
	Mat map1Right;
	Mat map2Left;
	Mat map2Right;

	Mat R;
	Mat T;
	Mat Q;
	Mat RectRotLeft;
	Mat RectRotRight;

	Mat newCamMatrixLeft;
	Mat newCamMatrixRight;

	Rect ROILeft;
	Rect ROIRight;

	StereoRetifier(double* _camMatrixLeft,double* _camMatrixRight, double *_distCoeffLeft, double *_distCoeffRight, double *_R,double *_T);
	//StereoRetifier(float* _camMatrixLeft,float* _camMatrixRight, float *_distCoeffLeft, float *_distCoeffRight);
	~StereoRetifier();
	void init(int width ,int height);
	void process(Mat leftRaw, Mat rightRaw, Mat &left ,Mat &right);
};

bool Retif(Mat &leftRaw, Mat &rightRaw, Mat &leftRectified, Mat &rightRectified, Mat &leftRightMerge, bool retif);


#endif