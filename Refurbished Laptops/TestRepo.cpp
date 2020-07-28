#include "TestRepo.h"
void TestRepo::tearDown() {
	elem.~Repo();
}

void TestRepo::testAdd() {
	Laptop* p = new Laptop(13.45, 32, "Intel Core i5", 199.99, 1, "https://laptop-gaming-msi");
	assert(elem.addLaptop(p) == 1);
	assert(elem.addLaptop(p) == 0);

	tearDown();
}

void TestRepo::testRemove() {
	Laptop* p = new Laptop(13.45, 32, "Intel Core i5", 199.99, 1, "https://laptop-gaming-msi");
	elem.addLaptop(p);
	assert(elem.removeLaptop(p) == 1);
	assert(elem.removeLaptop(p) == 0);

	tearDown();
}

void TestRepo::testUpdate() {
	Laptop* p = new Laptop(13.45, 32, "Intel Core i5", 199.99, 1, "https://laptop-gaming-msi");
	Laptop* h = new Laptop(15, 64, "Intel Core i3", 199.99, 5, "https://laptop-acer-i900");
	elem.addLaptop(p);
	assert(elem.updateLaptop(p->getPhoto(), h) == 1);
	assert(elem.updateLaptop(p->getPhoto(), h) == 0);
	delete p;
	delete h;

	tearDown();
}

void TestRepo::testGetElements() {
	Laptop* p = new Laptop(13.45, 32, "Intel Core i5", 199.99, 1, "https://laptop-gaming-msi");
	Laptop* h = new Laptop(15, 64, "Intel Core i3", 199.99, 5, "https://laptop-acer-i900");
	elem.addLaptop(p);
	elem.addLaptop(h);
	std::vector<Laptop*> res;
	res = elem.getElements();
	assert(res.size() == 2);
	assert(res[1]->getDisplaySize() == 15);
	for (auto it : res) {
		delete  it;
	}
	tearDown();
}