#include "inforeader.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    InfoReader w;
    w.show();
    return a.exec();
}
