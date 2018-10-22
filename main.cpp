#include "xmlparsewidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication::setStyle("Fusion");
    QApplication a(argc, argv);

    XMLParseWidget w;
    w.show();

    return a.exec();
}
