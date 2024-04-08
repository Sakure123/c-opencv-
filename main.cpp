#include<iostream>
#include<filesystem>
#include<string>
#include<opencv.hpp>
#include"prediction.h"
namespace fs = std::filesystem;
int main()
{
	const std::string postive_dir = "E:\\test\\1";
	const std::string negative_dir = "E:\\test\\0";
	std::vector<std::vector<float>> Xs;
	std::vector<float> y;
	for(fs::directory_entry entry : fs::directory_iterator(fs::path(postive_dir)))
	{
		std::string filepath = entry.path().string();
		cv::Mat image = cv::imread(filepath,-1);
		image.convertTo(image, CV_32F, 1.0 / 255);
		std::vector<float> x;
		x.assign((float*)image.datastart, (float*)image.dataend);
		Xs.push_back(x);
		y.push_back(1);
	}
	for (fs::directory_entry entry : fs::directory_iterator(fs::path(negative_dir)))
	{
		std::string filepath = entry.path().string();
		cv::Mat image = cv::imread(filepath,-1);
		image.convertTo(image, CV_32F, 1.0 / 255);
		std::vector<float> x;
		x.assign((float*)image.datastart, (float*)image.dataend);
		Xs.push_back(x);
		y.push_back(0);
	}
	prediction pred(400);
	pred.fit(Xs, y, 100);
	const std::string test_postive_dir = "E:\\train\\1";
	const std::string test_negative_dir = "E:\\train\\0";
	for (fs::directory_entry entry : fs::directory_iterator(fs::path(test_postive_dir)))
	{
		std::string filepath = entry.path().string();
		cv::Mat image = cv::imread(filepath,-1);
		image.convertTo(image, CV_32F, 1.0 / 255);
		std::vector<float> x;
		x.assign((float*)image.datastart, (float*)image.dataend);
		int y_predition = pred.prdeicty(x);
		std::cout << "预测结果：" << y_predition << std::endl;
	}
	for (fs::directory_entry entry : fs::directory_iterator(fs::path(test_negative_dir)))
	{
		std::string filepath = entry.path().string();
		cv::Mat image = cv::imread(filepath,-1);
		image.convertTo(image, CV_32F, 1.0 / 255);
		std::vector<float> x;
		x.assign((float*)image.datastart, (float*)image.dataend);
		int y_predition = pred.prdeicty(x);
		std::cout << "预测结果：" << y_predition << std::endl;
	}
}