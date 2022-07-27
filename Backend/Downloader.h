#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QFile>
#include <QTextStream>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QEventLoop>


class Downloader : public QObject
{
    Q_OBJECT

public:
    Downloader(const QString& fileName, const QString& filePath);

    QString getDownloadLink();
    void downloadFile(const QString& url);

private:
    static QString lineParser(const QString& line);

    QNetworkAccessManager _manager;
    QString _htmlSite;
    QString _fileNameXLSX;
    QString _standardPath;
    QString _url = "https://vega.fcyb.mirea.ru";

private slots:
    void slotDownloadSiteFinished();
    void slotDownloadFileFinished();
    void slotDownloadError();

signals:
    void resumeWork();
};


#endif // DOWNLOADER_H
