#include "mainwindow.h"
#include <QApplication>
#include "myhelper.h"
#include "configapp.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    myHelper::SetStyle("black");//黑色风格
    ConfigApp::initApp();
    MainWindow w;
    w.show();

    return a.exec();
}
