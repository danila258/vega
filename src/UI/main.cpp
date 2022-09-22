#include "MainWidget.h"

#include <QApplication>


int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    app.setOrganizationDomain("https://github.com/danila258/Vega");
    app.setApplicationName("Vega");
    
    #if defined(Q_OS_WIN)
        QFont serifFont("Times", 14);
        QApplication::setFont(serifFont);
    #endif

    MainWidget* Vega = new MainWidget();
    Vega->show();

    return app.exec();
}
