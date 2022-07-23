#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QFile>
#include <QTextStream>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QDebug>


class Downloader
{
public:
    Downloader();

    QString getDownloadLink();
    void downloadXLSX(const QString& link);
};


#endif // DOWNLOADER_H
