#include "stdafx.h"
#include "GUI.h"
#include "GUIDlg.h"
#include "afxdialogex.h"
#include "opencv2\highgui.hpp"

using namespace cv;
using namespace std;

void Pixelation_img(Mat input_img, IplImage* ascii_img2, IplImage* ascii_img3);
void Pixelation_vid(Mat frame, int pixel, char arr[], IplImage* IplImage_img, IplImage* IplImage_img2);