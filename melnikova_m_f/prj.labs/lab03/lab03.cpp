#include <opencv2/opencv.hpp>
#include <cmath>



int8_t Function(int8_t x)
{
	
	int8_t y = abs( x/2 * (sin(x/2) + cos(3*x)));



	return y;
};



int main()
{
	std::string name = "../../../data/cross_0256x0256.png";



	cv::Mat img_black_white = cv::imread(name, cv::IMREAD_GRAYSCALE);
	cv::Mat img = cv::imread(name);



	cv::imwrite("lab03_rgb.png", img);
	cv::imwrite("lab03_gre.png", img_black_white);



	cv::Mat I_1(256, 256, CV_8UC1);
	I_1 = 255;



	for (int i = 0; i < 256; i++)
	{
		I_1.at<int8_t>(Function(i), i) = 0;
	}



	cv::rotate(I_1, I_1, cv::ROTATE_180);



	cv::resize(I_1, I_1, cv::Size(512, 512), 0, 0, cv::InterpolationFlags::INTER_CUBIC);
	cv::imwrite("lab03_viz_func.png", I_1);



	cv::Mat lut(1, 256, CV_8UC1);



	for (int i = 0; i < 256; i++)
	{
		lut.at<int8_t>(0, i) = Function(i);
	}



	cv::Mat black_white_lut(256, 256, CV_8UC1);



	cv::LUT(img_black_white, lut, black_white_lut);
	cv::imwrite("lab03_gre_res.png", black_white_lut);



	cv::Mat img_lut_rgb(256, 256, CV_8UC3);



	cv::LUT(img, lut, img_lut_rgb);
	cv::imwrite("img_lut_rgb.png", img_lut_rgb);




	cv::Mat bgr[3];
	cv::split(img, bgr);
	cv::LUT(bgr[0], lut, bgr[0]);
	cv::LUT(bgr[1], lut, bgr[1]);
	cv::LUT(bgr[2], lut, bgr[2]);



	cv::Mat zeros = cv::Mat::zeros(cv::Size(img.rows, img.cols), CV_8UC1);



	cv::merge(std::vector<cv::Mat>({ bgr[0], zeros, zeros }), bgr[0]);
	cv::merge(std::vector<cv::Mat>({ zeros, bgr[1], zeros }), bgr[1]);
	cv::merge(std::vector<cv::Mat>({ zeros, zeros, bgr[2] }), bgr[2]);



	cv::Mat bw(256, 256, CV_8UC3);
	cv::merge(std::vector<cv::Mat>({ black_white_lut, black_white_lut, black_white_lut }), bw);



	cv::Mat img_channels(img.rows * 2, img.cols * 2, CV_8UC3);



	bw.copyTo(img_channels(cv::Rect(0, 0, 256, 256)));
	bgr[0].copyTo(img_channels(cv::Rect(256, 256, 256, 256)));
	bgr[1].copyTo(img_channels(cv::Rect(0, 256, 256, 256)));
	bgr[2].copyTo(img_channels(cv::Rect(256, 0, 256, 256)));



	cv::imwrite("lab03_rgb_res.png", img_channels);



	return 0;
}
