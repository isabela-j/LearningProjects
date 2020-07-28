#include "Controller.h"
Controller::Controller(Repo<Laptop>* repos) {
	repo = repos;
}

Controller::~Controller() {
	repo->~Repo();
	cout << "Controller destructor called. \n";
}

/// returns true is the laptop was added to the repository, false otherwise
bool Controller::addALaptop(Laptop* lap) {
	return repo->addLaptop(lap);
}

/// returns true is the laptop was removed from the repository, false otherwise
bool Controller::removeALaptop(Laptop* lap) {
	return repo->removeLaptop(lap);
}

/// returns true is the laptop was updated from the repository, false otherwise
bool Controller::updateALaptop(const QString& s, Laptop* lap) {
	return repo->updateLaptop(s, lap);
}

/// shows the string of all of the laptops from the repository
QString Controller::stringForAllLaptops() const {
    return repo->stringForAll();
}

///shows the string of the laptop which is at position "index"
QString Controller::showLAPbyIndex(const int& index) const {
    return repo->showLaptopFromIndex(index);
}


/// adds some data to the repository( at the beginning)
void Controller:: addData() { ///adds some random data to the repository
    Laptop* a = new Laptop(13.45, 32, "Acer", 199.99, 1, "https://laptop-gaming-msi");
	this->addALaptop(a);
    Laptop* b = new Laptop(15.6, 64, "Toshiba", 220.99, 3, "https://laptop-lenovo-legion-y530");
	this->addALaptop(b);
    Laptop* c = new Laptop(10.8, 64, "Asus", 299.99, 2, "https://laptop-hp-pavilion-15-dk0003");
	this->addALaptop(c);
    Laptop* d = new Laptop(11.5, 31, "Dell", 3100, 5, "https://laptop-hp-pavilion-15-dk0025nq");
	this->addALaptop(d);
    Laptop* e = new Laptop(18, 74, "MacBook", 1500, 2, "https://laptop-lenovo-legion-y7000");
	this->addALaptop(e);
    Laptop* h = new Laptop(10.8, 43, "Lenovo", 349.99, 1, "https://laptop-hp-250-g7");
	this->addALaptop(h);
}


/// filters the repository by a specific atributte
/// returns a vector which has all the laptops with that atributte
std::vector<Laptop*>  Controller::generalFilter(BaseFilter* filter) {
	std::vector<Laptop*> filteredList;
	 for (int i = 0; i < repo->getLength(); i++) {
		 Laptop* p = repo->getElements()[i];
		 if (filter->match(p)) {
			 filteredList.push_back(p);
		 }
			 
	 }
	 return filteredList; ///if we find specific elements, we return the new list
}

void Controller::loadFromFile(std::string document) {
	PersistenceEngineFromCSV* pers = new PersistenceEngineFromCSV();
	pers->readFromFile(document, repo);
    std::vector<Laptop *> res= repo->getElements();
    for(int i=0; i<repo->getLength();i++)
        addToUndo(res[i],1);
}

void Controller::saveDataFile(std::string document) {
	PersistenceEngineFromCSV* pers = new PersistenceEngineFromCSV();
	std::vector<Laptop*> res = repo->getElements();
	pers->writeInFile(document, res);
}

void Controller::saveDataFileJson(std::string document) {
	PersistenceEngineFromJson* pers = new PersistenceEngineFromJson();
	std::vector<Laptop*> res = repo->getElements();
    pers->writeInFile(document, res);
}

void Controller::addToUndo(Laptop *laptop, int opr)
{
    operation it;
    it.lap=laptop;
    it.op=opr;
    this->undo.push(it);
    //std::cout<<undo.top().op;
}

void Controller::removeFromUndo()
{
    this->undo.pop();

}

void Controller::addToRedo(Laptop *laptop, int opr)
{
    operation it;
    it.lap=laptop;
    it.op=opr;
    this->redo.push(it);

}

void Controller::removeFromRedo()
{
    this->redo.pop();
}

void Controller::removeEntireLaptop(const QString &s){
    repo->removeAllLaptops(s);
}

void Controller::undoOPERATION()
{
    if(undo.empty())
        cout<<"There is nothing to undo. \n";
    else
    {
        operation opp=undo.top();
        removeFromUndo();
        if(opp.op==1){
            int index=findIndex(opp.lap->getPhoto());
            Laptop *lap=getLaptopFromThisIndex(index);

            Laptop *laptopRemoved= new Laptop(lap->getDisplaySize(),lap->getMemorySize(),lap->getProcessor(), lap->getPrice(),lap->getQuantity(), lap->getPhoto());
            removeEntireLaptop(opp.lap->getPhoto());
            addToRedo(laptopRemoved, opp.op);
        }
        else {
            addALaptop(opp.lap);
            addToRedo(opp.lap, opp.op);
        }

    }
}

void Controller::redoOPERATION()
{
    if(redo.empty())
        cout<<"There is nothing to redo. \n";
    else
    {
        operation opp=redo.top();
        removeFromRedo();
        if(opp.op==1){
            addALaptop(opp.lap);
            addToUndo(opp.lap, opp.op);
        }
        else{
            int index=findIndex(opp.lap->getPhoto());
            Laptop *lap=getLaptopFromThisIndex(index);

            Laptop *laptopRemoved= new Laptop(lap->getDisplaySize(),lap->getMemorySize(),lap->getProcessor(), lap->getPrice(),lap->getQuantity(), lap->getPhoto());
            removeEntireLaptop(opp.lap->getPhoto());
            addToRedo(laptopRemoved, opp.op);
        }

    }
}


void Controller::loadFromJsonFile(std::string document) {
	PersistenceEngineFromJson* pers = new PersistenceEngineFromJson();
    pers->readFromFile(document, repo);

}
