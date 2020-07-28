#pragma once
#include "Repository.h"
#include "LaptopsWithBaseFilter.h"
#include "PersistenceEngine.h"
#include <set>
#include <stack>
struct operation {
    Laptop *lap;
    int op;
};
class Controller
{
public:
	Controller(Repo<Laptop>* repos);
	~Controller();
    int findIndex(const QString & t_name){return repo->findIndexByPhoto(t_name);}
	bool addALaptop(Laptop* lap);
	bool removeALaptop(Laptop* lap);
    bool updateALaptop(const QString& s, Laptop* lap);
    QString stringForAllLaptops() const;
    QString showLAPbyIndex(const int& index) const;
	void addData();
	void loadFromFile(std::string document);
	void loadFromJsonFile(std::string document);
	std::vector<Laptop*> generalFilter(BaseFilter* filter);
	std::vector<Laptop*> getAllElements() { return repo->getElements(); }
	int getSizeCtrl() { return repo->getLength(); }
	void saveDataFile(std::string document);
    void saveDataFileJson(std::string document);
    const QVector<Laptop*> &ctrl(){return repo->getrepo();}
    std::set<Laptop> &toBuyList() { return toBuy;}

    bool addToBuy(Laptop lap){
        auto res= toBuy.insert(lap);
        // res - pair : first element iterator to position of the element
        // second element is a bool -> was the element inserted
        for(Laptop l: toBuy){
            std::cout<<l.getProcessor().toStdString()<<" ";
        }
        std::cout<<std::endl;
        return res.second;
    }

    void addToUndo(Laptop* laptop, int opr);
    void removeFromUndo();
    void addToRedo(Laptop* laptop, int opr);
    void removeFromRedo();
    void removeEntireLaptop(const QString &s);

    void undoOPERATION();
    void redoOPERATION();

    Laptop* getLaptopFromThisIndex(const int& index) const{ return repo->getLaptopFromIndex(index);}

private:
	Repo<Laptop>* repo;
    std::set<Laptop> toBuy;
    std::stack<operation> undo; /// 1- add, 2-remove
    std::stack<operation> redo;
};

