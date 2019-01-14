#include "stdafx.h"
#include "life.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Life w;
    w.show();
    return a.exec();
}
