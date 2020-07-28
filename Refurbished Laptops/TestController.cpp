#include "TestController.h"
void TestController::setUp() {
	Repo<Laptop> repos;
	ctrl = &repos;
}

void TestController::tearDown() {
	ctrl.~Controller();
}

void TestController::testAdd() {
	setUp();

	Laptop* p = new Laptop(13.45, 32, "Intel Core i5", 199.99, 1, "https://laptop-gaming-msiiii");
	assert(ctrl.addALaptop(p) == 1);
	assert(ctrl.addALaptop(p) == 0);

	tearDown();
}

void TestController::testRemove() {
	setUp();

	Laptop* p = new Laptop(13.45, 32, "Intel Core i5", 199.99, 1, "https://laptop-gaming-msi");
	ctrl.addALaptop(p);
	assert(ctrl.removeALaptop(p) == 1);
	assert(ctrl.removeALaptop(p) == 0);

	tearDown();
}

void TestController::testUpdate() {
	setUp();

	Laptop* p = new Laptop(13.45, 32, "Intel Core i5", 199.99, 1, "https://laptop-gaming-msi");
	Laptop* h = new Laptop(15, 64, "Intel Core i3", 199.99, 5, "https://laptop-acer-i900");
	ctrl.addALaptop(p);
	assert(ctrl.updateALaptop(p->getPhoto(), h) == 1);
	assert(ctrl.updateALaptop(p->getPhoto(), h) == 0);
	delete p;
	delete h;
	tearDown();
}

void TestController::testAddData() {
	setUp();
	ctrl.addData();
	assert(ctrl.getSizeCtrl() == 6);
	tearDown();
}

void TestController::testGeneralFilter() {
	setUp();
	ctrl.addData();
	LaptopsWithBaseFilter* f = new LaptopsWithBaseFilter(15.6);
	std::vector < Laptop*> res;
	res=ctrl.generalFilter(f);
	assert(res.size() == 1);
	for (auto it : res)
		delete it;
	tearDown();
}

void TestController::testGetAllElements() {
	setUp();
	ctrl.addData();
	std::vector < Laptop*> res;
	res = ctrl.getAllElements();
	assert(res.size() == 6);
	for (auto it : res)
		delete it;
	tearDown();
}