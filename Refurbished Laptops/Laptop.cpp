#include "Laptop.h"

///default constructor
Laptop::Laptop() {
    displaySize = 0;
    memorySize = 0;
    processorGeneration = "";
    price = 0;
    quantity = 0;
    photo = "";
}

///another constructor
Laptop::Laptop(const double dSize, const int mSize, const QString pGen, const double price, const int quantity,
    const QString pic) {
    this->displaySize = dSize;
    this->memorySize = mSize;
    this->processorGeneration = pGen;
    this->price = price;
    this->quantity = quantity;
    this->photo = pic;
}

///copy constructor
Laptop::Laptop(const Laptop& obj) {
    this->displaySize = obj.displaySize;
    this->memorySize = obj.memorySize;
    this->processorGeneration = obj.processorGeneration;
    this->price = obj.price;
    this->quantity = obj.quantity;
    this->photo = obj.photo;
}

///destructor
Laptop::~Laptop() {
    displaySize = 0;
    memorySize = 0;
    processorGeneration = "";
    price = 0;
    quantity = 0;
    photo = "";
}

/// equality operator
/// If we ever need to modify the data from an object of type Laptop with another one( still of type Laptop)
/// we don't have to proceed like this: lap1.setPhoto(lap2.getPhoto());    ( also available for displaySize, memorySize, etc)
/// We will just do: lap1=lap2;
Laptop& Laptop::operator=(const Laptop& other) {
    this->displaySize = other.displaySize;
    this->memorySize = other.memorySize;
    this->processorGeneration = other.processorGeneration;
    this->price = other.price;
    this->quantity = other.quantity;
    this->photo = other.photo;
    return *this;
}


///getters
double Laptop::getDisplaySize() const { return displaySize; }

int Laptop::getMemorySize() const { return memorySize; }

QString Laptop::getProcessor() const { return processorGeneration; }

double Laptop::getPrice() const { return price; }

int Laptop::getQuantity() const { return quantity; }

QString Laptop::getPhoto() const { return photo; }

///setters

void Laptop::setDisplaySize(const double& dSize) { this->displaySize = dSize; }
void Laptop::setMemorySize(const int& mSize) { this->memorySize = mSize; }
void Laptop::setProcessor(const QString& pGen) { this->processorGeneration = pGen; }
void Laptop::setPrice(const double& price) { this->price = price; }
void Laptop::setQuantity(const  int& quantity) { this->quantity = quantity; }
void Laptop::setPhoto(const QString& pic) { this->photo = pic; }


///get a special string for your object in order to see all of its specifications
QString Laptop::toString() const {
    QString str= "Display size: "+QString::number(displaySize)+"\n Memory size: "+QString::number(memorySize)+"\n Processor: "+processorGeneration+"\n Price: "+QString::number(price)+"\n Quantity: "+QString::number(quantity)+"\n Picture:"+ photo+"\n";
    return str;
}

bool Laptop::operator==(const Laptop &other)
{
    return !(photo.compare(other.photo, Qt::CaseInsensitive)); //returns true if the laptops are different
}

bool Laptop::operator<(const Laptop &other) const
{
    return(photo.compare(other.photo,Qt::CaseInsensitive)<0);
}

bool Laptop::operator==(const QString &other_photo)
{
    return !(photo.compare(other_photo, Qt::CaseInsensitive));
}
