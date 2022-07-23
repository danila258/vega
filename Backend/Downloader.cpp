#include "Downloader.h"

Downloader::Downloader()
{
    QFile file("/Users/danila/Downloads/Вега — МИРЭА.html");
    file.open(QIODevice::ReadOnly);

    QTextStream in(&file);

    while(!in.atEnd()) {
        QString line = in.readLine();
        qDebug() << line;
    }
}

QString Downloader::getDownloadLink()
{
    int a = 5;
    return "df";
//    QNetworkAccessManager *manager = new QNetworkAccessManager();
//    connect(manager, SIGNAL(QNetworkAccessManager::finished), SLOT(replyFinished));

//    manager->get(QNetworkRequest(QUrl("http://qt-project.org")));
}
