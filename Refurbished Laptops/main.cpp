
#include <QApplication>
#include "laptopsgui.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Repo<Laptop> rep;
    Controller* ctrl= new Controller(&rep);
    ctrl->loadFromFile("C:\\Users\\Isabela\\Desktop\\triallab10\\csvData9.txt");
    LaptopsGUI* laptopsUI=new LaptopsGUI({},ctrl);
    laptopsUI->show();
    return a.exec();
}
