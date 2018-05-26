#include "stdafx.h"
#include "GUI.h"
#include "GUIDlg.h"
#include "afxdialogex.h"
#include "opencv2\highgui.hpp"
#include "CvvImage.h"	//화면출력에 필요

using namespace cv;
using namespace std;

void PrintAscii_img(CGUIDlg* pDlg, IplImage* ascii_img, Mat dst_img, string file_name);