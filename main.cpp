#include "maindialog.h"
#include <QApplication>
int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    mainDialog diag;
    diag.show();
    return app.exec();
}
