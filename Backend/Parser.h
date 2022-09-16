#ifndef PARSER_H
#define PARSER_H

#include <OpenXLSX.hpp>
using namespace OpenXLSX;

#include <QVector>
#include <QString>
#include <QFile>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
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

    void readXLSX(const QString& directory, const QString& fileNameXLSX, int groupIndex);
    static QStringList groups(const QString& directory, const QString& fileNameXLSX);   // return all groups from file   
    void writeXML(const QString& directory, const QString& fileNameXML);
    static QVector<QVector<Lesson*>> readXML(const QString& directory, const QString& fileNameXML, int userSubgroup,
                                             int userWeek);

private:
    QVector<QVector<Lesson*>> _rawSchedule;
};


#endif // PARSER_H
