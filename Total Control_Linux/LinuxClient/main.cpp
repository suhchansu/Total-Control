
#include <QApplication>
#include "mainclient.h"


int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    MainClient *mc = new MainClient();
    mc->show();

    return app.exec();
}
