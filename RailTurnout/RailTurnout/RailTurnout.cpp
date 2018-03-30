//#include <opencv2\opencv.hpp>
//#include <iostream>
//using namespace cv;
//using namespace std;
//int main()
//{
//	Mat foreground = imread("组3（水平）\\foreground.jpg");
//	Mat background = imread("组3（水平）\\background.jpg");
//	Mat diff = foreground - background;
//	namedWindow("差分后", WINDOW_NORMAL);
//	moveWindow("差分后",0,0);
//	imshow("差分后", diff);
//
//	//通道分离成R、G、B
//	std::vector<cv::Mat>SrcMatpart(diff.channels());      //生成与通道数数目相等的图像容器
//	cv::split(diff, SrcMatpart);                          //分解与通道数数目相等的图像容器
//	Mat diff_b = SrcMatpart[0];
//	Mat diff_g = SrcMatpart[1];
//	Mat diff_r = SrcMatpart[2];
//
//	//根据R通道与G通道混合分割的效果
//	Mat dst_g, dst_r, dst;
//	int thre = threshold(diff_g, dst_g, 0, 255, CV_THRESH_OTSU);
//	//threshold(gray, dst, 250, 255, CV_THRESH_BINARY);         //0是黑色，1是白色
//	cout << "当前阈值为：" << thre << endl;
//
//	//根据上一步OTSU自动分割的阈值对G通道分割出来的取反与R通道分割出来的进行与运算
//	threshold(diff_g, dst_g, thre, 255, CV_THRESH_BINARY_INV);   
//
//	//对R通道进行OTSU阈值分割
//	threshold(diff_r, dst_r, 0, 255, CV_THRESH_OTSU);
//
//	//与运算得到光线区域
//	bitwise_and(dst_g, dst_r, dst);
//	imshow("dst", diff_r);
//
//	//Mat gray;
//	//cvtColor(diff, gray, CV_BGR2GRAY);
//	//Mat dst;
//	//int thre = threshold(gray, dst, 0, 255, CV_THRESH_OTSU);
//	////threshold(gray, dst, 250, 255, CV_THRESH_BINARY);         //0是黑色，1是白色
//	//cout << "当前阈值为：" << thre << endl;
//	//imshow("src", diff);
//	//imshow("gray", gray);
//	//imshow("dst", dst);
//	////imwrite("guangxian.jpg", dst);
//	//waitKey(0);
//
//	cout << "diff_r的通道数：" << diff_r.channels() << endl;
//	cvtColor(diff_r, diff_r, CV_GRAY2BGR);
//	cout << "diff_r的通道数：" << diff_r.channels() << endl;
//	imwrite("差分后.jpg", diff_r);
//	waitKey(20171209);
//}


//提取光线中心
#include <opencv2\opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;
int main()
{
	Mat img0 = imread("差分后.jpg", 1);
	imshow("原图", img0);
	Mat img;
	cvtColor(img0, img0, CV_BGR2GRAY);
	img = img0.clone();

	//高斯滤波
	img.convertTo(img, CV_32FC1);
	GaussianBlur(img, img, Size(0, 0), 6, 6);

	//一阶偏导数
	Mat m1, m2;
	m1 = (Mat_<float>(1, 2) << 1, -1);  //x偏导
	m2 = (Mat_<float>(2, 1) << 1, -1);  //y偏导

	Mat dx, dy;
	filter2D(img, dx, CV_32FC1, m1);
	filter2D(img, dy, CV_32FC1, m2);

	//二阶偏导数
	Mat m3, m4, m5;
	m3 = (Mat_<float>(1, 3) << 1, -2, 1);   //二阶x偏导
	m4 = (Mat_<float>(3, 1) << 1, -2, 1);   //二阶y偏导
	m5 = (Mat_<float>(2, 2) << 1, -1, -1, 1);   //二阶xy偏导

	Mat dxx, dyy, dxy;
	filter2D(img, dxx, CV_32FC1, m3);
	filter2D(img, dyy, CV_32FC1, m4);
	filter2D(img, dxy, CV_32FC1, m5);

	//hessian矩阵
	double maxD = -1;
	int imgcol = img.cols;
	int imgrow = img.rows;
	vector<double> Pt;
	for (int i = 0; i<imgcol; i++)
	{
		for (int j = 0; j<imgrow; j++)
		{
			if (img0.at<uchar>(j, i)>50)           //阈值设置
			{
				Mat hessian(2, 2, CV_32FC1);
				hessian.at<float>(0, 0) = dxx.at<float>(j, i);
				hessian.at<float>(0, 1) = dxy.at<float>(j, i);
				hessian.at<float>(1, 0) = dxy.at<float>(j, i);
				hessian.at<float>(1, 1) = dyy.at<float>(j, i);

				Mat eValue;				   //特征值
				Mat eVectors;              //特征向量
				eigen(hessian, eValue, eVectors);

				//cout << "特征值为：" << eValue << endl;
				//cout << "特征向量为：" << eVectors << endl;

				double nx, ny;				 //特征向量的x，y分量
				double fmaxD = 0;            //最大特征值
				if (fabs(eValue.at<float>(0, 0)) >= fabs(eValue.at<float>(1, 0)))  //求特征值最大时对应的特征向量
				{
					nx = eVectors.at<float>(0, 0);
					ny = eVectors.at<float>(0, 1);
					fmaxD = eValue.at<float>(0, 0);
				}
				else
				{
					nx = eVectors.at<float>(1, 0);
					ny = eVectors.at<float>(1, 1);
					fmaxD = eValue.at<float>(1, 0);
				}

				double t = -(nx*dx.at<float>(j, i) + ny*dy.at<float>(j, i)) / (nx*nx*dxx.at<float>(j, i) + 2 * nx*ny*dxy.at<float>(j, i) + ny*ny*dyy.at<float>(j, i));

				//cout << "i = " << i << endl;
				//cout << "j = " << j << endl;
				//cout << "t*nx:" << t*nx << endl;
				//cout << "t*ny:" << t*ny << endl;
				if (fabs(t*nx) <= 0.5 && fabs(t*ny) <= 0.5)
				{
					Pt.push_back(i);
					Pt.push_back(j);
				}
			}
		}
	}
	Mat result;
	cvtColor(img0, result, COLOR_GRAY2BGR);
	//result = imread("组3（水平）\\foreground.jpg");
	for (int k = 0; k<Pt.size() / 2; k++)
	{
		Point rpt;
		rpt.x = Pt[2 * k + 0];
		rpt.y = Pt[2 * k + 1];
		result.at<Vec3b>(rpt.y, rpt.x)[0] = 255;
		result.at<Vec3b>(rpt.y, rpt.x)[1] = 0;
		result.at<Vec3b>(rpt.y, rpt.x)[2] = 0;
		//circle(result, rpt, 1, Scalar(0, 0, 255));
	}
	//namedWindow("result", WINDOW_NORMAL);
	imshow("result", result);
	waitKey(0);
	waitKey(20171209);
}
