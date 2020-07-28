#pragma once
#include <exception>
#include <string>
using namespace std;

class BaseRepoExceptions: public exception
{
public:
	 const char* what() const override { return "Generic. \n"; }
};

class FileException : public BaseRepoExceptions
{
private:
	std::string path_name;
	std::string exceptionMessage;
public:
	FileException(std::string path_n) : path_name(path_n) {
		exceptionMessage = "The file " + path_name + " does not exist. \n";
	}
	const char* what() const {
		return exceptionMessage.c_str();
	}
};

class ArrayOutOfBoundsException : public BaseRepoExceptions
{
public:
	const char* what() const { return "Out of bound. \n"; }
};

class LaptopNotFoundException : public BaseRepoExceptions
{
private:
	std::string laptopPic;
	std::string exceptionMessage;

public:
	LaptopNotFoundException(std::string lName) : laptopPic(lName) {
		exceptionMessage = "Laptop with image link " + laptopPic + " not found. \n";
	}
	const char* what() const {
		return exceptionMessage.c_str();
	}

};


