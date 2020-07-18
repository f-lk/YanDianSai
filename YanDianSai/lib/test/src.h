//
// Created by flk on 20-7-1.
//

#ifndef TEST_SRC_H
#define TEST_SRC_H

#include "circle.h"

char str[100];
char str2[100];
void rotVectorToMatrix(Mat omMat,double *_R);
void mergeImg(Mat & dst,Mat &src1,Mat &src2);
void shicha(Mat left_img, Mat right_img);

bool ReadImage(Mat &left_frame, Mat &right_frame,int i);


#endif //TEST_SRC_H
