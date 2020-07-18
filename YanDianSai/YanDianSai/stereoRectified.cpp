#include "stereoRectified.h"

using namespace cv;

StereoRetifier::StereoRetifier(double* _camMatrixLeft,double* _camMatrixRight, double *_distCoeffLeft, double *_distCoeffRight, double *_R,double *_T)
{
	camMatrixLeft .create(3,3,CV_64FC1);
	camMatrixRight.create(3,3,CV_64FC1);

	distCoeffLeft.create(4,1,CV_64FC1);
	distCoeffRight.create(4,1,CV_64FC1);

	R.create(3,3,CV_64FC1);
	T.create(3,1,CV_64FC1);

	RectRotLeft .create(3,3,CV_64FC1);
	RectRotRight.create(3,3,CV_64FC1);

	newCamMatrixLeft .create(3,4,CV_64FC1);
	newCamMatrixRight.create(3,4,CV_64FC1);

	Q.create(4,4,CV_64FC1);

	memcpy(camMatrixLeft.data,_camMatrixLeft,sizeof(double)*3*3);
	memcpy(camMatrixRight.data,_camMatrixRight,sizeof(double)*3*3);

	memcpy(distCoeffLeft.data,_distCoeffLeft,sizeof(double)*4);
	memcpy(distCoeffRight.data,_distCoeffRight,sizeof(double)*4);

	memcpy(R.data,_R,3*3*sizeof(double));
	memcpy(T.data,_T,3*sizeof(double));

//	cout<<"R"<<R<<endl;
	//cout<<"T"<<T<<endl;
}

void StereoRetifier::process(Mat leftRaw, Mat rightRaw, Mat &left ,Mat &right)
{
	remap(leftRaw ,left ,map1Left,map2Left,INTER_LINEAR,0);
	remap(rightRaw,right,map1Right,map2Right,INTER_LINEAR,0);

//	int x1 = max(ROILeft.x,ROIRight.x);
//	int y1 = max(ROILeft.y,ROIRight.y);
//	int x2 = min(ROILeft.x+ROILeft.width,  ROIRight.x+ROIRight.width);
//	int y2 = min(ROILeft.y+ROILeft.height, ROIRight.y+ROIRight.height);
//
//	int width  = x1 - x2;  //x2-x1
//	int height = y1 - y2;  //y2-y1
//
//	left = left(Rect(x1,y1,width,height));
//	right = right(Rect(x1,y1,width,height));
	//rectangle(left,Point(ROILeft.x,ROILeft.y),Point(ROILeft.x+ROILeft.width,ROILeft.y+ROILeft.height),Scalar(255));
	//rectangle(right,Point(ROIRight.x,ROIRight.y),Point(ROIRight.x+ROIRight.width,ROIRight.y+ROIRight.height),Scalar(255));
	//imshow("crop",left_);
	//imshow("cropR",right_); waitKey();
}

void StereoRetifier::init(int width ,int height)
{
	stereoRectify(camMatrixLeft, distCoeffLeft, camMatrixRight, distCoeffRight,
		Size(width,height), R,T,RectRotLeft,RectRotRight,
		newCamMatrixLeft,newCamMatrixRight,Q,CALIB_ZERO_DISPARITY,
		0,Size(width,height),&ROILeft,&ROIRight);

	initUndistortRectifyMap(camMatrixLeft,distCoeffLeft,RectRotLeft,newCamMatrixLeft,Size(width,height),CV_16SC2,map1Left,map2Left);  //CV_32FC1

//	cout<<"rect rot left:"<<RectRotLeft<<endl;
//	cout<<"new cam left:" <<newCamMatrixLeft<<endl;
	initUndistortRectifyMap(camMatrixRight,distCoeffRight,RectRotRight,newCamMatrixRight,Size(width,height),CV_16SC2,map1Right,map2Right);
//	cout<<"rect rot right:"<<RectRotRight<<endl;
//	cout<<"new cam right:" <<newCamMatrixRight<<endl;
}

StereoRetifier::~StereoRetifier()
{

}

bool Retif(Mat &leftRaw, Mat &rightRaw, Mat &leftRectified, Mat &rightRectified, Mat &leftRightMerge, bool retif)
{
    if(retif == false)
    {
        leftRectified = leftRaw;
        rightRectified = rightRaw;
        return false;
    }

    //去畸变
    StereoRetifier stereoRectifier(camMatrixLeft_, camMatrixRight_, distCoeffLeft_, distCoeffRight_, R_, T_);
    stereoRectifier.init(leftRaw.cols, leftRaw.rows);
    stereoRectifier.process(leftRaw, rightRaw, leftRectified, rightRectified);
    leftRightMerge.create(2*leftRectified.rows, leftRectified.cols + rightRectified.cols, CV_8UC1);

    //去畸变后的图像拼接到一起
    leftRectified.copyTo(leftRightMerge(Rect(0, 0, leftRectified.cols, leftRectified.rows)));
    rightRectified.copyTo(leftRightMerge(Rect(leftRectified.cols, 0, rightRectified.cols, rightRectified.rows)));
    leftRaw.copyTo(leftRightMerge(Rect(0,leftRaw.rows,leftRaw.cols,leftRaw.rows)));
    rightRaw.copyTo(leftRightMerge(Rect(leftRectified.cols,leftRectified.rows,rightRaw.cols,rightRaw.rows)));

    //画平行线
    for (int a = 0; a < leftRightMerge.rows; a += 30) {
        line(leftRightMerge, Point(0, a), Point(leftRightMerge.cols - 1, a), Scalar(128), 1);
    }

    //          显示图像
    imshow("leftRightMerge", leftRightMerge);
    waitKey(5);

    return true;

}
