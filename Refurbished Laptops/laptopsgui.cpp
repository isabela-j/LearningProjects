#include "laptopsgui.h"
#include <QFrame>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QDebug>
#include <QFileDialog>
#include <QIcon>
#include <QStatusBar>
#include <QWidget>
#include <QPalette>
#include <QMenu>
#include <QMenuBar>
#include <QShortcut>
#include <QRegularExpression>
LaptopsGUI:: LaptopsGUI(QWidget *parent, Controller *ctrl): QMainWindow(parent)
{

    this->setWindowTitle("Laptops");
    this->setMinimumSize(QSize(200,300));
    m_controller=ctrl;
    m_totalsum=0;
    QMenu *fileMenu= this->menuBar()->addMenu("&File");
    QAction *removeLaptopAction=new QAction("Remove laptop");
    fileMenu->addAction(removeLaptopAction);
    connect(removeLaptopAction, &QAction::triggered, this, &LaptopsGUI::onRemovePlantTriggered);

    QWidget *centralW=createCentralWidget();
    this->setCentralWidget(centralW);
}


void LaptopsGUI::ctrlPopulate()
{
    QVector<Laptop*> laptop_ctrl= m_controller->ctrl();
    m_ctrlListWidget->clear();
   for(auto it: laptop_ctrl){
        if(!it->getPhoto().isEmpty())
        {
            QIcon icon(it->getPhoto());
            if(!icon.isNull())
            {
                new QListWidgetItem(icon, it->getProcessor(),m_ctrlListWidget);
            }
            else new QListWidgetItem(it->getProcessor(),m_ctrlListWidget);
        }
        else new QListWidgetItem(it->getProcessor(),m_ctrlListWidget);
    }
}

void LaptopsGUI::addWasPressed()
{
    Laptop *lap=new Laptop(0,0,"",0,0,"");
    lap->setDisplaySize(m_displaySizeEdit->text().toDouble());
    lap->setMemorySize(m_memorySizeEdit->text().toInt());
    lap->setProcessor(m_processorEdit->text());
    lap->setPrice(m_priceEdit->text().toDouble());
    lap->setQuantity(m_quantityEdit->text().toInt());
    lap->setPhoto(m_photoEdit->text());

    m_controller->addALaptop(lap);
    ctrlPopulate();
    m_controller->addToUndo(lap, 1);
}

void LaptopsGUI::removeWasPressed()
{
    QString s= m_photoToRemove->text();
    int index=m_controller->findIndex(s);
    if(index!=-1)
   { Laptop *lap=m_controller->getLaptopFromThisIndex(index);

    Laptop *laptopRemoved= new Laptop(lap->getDisplaySize(),lap->getMemorySize(),lap->getProcessor(), lap->getPrice(),lap->getQuantity(), lap->getPhoto());

    m_controller->removeEntireLaptop(s);
    ctrlPopulate();
    m_controller->addToUndo(laptopRemoved,2);
    }
    else cout<<"Laptop not found";
}

void LaptopsGUI::updateWasPressed()
{
    Laptop *lap= new Laptop(0,0,"",0,0,"");
    lap->setDisplaySize(m_displayUpdated->text().toDouble());
    lap->setMemorySize(m_memoryUpdated->text().toInt());
    lap->setProcessor(m_procesorUpdated->text());
    lap->setPrice(m_priceUpdated->text().toDouble());
    lap->setQuantity(m_quantityUpdated->text().toInt());
    lap->setPhoto(m_photoUpdated->text());

    QString str=m_searchedPhoto->text();

    m_controller->updateALaptop(str,lap);
    ctrlPopulate();
}

void LaptopsGUI::onRemovePlantTriggered()
{
    QWidget *removeLaptop= createRemoveLaptopWidget();
    removeLaptop->show();
}

void LaptopsGUI::onAddBuyPressed()
{
 int selectedIndex=m_ctrlListWidget->currentRow();
 if(selectedIndex<0)
     return;
 Laptop lap= *m_controller->ctrl()[selectedIndex];
 bool inserted=m_controller->addToBuy(lap);
 m_totalsum+=lap.getPrice();
 QString sum= "Total sum is: "+ QString::number(m_totalsum) + " RON";
 m_showsum->setText(sum);
 if(inserted)
 {
     m_toBuyWidget->addItem(lap.getProcessor());
 }
}

void LaptopsGUI::showDialogADD()
{
    QString path;
    path=QFileDialog::getOpenFileName(this,"Select picture","","(*.jpg *.png)");
    path.replace("/","\\\\");
    m_photoEdit->setText(path);

}

void LaptopsGUI::showDialogREMOVE()
{
    QString path;
    path=QFileDialog::getOpenFileName(this,"Select picture","","(*.jpg *.png)");
    path.replace("/","\\\\");
    m_photoToRemove->setText(path);
}

void LaptopsGUI::showDialogUPDATE()
{
    QString path;
    path=QFileDialog::getOpenFileName(this,"Select picture","","(*.jpg *.png)");
    path.replace("/","\\\\");
    m_photoUpdated->setText(path);
}

void LaptopsGUI::showDialogSEARCH()
{
    QString path;
    path=QFileDialog::getOpenFileName(this,"Select picture","","(*.jpg *.png)");
    m_searchedPhoto->setText(path);
}

void LaptopsGUI::onUndoActivated()
{
    m_controller->undoOPERATION();
    ctrlPopulate();
    std::cout<<"Undo was done. \n";
}

void LaptopsGUI::onRedoActivated()
{
    m_controller->redoOPERATION();
    ctrlPopulate();
    std::cout<<"Redo was done. \n";
}

QWidget *LaptopsGUI::createAddLaptopWidget()
{
    //create widget
    QWidget *widget=new QWidget(this);

    //create grid layout
    QGridLayout *grid=new QGridLayout(this);

    //elements for grid label
    QLabel *labelDS= new QLabel("Display Size",this);
    m_displaySizeEdit= new QLineEdit(this);
    QLabel *labelMS=new QLabel("Memory size",this);
    m_memorySizeEdit= new QLineEdit(this);
    QLabel *labelProc=new QLabel("Processor",this);
    m_processorEdit=new QLineEdit(this);
    QLabel *labelPrice=new QLabel("Price",this);
    m_priceEdit=new QLineEdit(this);
    QLabel *labelQuantity=new QLabel("Quantity",this);
    m_quantityEdit=new QLineEdit(this);
    QLabel *labelPhoto=new QLabel("Photo",this);
    m_photoEdit=new QLineEdit(this);

    QPushButton *browseButton= new QPushButton("Browse", this);
    QPushButton *addButton=new QPushButton("Add", this);

    //add the elements to the grid
    grid->addWidget(labelDS, 0,0);
    grid->addWidget(m_displaySizeEdit, 0,1,1,2); //line 0, col 0, se extine pe 1 singura linie, se extinde pe 2 coloane
    grid->addWidget(labelMS,1,0);
    grid->addWidget(m_memorySizeEdit,1,1,1,2);
    grid->addWidget(labelProc,2,0);
    grid->addWidget(m_processorEdit,2,1,1,2);
    grid->addWidget(labelPrice,3,0);
    grid->addWidget(m_priceEdit,3,1,1,2);
    grid->addWidget(labelQuantity,4,0);
    grid->addWidget(m_quantityEdit,4,1,1,2);
    grid->addWidget(labelPhoto,5,0);
    grid->addWidget(m_photoEdit,5,1);
    grid->addWidget(browseButton,5,2);
    grid->addWidget(addButton,6,2);

    widget->setLayout(grid);

    connect(addButton, &QPushButton::pressed, this, &LaptopsGUI::addWasPressed);
    connect(browseButton, &QPushButton::pressed, this, &LaptopsGUI::showDialogADD);

    return widget;
}

QWidget *LaptopsGUI:: createRemoveLaptopWidget()
{
    QWidget* widget=new QWidget(); // we will not specify by "this" because
    //it will not show it properly when we create a pop up widget

    QGridLayout* layout=new QGridLayout(this);

    QLabel *labelPhoto=new QLabel("Photo",this);
    m_photoToRemove=new QLineEdit(this);

    QPushButton* browseButton=new QPushButton("Browse",this);
    QPushButton* removeButton=new QPushButton("Remove", this);

    layout->addWidget(labelPhoto, 0,0);
    layout->addWidget(m_photoToRemove,0,1);
    layout->addWidget(browseButton,0,2);
    layout->addWidget(removeButton,1,2);

    widget->setLayout(layout);

    connect(removeButton, &QPushButton::pressed, this, &LaptopsGUI::removeWasPressed);
    connect(browseButton, &QPushButton::pressed, this, &LaptopsGUI::showDialogREMOVE);

    return widget;
}

QWidget *LaptopsGUI::createUpdateLaptopWidget()
{
    QWidget *widget= new QWidget(this);

    QGridLayout *layout= new QGridLayout(this);

    //new data
    QLabel *display=new QLabel("New display size",this);
    m_displayUpdated= new QLineEdit(this);
    QLabel* memory=new QLabel("New memory size", this);
    m_memoryUpdated=new QLineEdit(this);
    QLabel *proc=new QLabel("New processor", this);
    m_procesorUpdated=new QLineEdit(this);
    QLabel* price=new QLabel("New price", this);
    m_priceUpdated=new QLineEdit(this);
    QLabel *quantity=new QLabel("New quantity",this);
    m_quantityUpdated=new QLineEdit(this);
    QLabel *photo=new QLabel("New photo", this);
    m_photoUpdated=new QLineEdit(this);

    //searched laptop
    QLabel *searched=new QLabel("Searched photo",this);
    m_searchedPhoto=new QLineEdit(this);

    //buttons
    QPushButton *browseUpdate=new QPushButton("Browse",this);
    QPushButton *browseSearch=new QPushButton("Browse",this);
    QPushButton *update=new QPushButton("Update",this);

    layout->addWidget(display,0,0);
    layout->addWidget(m_displayUpdated,0,1,1,2);
    layout->addWidget(memory,1,0);
    layout->addWidget(m_memoryUpdated,1,1,1,2);
    layout->addWidget(proc,2,0);
    layout->addWidget(m_procesorUpdated,2,1,1,2);
    layout->addWidget(price,3,0);
    layout->addWidget(m_priceUpdated,3,1,1,2);
    layout->addWidget(quantity,4,0);
    layout->addWidget(m_quantityUpdated,4,1,1,2);
    layout->addWidget(photo,5,0);
    layout->addWidget(m_photoUpdated,5,1);
    layout->addWidget(browseUpdate, 5,2);
    layout->addWidget(searched,7,0);
    layout->addWidget(m_searchedPhoto,7,1);
    layout->addWidget(browseSearch,7,2);
    layout->addWidget(update,8,2);

    widget->setLayout(layout);

    connect(update,&QPushButton::pressed, this, &LaptopsGUI::updateWasPressed);
    connect(browseUpdate,&QPushButton::pressed, this, &LaptopsGUI::showDialogUPDATE);
    connect(browseSearch,&QPushButton::pressed,this, &LaptopsGUI::showDialogSEARCH);


    return widget;
}
QWidget *LaptopsGUI::createHorizontalWidget()
{
    QWidget *widget=new QWidget(this);

    QWidget *addNewLaptop= createAddLaptopWidget();
    QWidget *removeLaptop= createRemoveLaptopWidget();
    QWidget *updateLaptop= createUpdateLaptopWidget();

    QHBoxLayout *hBoxLayout=new QHBoxLayout;

    //add
    hBoxLayout->addWidget(addNewLaptop);

    QFrame* line1=new QFrame(this);
    line1->setFrameShape(QFrame::VLine);
    line1->setFrameShadow(QFrame::Sunken);
    hBoxLayout->addWidget(line1);

    //remove
    hBoxLayout->addWidget(removeLaptop);

    ///separate again
    QFrame* line2=new QFrame(this);
    line2->setFrameShape(QFrame::VLine);
    line2->setFrameShadow(QFrame::Sunken);
    hBoxLayout->addWidget(line2);

    ///update
    hBoxLayout->addWidget(updateLaptop);

    widget->setLayout(hBoxLayout);
    return widget;
}

QWidget *LaptopsGUI::createToBuyWidget()
{
    QWidget *widget=new QWidget(this);
    QVBoxLayout *vertical= new QVBoxLayout;

    QPushButton *load=new QPushButton("load repo",this);
    vertical->addWidget(load,1, Qt::AlignCenter);
    vertical->addWidget(m_ctrlListWidget);

    widget->setLayout(vertical);

    connect(load,&QPushButton::pressed, this, &LaptopsGUI::ctrlPopulate);

    return widget;

}

QWidget *LaptopsGUI:: createCentralWidget()
{
    QWidget *widget=new QWidget(this);
    QVBoxLayout *vBoxLayout=new QVBoxLayout;
    m_ctrlListWidget=new QListWidget(this);
    m_toBuyWidget=new QListWidget(this);

    //add, update, remove widget - which is horizontal
    QWidget *horizontal=createHorizontalWidget();
    vBoxLayout->addWidget(horizontal);


    QFrame* line1=new QFrame(this);
    line1->setFrameShape(QFrame::HLine);
    line1->setFrameShadow(QFrame::Sunken);
    vBoxLayout->addWidget(line1);

    QWidget *horiz2 =createToBuyWidget();
    vBoxLayout->addWidget(horiz2);

    QPushButton *buy= new QPushButton("buy",this);
    vBoxLayout->addWidget(buy,1, Qt::AlignCenter);

    //add items for buying


    vBoxLayout->addWidget(m_toBuyWidget);


    QString sum= "Total sum is: "+ QString::number(m_totalsum) + " RON";
    m_showsum=new QLabel(sum,this);

    vBoxLayout->addWidget(m_showsum);

    //create shortcuts
    QShortcut* und=new QShortcut(QKeySequence(tr("Ctrl+x", "File|Open")),this);
    QShortcut* red=new QShortcut(QKeySequence(tr("Ctrl+z", "File|Open")),this);

    widget->setLayout(vBoxLayout);

    connect(und,&QShortcut::activated,this, &LaptopsGUI::onUndoActivated);
    connect(red,&QShortcut::activated,this, &LaptopsGUI::onRedoActivated);

    connect(buy,&QPushButton::pressed, this, &LaptopsGUI::onAddBuyPressed);

    QPalette pal= palette();
    pal.setColor(QPalette::Background, Qt::darkCyan);
    widget->setAutoFillBackground(true);
    widget->setPalette(pal);
    return widget;

}







