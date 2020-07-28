#include "TestLaptop.h"
#include <cassert>

//void TestLaptop::tearDown() {
//	lap.~Laptop();
//}

//void TestLaptop::setUp() {
//	Laptop* p=new Laptop(13.45, 32, "Intel Core i5", 199.99, 1, "https://laptop-gaming-msi");
//	lap = p;
//}

void TestLaptop::testGetters() {
	Laptop* lap = new Laptop(13.45, 32, "Intel Core i5", 199.99, 1, "https://laptop-gaming-msi");
	assert(lap->getDisplaySize() == 13.45);
	assert(lap->getMemorySize() == 32);
	assert(lap->getProcessor() == "Intel Core i5");
	assert(lap->getPrice() == 199.99);
	assert(lap->getQuantity() == 1);
	assert(lap->getPhoto() == "https://laptop-gaming-msi");
	
	//tearDown();
}

void TestLaptop::testSetters() {
	//setUp();
	Laptop* lap = new Laptop(13.45, 32, "Intel Core i5", 199.99, 1, "https://laptop-gaming-msi");
	lap->setDisplaySize(20);
	assert(lap->getDisplaySize() == 20);
	lap->setMemorySize(22);
	assert(lap->getMemorySize() == 22);
	lap->setProcessor("Intel Core i7");
	assert(lap->getProcessor() == "Intel Core i7");
	lap->setPrice(200);
	assert(lap->getPrice() == 200);
	lap->setQuantity(8);
	assert(lap->getQuantity() == 8);
	lap->setPhoto("https://laptop-gaming-mmm");
	assert(lap->getPhoto() == "https://laptop-gaming-mmm");
	//tearDown();
}

//TestLaptop::TestLaptop() = default;