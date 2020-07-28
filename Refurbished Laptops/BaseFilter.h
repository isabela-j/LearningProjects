#pragma once
#include "Laptop.h"
class BaseFilter
{
private:
    Laptop* p;
public:
    BaseFilter();
    ~BaseFilter();
    bool virtual match(Laptop* lap) = 0;
};

