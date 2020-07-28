#pragma once
#include "Laptop.h"
#include "Repository.h"
#include "CustomExceptions.h"
#include <fstream>
#include <sstream>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
class PersistenceEngine
{
public:
	virtual ~PersistenceEngine() = default;
	virtual void writeInFile(std::string document, std::vector<Laptop*> elems) = 0;
	virtual void readFromFile(std::string document, Repo<Laptop>* rep) = 0;
};


class PersistenceEngineFromCSV: public PersistenceEngine
{
public:
	PersistenceEngineFromCSV() {

	}
	~PersistenceEngineFromCSV() {

	}
	void writeInFile(std::string document, std::vector<Laptop*> elems) {
		ofstream wFile(document);
		if (wFile.is_open()) {
			if (elems.empty())
				throw ArrayOutOfBoundsException();
			for (int i = 0; i < elems.size(); i++)
            {
                std::string proc=elems[i]->getProcessor().toStdString();
                std::string photo=elems[i]->getPhoto().toStdString();
                wFile << elems[i]->getDisplaySize() << ";" << elems[i]->getMemorySize() << ";" << proc<< ";" << elems[i]->getPrice() << ";" << elems[i]->getQuantity() << ";" << photo<<"\n";
            }
             wFile.close();
		}
		else throw FileException(document);

	}
	void readFromFile(std::string document, Repo<Laptop>* rep) {
		ifstream rFile(document);
		if (rFile.is_open())
		{
			std::string line;
			std::vector<std::string> elems;
			///read line by line
			while (std::getline(rFile, line)) {

				/// read word by word
				std::vector<std::string> result;
				std::string temp;
				std::stringstream X(line);
				while (std::getline(X, temp, ';'))
					result.push_back(temp);

				if (result.empty())
					throw ArrayOutOfBoundsException();

				elems = result;

				///convert into what you need
				double dsize = std::stod(elems[0]);
				int mSize = std::stoi(elems[1]);
                QString processor = QString:: fromStdString(elems[2]);
				double price = std::stod(elems[3]);
				double quantity = std::stoi(elems[4]);
                QString photo = QString:: fromStdString(elems[5]);

				///add it to repository
				rep->addLaptop(new Laptop(dsize, mSize, processor, price, quantity, photo));
			}
			rFile.close();
		}
		else throw FileException(document);

	}
};


class PersistenceEngineFromJson : public PersistenceEngine
{
public:
	PersistenceEngineFromJson() {

	}
	~PersistenceEngineFromJson() {

	}
	void writeInFile(std::string document, std::vector<Laptop*> elems) {
		QJsonObject rootObj;

		QJsonArray laptopsArray;
		for (auto const& elem: elems)
		{
			///create a json object
			QJsonObject jsonObject;
			jsonObject.insert("display size", elem->getDisplaySize());
			jsonObject.insert("memory size", elem->getMemorySize());
            QString proc = elem->getProcessor();
			jsonObject.insert("processor generation", proc);
			jsonObject.insert("price", elem->getPrice());
			jsonObject.insert("quantity", elem->getQuantity());
            proc = elem->getPhoto();
			jsonObject.insert("photo", proc);

			laptopsArray.push_back(jsonObject);

		}

		rootObj["Laptops Array"] = laptopsArray;

		QJsonDocument jsondoc{ rootObj };
		QString jsonStr = jsondoc.toJson(QJsonDocument::Indented); //getting the representation	QString of this json document

		//saving jsonStr to the std:: string document
		ofstream outFile{ document };
		if (outFile.is_open()) {
			outFile << jsonStr.toStdString();
			outFile.close();
		}
		else throw FileException(document);

	}

	void readFromFile(std::string document, Repo<Laptop>* rep) {
		QString proc = QString::fromStdString(document);
		QFile file(proc);
		file.open(QIODevice::ReadOnly | QIODevice::Text);
		QByteArray jsonData = file.readAll();
		file.close();

		QJsonDocument jsondoc = QJsonDocument::fromJson(jsonData);
		QJsonObject obj = jsondoc.object();

		QJsonValue value = obj.value("Laptops Array");
		QJsonArray lapArray = value.toArray();

		foreach (const QJsonValue & v, lapArray)
		{
			double ds = v.toObject().value("display size").toDouble();
			int ms = v.toObject().value("memory size").toInt();
            QString qproc= v.toObject().value("processor generation").toString();

			double price= v.toObject().value("price").toDouble();
			int quantity= v.toObject().value("price").toInt();
            QString qphoto = v.toObject().value("photo").toString();


            Laptop* lap = new Laptop(ds, ms, qproc, price, quantity, qphoto);

			rep->addLaptop(lap);
		}

	}
};
