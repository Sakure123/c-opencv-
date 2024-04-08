#pragma once
#include<vector>
class prediction
{
public:
	std::vector<float> m_w;
	float m_bios;
	float m_lr;
	prediction(int input_size, float learning_rate = 0.01);
	float netInput(const std::vector<float>& x);
	int prdeicty(const std::vector<float>& x);
	float train(const std::vector<float>& x, int y);
	void fit(const std::vector<std::vector<float>>& Xs, const std::vector<float>& y, int input);
};

