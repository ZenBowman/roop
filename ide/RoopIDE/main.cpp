#include "roopenvironment.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RoopEnvironment w;
    w.show();

    return a.exec();
}
