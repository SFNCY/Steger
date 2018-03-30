/*********************绘制直方图*********************/
/*********************绘制直方图*********************/
/*********************绘制直方图*********************/
//#include<opencv2/opencv.hpp>    
//#include<iostream>    
//#include<vector>     
//using namespace cv;
//using namespace std;
//
//int main()
//{
//	Mat srcImage = imread("1.bmp");
//	imshow("ScrImage", srcImage);
//	int channels = 0;
//	MatND dstHist;
//	int histSize[] = { 256 };       //如果写成int histSize = 256;调用计算直方图的函数的时，该变量需写成&histSize    
//	float midRanges[] = { 0, 256 };
//	const float *ranges[] = { midRanges };
//	calcHist(&srcImage, 1, &channels, Mat(), dstHist, 1, histSize, ranges, true, false);
//
//	//绘制直方图,首先先创建一个黑底的图像，为了可以显示彩色，所以该绘制图像是一个8位的3通道图像    
//	Mat drawImage = Mat::zeros(Size(256, 256), CV_8UC3);
//	//任何一个图像的某个像素的总个数有可能会很多，甚至超出所定义的图像的尺寸，  
//	//所以需要先对个数进行范围的限制，用minMaxLoc函数来得到计算直方图后的像素的最大个数    
//	double g_dHistMaxValue;
//	minMaxLoc(dstHist, 0, &g_dHistMaxValue, 0, 0);
//	//将像素的个数整合到图像的最大范围内    
//	for (int i = 0; i < 256; i++)
//	{
//		int value = cvRound(dstHist.at<float>(i) * 256 * 0.9 / g_dHistMaxValue);
//		line(drawImage, Point(i, drawImage.rows - 1), Point(i, drawImage.rows - 1 - value), Scalar(0, 0, 255));
//	}
//
//	imshow("hist", drawImage);
//	waitKey(0);
//	return 0;
//}
//

/*********************2.通道分离*********************/
/*********************2.通道分离*********************/
/*********************2.通道分离*********************/
//#include <opencv2\opencv.hpp>
//#include <iostream>
//using namespace std;
//using namespace cv;
//int main()
//{
//	Mat SrcMat = imread("1.bmp");
//	cout << "通道数：" << SrcMat.channels() << endl;
//	//namedWindow("原图像", WINDOW_NORMAL);
//	imshow("原图像", SrcMat);
//
//	std::vector<cv::Mat>SrcMatpart(SrcMat.channels());      //生成与通道数数目相等的图像容器
//	cv::split(SrcMat, SrcMatpart);                          //分解与通道数数目相等的图像容器
//	//cv::Mat MergeMat;
//	//cv::merge(SrcMatpart, MergeMat);                                //合成与通道数数目相等的图像容器
//
//	Mat a= SrcMatpart[0];
//	imshow("合成后", SrcMatpart[0]);
//	cout << "合成后通道数：" << SrcMatpart[0].channels() << endl;
//	waitKey(20171209);
//	//destroyWindow("原图像");
//}

/*********************3.OTSU自动阈值分割*********************/
/*********************3.OTSU自动阈值分割*********************/
/*********************3.OTSU自动阈值分割*********************/
//#include <iostream>  
//#include <opencv2/opencv.hpp>  
//using namespace std;
//using namespace cv;
//
//int main()
//{
//	//Mat img = imread(argv[1], -1);
//	//if (img.empty())
//	//{
//	//	cout << "Error: Could not load image" << endl;
//	//	return 0;
//	//}
//
//	Mat SrcMat = imread("差分后.jpg");
//	//cout << "通道数：" << SrcMat.channels() << endl;
//	////namedWindow("原图像", WINDOW_NORMAL);
//	//imshow("原图像", SrcMat);
//
//	//std::vector<cv::Mat>SrcMatpart(SrcMat.channels());      //生成与通道数数目相等的图像容器
//	//cv::split(SrcMat, SrcMatpart);                          //分解与通道数数目相等的图像容器
//	//Mat img = SrcMatpart[0];
//
//	Mat gray;
//	cvtColor(SrcMat, gray, CV_BGR2GRAY);
//	Mat dst;
//	int thre = threshold(gray, dst, 0, 255, CV_THRESH_OTSU);
//	//threshold(gray, dst, 250, 255, CV_THRESH_BINARY);         //0是黑色，1是白色
//	cout << "当前阈值为：" << thre << endl;
//	imshow("src", SrcMat);
//	imshow("gray", gray);
//	imshow("dst", dst);
//	//imwrite("guangxian.jpg", dst);
//	waitKey(0);
//
//	return 0;
//}


/*********************4.图像差分*********************/
/*********************4.图像差分*********************/
/*********************4.图像差分*********************/
//#include <opencv2\opencv.hpp>
//#include <iostream>
//using namespace cv;
//using namespace std;
//int main()
//{
//	Mat foreground = imread("foreground.bmp");
//	Mat background = imread("background.bmp");
//	Mat diff = foreground - background;
//	imshow("差分后", diff);
//	imwrite("差分后.jpg", diff);
//	waitKey(20171209);
//}
