#pragma once
#include "Repository.h"
#include <cassert>
class TestRepo
{
private:
	Repo<Laptop> elem;
	void tearDown();

public:
	void testAdd();
	void testRemove();
	void testUpdate();
	void testGetElements();
};



