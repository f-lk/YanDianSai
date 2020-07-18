//
// Created by flk on 20-7-1.
//

#include "circle.h"
//using namespace std;
//using namespace cv;

void say_hello()
{
    cout<<"hello, circle"<<endl;
}


void detectCircle(Mat& img, vector<Vec3f> &circle_batch)
{
    Mat img2;
    medianBlur(img, img2, 7);
    HoughCircles(img2,circle_batch,HOUGH_GRADIENT,1,200,300,25,0,50);
}

bool circleFilter(vector<Vec3f> &left_circle_batch,vector<Vec3f> &right_circle_batch, Vec3f &left_circle, Vec3f &rigt_circle)
{
    double score_all=0;
    int i_=0,j_=0;
    if(left_circle_batch.empty()||right_circle_batch.empty())
    {
        cout<<"Cannot find circle! "<<endl;
        return true;
    } else{
        for (int a=0; a<left_circle_batch.size(); a++)
        {
            for (int b=0; b<right_circle_batch.size(); b++)
            {
                double score=abs(left_circle_batch[a][1]-right_circle_batch[b][1])+2*abs(left_circle_batch[a][2]-right_circle_batch[b][2]);
                if(a==0&&b==0)
                {
                    score=score_all;
                }
                else if(score<score_all){
                    score_all=score;
                    i_=a;
                    j_=b;
                }
            }
        }
        left_circle=left_circle_batch[i_];
        rigt_circle=right_circle_batch[j_];
        return false;
    }
}


void drawCircle(Mat &img, Vec3f &circle_, string name, double distance)
{
    char str[256];
    Point2f center;
    center.x=circle_[0];
    center.y=circle_[1];
    cvtColor(img,img,COLOR_GRAY2BGR);
    circle(img,center,(int)circle_[2],color,1,LINE_8,0);
//    float a =center.x;
//    float b =center.y;
    sprintf(str,"x=%f, y=%f, Dis=%f", center.x,center.y, distance);
    putText(img,str,textpoint,2,0.5,color,2);
    imshow(name,img);
    waitKey(0);
}




//void drawCircle(Mat &img, Vec3f &left_circle, Vec3f &rigt_circle)
//{
//
//    if(left_circle)
//
//}

void add(int & i)
{
    i=i+1;
}

















//void circleFilter(left_circle_batch, right_circle_batch)
//{
//
//
//
//
//
//}
















