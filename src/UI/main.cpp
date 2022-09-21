#include "MainWidget.h"

#include <QApplication>


int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    app.setOrganizationDomain("https://github.com/danila258/Vega");
    app.setApplicationName("Vega");

    MainWidget* Vega = new MainWidget();
    Vega->show();

    return app.exec();
}
