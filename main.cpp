#include "LumaX.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LumaX w;
    w.show();
    return a.exec();
}
