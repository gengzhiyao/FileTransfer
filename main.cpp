#include <QApplication>
#include <QPushButton>
#include "transfileclient.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TransFileClient widget;
    widget.show();
    return a.exec();
}
