#ifndef PARSER_H
#define PARSER_H

#include <OpenXLSX.hpp>
using namespace OpenXLSX;

#include <QVector>
#include <QString>
#include <QFile>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QStandardPaths>
#include <QDebug>


struct Lesson
{
    int _number;
    QString _name;
    QString _cabinet;
};


class Parser
{
public:
    Parser() = default;

    void readXLSX();
    void writeXML();
    QVector<QVector<Lesson*>> readXML();

private:
    int groupIndex(const QString& group);

    XLWorksheet _table;
    QVector<QVector<Lesson*>> _rawSchedule;
    QString _fileNameXML = "Schedule.xml";
};


#endif // PARSER_H
