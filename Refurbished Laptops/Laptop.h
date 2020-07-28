#pragma once
#include <string>
#include <QString>
#include <iostream>
using namespace std;
using std::string;


class Laptop
{
public:
    Laptop();
    Laptop(const double dSize = 0, const int mSize = 0, const QString pGen = "", const double price = 0, const  int quantity = 0, const QString pic = "");
    Laptop(const Laptop& obj);
    ~Laptop();
    Laptop& operator=(const Laptop& other);



    ///getters
    double getDisplaySize() const;
    int getMemorySize() const;
    QString getProcessor() const;
    double getPrice() const;
    int getQuantity() const;
    QString getPhoto() const;

    ///setters
    void setDisplaySize(const double& dSize);
    void setMemorySize(const int& mSize);
    void setProcessor(const QString& pGen);
    void setPrice(const double& price);
    void setQuantity(const  int& quantity);
    void setPhoto(const QString& pic);

    ///string for laptop
    QString toString() const;

    ///assignment operators
    bool operator==(const Laptop& other);
    bool operator==(const QString& other_photo);
    bool operator<(const Laptop &other) const;

private:
    double displaySize;
    int memorySize;
    QString processorGeneration;
    double price;
    int quantity;
    QString photo;

};

