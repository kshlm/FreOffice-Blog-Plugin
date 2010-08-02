#include "maindialog.h"
#include <QApplication>
int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    app.setOverrideCursor(QCursor(Qt::BlankCursor));
    mainDialog diag;
    diag.show();
    return app.exec();
}
