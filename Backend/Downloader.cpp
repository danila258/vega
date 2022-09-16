#include "Downloader.h"

Downloader::Downloader(const QString& fileName, const QString& filePath)
    : _fileNameXLSX(fileName), _standardPath(filePath)
{}

QString Downloader::getDownloadUrl()
{
    QNetworkReply* reply = _manager.get( QNetworkRequest(QUrl(_url)) );
    connect(reply, SIGNAL( finished() ), SLOT( slotDownloadSiteFinished() ));
    connect(reply, &QNetworkReply::errorOccurred, this, &Downloader::slotDownloadError);

    QEventLoop pause;
    connect(this, SIGNAL( resumeWork() ), &pause, SLOT( quit() ));
    pause.exec();

    QTextStream stream(&_htmlSite);

    while ( !stream.atEnd() )
    {
        QString line = stream.readLine();

        if (line.contains("xlsx"))
        {
            return parsingLine(line);
        }
    }

    return "";
}

void Downloader::downloadFile(const QString& url)
{
    QNetworkReply* reply = _manager.get( QNetworkRequest(QUrl(url)) );
    connect(reply, SIGNAL( finished() ), SLOT( slotDownloadFileFinished() ));
    connect(reply, &QNetworkReply::errorOccurred, this, &Downloader::slotDownloadError);

    QEventLoop pause;
    connect(this, SIGNAL(resumeWork()), &pause, SLOT(quit()));
    pause.exec();
}

QString Downloader::parsingLine(const QString& line)
{
    QString link;
    bool flag = false;

    for (auto& item : line)
    {
        if (flag)
        {
            if (item == '>')
            {
                return link;
            }

            link.push_back(item);
        }
        else if (item == '=')
        {
            flag = true;
        }

    }

    return "";
}

void Downloader::slotDownloadSiteFinished()
{
    _htmlSite = qobject_cast<QNetworkReply*>(sender())->readAll();
    sender()->deleteLater();

    emit( Downloader::resumeWork() );
}

void Downloader::slotDownloadFileFinished()
{
    QFile file(_standardPath + "/" + _fileNameXLSX);

    if ( !file.open(QIODevice::WriteOnly) )
    {
        throw std::runtime_error("file with site open error");
    }

    file.write( qobject_cast<QNetworkReply*>( sender())->readAll() );

    emit( resumeWork() );
}

void Downloader::slotDownloadError()
{
    qDebug() << "no internet";
}
