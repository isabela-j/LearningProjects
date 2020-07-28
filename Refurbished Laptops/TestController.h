#pragma once
#include "Controller.h"
#include <cassert>
class TestController
{
public:
	void testAdd();
	void testRemove();
	void testUpdate();
	void testAddData();
	void testGeneralFilter();
	void testGetAllElements();

private:
	Controller ctrl;
	void setUp();
	void tearDown();
};

