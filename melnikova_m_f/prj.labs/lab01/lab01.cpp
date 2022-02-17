#include <opencv2/opencv.hpp>

int main() {
	cv::Mat img(180, 768, CV_8UC1);
	// draw dummy image
	img = 0;
	int r = 0, g = 0;
	const cv::Scalar& clr = 150;
	cv::Rect rc = { 0, 0, 3, img.rows };
	for (int i = 0; i < 768; i += 3) {
		cv::rectangle(img, rc, { i / 3.0 }, -1);
		rc.x += rc.width;
	}
	cv::imwrite("test.png", img);
}

