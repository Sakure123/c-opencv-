#include "prediction.h"
#include<random>
#include<iostream>
prediction::prediction(int input_size, float learing_rate) :m_lr(learing_rate)
{
	std::default_random_engine e;
	std::uniform_real_distribution<float> distribution(-1.0, 1.0);
	for (int i = 0; i < input_size; ++i)
	{
		m_w.push_back(distribution(e));
	}
	m_bios = 0;
}

float prediction::netInput(const std::vector<float>& x)
{
	float sum = m_bios;
	for (int i = 0; i < x.size(); ++i)
	{
		sum += x[i] * m_w[i];
	}
	return sum;
}

int prediction::prdeicty(const std::vector<float>& x)
{
	return netInput(x) > 0 ? 1 : 0;
}

float prediction::train(const std::vector<float>& x, int y)
{
	int y_prediction = prdeicty(x);
	float update = (y - y_prediction) * m_lr;
	for (int i = 0; i < m_w.size(); ++i)
	{
		m_w[i] += update * x[i];
	}
	m_bios += update;
	return update;
}

void prediction::fit(const std::vector<std::vector<float>>& Xs, const std::vector<float>& y, int input)
{
	for (int i = 0; i < input; ++i)
	{
		int error = 0;
		for (int j = 0; j < Xs.size(); ++j)
		{
			float update = train(Xs[j],y[j]);
			error += update != 0?1 : 0;
		}
		std::cout << "epoch£º" << i << "error= " << error << std::endl;
	}
}
