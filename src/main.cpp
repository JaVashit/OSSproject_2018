#include <stdio.h>
#include <stdlib.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
Mat img = imread("lena.png",CV_LOAD_IMAGE_COLOR);

for (int i = 0; i <img.size().height; i += 2) {
	for (int j = 0; j < img.size().width; j += 2) {
		int color = 0;
		for (int k = 0; k < 2; k++) {
			for (int l = 0; l < 2; l++) {
				if ((i + k) >= 0 && (j + l) < img.size().width) 
					color += (img.at<Vec3b>(i + k,j + l)[0] + img.at<Vec3b>(i + k, j + l)[1] + img.at<Vec3b>(i + k, j + l)[2])/3;
			}
		}
		int pixel = (color / (2 * 2));
		
		
		if (pixel >= 0 && pixel <= 25) printf("#");
		else if (pixel > 25 && pixel <= 50) printf("$");
		else if (pixel > 50 && pixel <= 75) printf("O");
		else if (pixel > 75 && pixel <= 100) printf("=");
		else if (pixel > 100 && pixel <= 125) printf("+");
		else if (pixel > 125 && pixel <= 150) printf("|");
		else if (pixel > 150 && pixel <= 175) printf("-");
		else if (pixel > 175 && pixel <= 200) printf("^");
		else if (pixel > 200 && pixel <= 225) printf(".");
		else if (pixel > 225 && pixel <= 255) printf(" ");

	}
	printf("\n");
}



imshow("image", img);
waitKey(0);

return 0;
}
