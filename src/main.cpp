#include <stdio.h>
#include <stdlib.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
Mat img = imread("lena.png",CV_LOAD_IMAGE_COLOR); // Import image

for (int i = 0; i <img.size().height; i += 2) {
	for (int j = 0; j < img.size().width; j += 2) {
		int color = 0;
		// Divide the image by a square of size 2 and calculate the RGB average within it
		for (int k = 0; k < 2; k++) { 
			for (int l = 0; l < 2; l++) {
				if ((i + k) >= 0 && (j + l) < img.size().width) 
					color += (img.at<Vec3b>(i + k,j + l)[0] + img.at<Vec3b>(i + k, j + l)[1] + img.at<Vec3b>(i + k, j + l)[2])/3;
			}
		}
		int pixel = (color / (2 * 2)); // Divide the calculated RGB mean value by the width of the square of size 2
		
		if (pixel >= 0 && pixel <= 15) cout << "#";
		else if (pixel > 15 && pixel <= 30) cout << "%";
		else if (pixel > 30 && pixel <= 45) cout << "&";
		else if (pixel > 45 && pixel <= 60) cout << "$";
		else if (pixel > 60 && pixel <= 75) cout << "@";
		else if (pixel > 75 && pixel <= 90) cout << "0";
		else if (pixel > 90 && pixel <= 105) cout << "=";
		else if (pixel > 105 && pixel <= 120) cout << "+";
		else if (pixel > 120 && pixel <= 135) cout << "?";
		else if (pixel > 135 && pixel <= 150) cout << "|";
		else if (pixel > 150 && pixel <= 165) cout << "/";
		else if (pixel > 165 && pixel <= 180) cout << "~";
		else if (pixel > 180 && pixel <= 195) cout << "-";
		else if (pixel > 195 && pixel <= 210) cout << "^";
		else if (pixel > 210 && pixel <= 225) cout << ".";
		else if (pixel > 225 && pixel <= 240) cout << "`";
		else if (pixel > 240 && pixel <= 255) cout << " ";
		
	}
	cout << "\n";
}
imshow("image", img); // Show image
waitKey(0);

return 0;
}
