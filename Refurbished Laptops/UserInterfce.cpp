/*#include "UserInterfce.h"

///-----------------------------------------ADMINISTRATOR PART--------------------------------------------
void printMenuForAdmin() {
	cout << "\n Choose one option \n";
	cout << "1- Add a laptop. \n";
	cout << "2- Remove a laptop. \n";
	cout << "3- Update a laptop. \n";
	cout << "4- See all laptops. \n";
	cout << "5- Exit. \n";
}

void read(double &dSize, int &memorySize, std:: string& proc, double &price, int& quant, std::string & pic ) {
	cout << "Display size: ";
	cin >> dSize;
	
	cout << "Memory size:";
	cin >> memorySize;
	cin.get();
	cout << "Processor Generation: ";
	std::getline(std::cin, proc);

	cout << "Price: ";
	cin >> price;

	cout << "Quantity: ";
	cin >> quant;

	cin.get();
	cout << "Link to picture: ";
	std::getline(std::cin, pic);
}

void uiAdd(Controller* ctrl) {
	double dSize = 0;
	int memorySize = 0;
	std::string proc;
	double price = 0;
	int quant = 0;
	std::string pic;
	read(dSize, memorySize, proc, price, quant, pic);
	Laptop* lap = new Laptop(dSize, memorySize, proc, price, quant, pic);

	bool ok = ctrl->addALaptop(lap);
	if (ok)
		cout << "Operation completed successfully. \n";
	else cout << "Operation failed to complete. \n";
}

void uiRemove(Controller* ctrl) {
	std::string pic;
	cin.get();
	cout << "Link to the picture: ";
	std::getline(std::cin, pic);
	Laptop* lap = new Laptop(0,0,"",0,0, pic);
	bool ok = ctrl->removeALaptop(lap);
	if (ok)
		cout << "Operation completed successfully. \n";
	else throw LaptopNotFoundException(pic);

}

void uiUpdate(Controller* ctrl) {
	std::string picc;
	cin.get();
	cout << "Link to the picture: ";
	std::getline(std::cin, picc);

	cout << "\n Data of new laptop: \n";
	double dSize = 0;
	int memorySize = 0;
	std::string proc;
	double price = 0;
	int quant = 0;
	std::string pic;
	read(dSize, memorySize, proc, price, quant, pic);
	Laptop* lap = new Laptop(dSize, memorySize, proc, price, quant, pic);

	bool ok = ctrl->updateALaptop(picc, lap);
	if (ok)
		cout << "Operation completed successfully. \n";
	else cout << "Operation failed to complete. \n";



}
void uiSeeAll(Controller* ctrl) {
	ctrl->stringForAllLaptops();
}

void displayUIforAdmin(Controller* ctrl)
{
	int op;
	try {
		ctrl->loadFromFile("C:\\Users\\Isabela\\source\\repos\\Lab9\\csvData9.txt");
		//ctrl->loadFromJsonFile("C:\\Users\\Isabela\\source\\repos\\Lab9\\writeJson.txt");
	}
	catch (BaseRepoExceptions& ex)
	{
		cout << ex.what();
	}
	do {
		printMenuForAdmin();
		cout << "Your option is: ";
		cin >> op;
		switch (op)
		{
		case 1:
			uiAdd(ctrl);
			break;
		case 2:
			try {
				uiRemove(ctrl);
			}
			catch (BaseRepoExceptions &ex) {

				cout << ex.what();
			}
			
			break;
		case 3:
			uiUpdate(ctrl);
			break;
		case 4:
			uiSeeAll(ctrl);
			break;
		case 5:
			try {
				ctrl->saveDataFile("C:\\Users\\Isabela\\source\\repos\\Lab9\\csvData9.txt");
				//ctrl->saveDataFileJson("C:\\Users\\Isabela\\source\\repos\\Lab9\\writeJson.txt");
			}
			catch (BaseRepoExceptions& ex)
			{
				cout << ex.what();
			}
			cout << "Exit. \n";
			exit(0);
		default:
			cout << "Unknown option. \n";
			break;
		}
	} while (true);
}

/// --------------------------------USER PART----------------------------------------------------


void displayForUser(Controller* ctrl) {
	double dSize;
	cout << "Hello! Please insert the display size that you are interested in: ";
	cin >> dSize;

	try {
		ctrl->loadFromFile("C:\\Users\\Isabela\\source\\repos\\Lab9\\csvData9.txt");
	}
	catch (BaseRepoExceptions& ex)
	{
		cout << ex.what();
	}

	///-------- create de filtered repo 

	std::vector<Laptop*> myList;
	if (dSize == 0)
		myList = ctrl->getAllElements();
	else {
		LaptopsWithBaseFilter* b= new LaptopsWithBaseFilter(dSize);
		myList = ctrl->generalFilter(b);
	}

	/// ------- practical part
	
	bool stop = false;
	double totalSum = 0;
	int opt = 0;
	while (!stop) {
		int it = 0;
		if (myList.size() <= 0)
		{
			cout << "I'm sorry! We do not have such laptops anymore. \n";
			cout << "The total sum is: " << totalSum << ". Thank you for choosing us! \n\n";
			stop = true;
		}
		else {
			while (!stop && it < myList.size()) {
				myList[it]->toString();
				cout << "\n Do you want to buy it?(1-yes, 2-no): ";
				cin >> opt;
				if (opt == 1)
				{
					totalSum = totalSum + myList[it]->getPrice();
					myList[it]->setQuantity(myList[it]->getQuantity() - 1);/// if you buy, then decrease the quantity
					if (myList[it]->getQuantity() == 0) {///if there is no such laptop on stock, delete it
						delete myList[it];
						myList[it] = nullptr;
						myList.erase(myList.begin() + it);
					}

					cout << "The total sum by now is: " << totalSum << ". \n";
				}
				cout << "Do you want to continue your shopping?(1-yes, 2-no): ";
				cin >> opt;
				cout << "\n\n";
				if (opt == 2) {
					cout << "The total sum is: " << totalSum << ". Thank you for choosing us! \n\n";
					cout << "Goodbye! \n";
					stop = true;
				}	
				it++;

			}
			
		}
		

	}
	exit(0);
}
*/
