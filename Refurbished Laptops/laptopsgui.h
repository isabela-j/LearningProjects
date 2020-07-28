#ifndef LAPTOPSGUI_H
#define LAPTOPSGUI_H

#include <QLineEdit>
#include <QMainWindow>
#include <QListWidget>
#include <QLabel>
#include <Repository.h>
#include "Controller.h"
class Controller;
class LaptopsGUI: public QMainWindow
{
    Q_OBJECT;

public:
    explicit LaptopsGUI(QWidget *parent=nullptr, Controller *ctrl=nullptr);
   // void setCtrl(Controller *ctrl);


signals:

public slots:
    void ctrlPopulate();
    void addWasPressed();
    void removeWasPressed();
    void updateWasPressed();

    void onRemovePlantTriggered();

    void onAddBuyPressed();

    void showDialogADD();
    void showDialogREMOVE();
    void showDialogUPDATE();
    void showDialogSEARCH();

    void onUndoActivated();
    void onRedoActivated();

private:
    Controller* m_controller;

    QListWidget* m_ctrlListWidget;
    QListWidget* m_toBuyWidget;
    double m_totalsum;

    ///widgets
    QWidget *createAddLaptopWidget();
    QWidget *createRemoveLaptopWidget();
    QWidget *createUpdateLaptopWidget();
    QWidget *createCentralWidget();
    QWidget *createHorizontalWidget();
    QWidget *createToBuyWidget();

    ///add new laptop, GUI elements
    QLineEdit* m_displaySizeEdit;
    QLineEdit* m_memorySizeEdit;
    QLineEdit* m_processorEdit;
    QLineEdit* m_priceEdit;
    QLineEdit* m_quantityEdit;
    QLineEdit* m_photoEdit;

    ///remove laptop
    QLineEdit* m_photoToRemove;

    ///update laptop
    QLineEdit* m_displayUpdated;
    QLineEdit* m_memoryUpdated;
    QLineEdit* m_procesorUpdated;
    QLineEdit* m_priceUpdated;
    QLineEdit* m_quantityUpdated;
    QLineEdit* m_photoUpdated;
    QLineEdit* m_searchedPhoto;

    ///total sum of the user
    QLabel* m_showsum;

};

#endif // LAPTOPSGUI_H
