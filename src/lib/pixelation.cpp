#include "stdafx.h"
#include "GUI.h"
#include "GUIDlg.h"
#include "afxdialogex.h"
#include "opencv2\highgui.hpp"

using namespace cv;
using namespace std;

void Pixelation_img(Mat input_img, IplImage* ascii_img2, IplImage* ascii_img3) {

	//원본의 색을 저장하여 폰트의 색 결정
	Scalar color = 0;

	//각 픽셀이 폰트를 정할 때 사용하는 수치를 저장하기 위한 변수
	int insert_sum = 0;

	//출력에 사용될 단어
	char arr[17] = { '#','%','&','$','@','0','=','+','?','|','/','~','-','^','.','`',' ' };

	for (int i = 0; i <input_img.size().height; i += 1) {
		for (int j = 0; j < input_img.size().width; j += 1) {

			int color = 0;
			CvScalar ascii_color = 0;

			color += (input_img.at<Vec3b>(i, j)[0] + input_img.at<Vec3b>(i, j)[1]
				+ input_img.at<Vec3b>(i, j)[2]) / 3;
			ascii_color = input_img.at<Vec3b>(i, j);

			int pixel = (color / (2 * 2)); // Divide the calculated RGB mean value by the width of the square of size 2

			CvFont font;
			cvInitFont(&font, CV_FONT_HERSHEY_SIMPLEX, 0.6f, 0.6f, 0, 1, 8);
			char szText[2];

			if (pixel >= 0 && pixel <= 15) sprintf_s(szText, "%c", arr[0]);
			else if (pixel > 15 && pixel <= 30) sprintf_s(szText, "%c", arr[1]);
			else if (pixel > 30 && pixel <= 45) sprintf_s(szText, "%c", arr[2]);
			else if (pixel > 45 && pixel <= 60) sprintf_s(szText, "%c", arr[3]);
			else if (pixel > 60 && pixel <= 75) sprintf_s(szText, "%c", arr[4]);
			else if (pixel > 75 && pixel <= 90) sprintf_s(szText, "%c", arr[5]);
			else if (pixel > 90 && pixel <= 105) sprintf_s(szText, "%c", arr[6]);
			else if (pixel > 105 && pixel <= 120) sprintf_s(szText, "%c", arr[7]);
			else if (pixel > 120 && pixel <= 135) sprintf_s(szText, "%c", arr[8]);
			else if (pixel > 135 && pixel <= 150) sprintf_s(szText, "%c", arr[9]);
			else if (pixel > 150 && pixel <= 165) sprintf_s(szText, "%c", arr[10]);
			else if (pixel > 165 && pixel <= 180) sprintf_s(szText, "%c", arr[11]);
			else if (pixel > 180 && pixel <= 195) sprintf_s(szText, "%c", arr[12]);
			else if (pixel > 195 && pixel <= 210) sprintf_s(szText, "%c", arr[13]);
			else if (pixel > 210 && pixel <= 225) sprintf_s(szText, "%c", arr[14]);
			else if (pixel > 225 && pixel <= 240) sprintf_s(szText, "%c", arr[15]);
			else if (pixel > 240 && pixel <= 255) sprintf_s(szText, "%c", arr[16]);


			if (j % 10 == 0 && i % 5 == 0)
				cvPutText(ascii_img2, szText, cvPoint(j, i), &font, cvScalar(255, 255, 255));
			if (j % 14 == 0 && i % 18 == 0)
				cvPutText(ascii_img3, szText, cvPoint(j, i), &font, ascii_color);

		}

	}
}