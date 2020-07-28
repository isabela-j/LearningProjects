#pragma once
#include "BaseFilter.h"
class LaptopsWithBaseFilter:public BaseFilter
{
private:
	double displaySize;
public:
	LaptopsWithBaseFilter();
	LaptopsWithBaseFilter(double dSize);
	~LaptopsWithBaseFilter();
	bool match(Laptop* lap);
};

