#include "LaptopsWithBaseFilter.h"

LaptopsWithBaseFilter::LaptopsWithBaseFilter() {
	displaySize = 0;
}

LaptopsWithBaseFilter::LaptopsWithBaseFilter(double dSize) {
	displaySize = dSize;
}

LaptopsWithBaseFilter::~LaptopsWithBaseFilter() {

}

bool LaptopsWithBaseFilter::match(Laptop* lap) {
	return displaySize == lap->getDisplaySize();
}