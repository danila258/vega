#include "Parser.h"

void Parser::readXLSX()
{
    _rawSchedule.resize(6);

    XLDocument doc;
    std::string path = "/Users/danila/Downloads/2022spr8.xlsx";

    doc.open(path);
    _table = doc.workbook().worksheet("Table 1");

    QString group = "КМБО-02-21";

    int dayIndex = 0;
    int count = 0;
    int number = 0;
    int rowCount = _table.rowCount();
    int factor = groupIndex(group);
    bool cabinetFlag = false;

    for ( auto& row : _table.rows(3, rowCount - 2) )
    {
        if (row.cells(2, 2).begin()->value().typeAsString() == "integer")
        {
            number = row.cells(2, 2).begin()->value().get<int>();
            ++count;
        }

        for ( auto& rowCell : row.cells(3 + factor * 2, 4 + factor * 2) )
        {
            if (rowCell.value().typeAsString() == "string")
            {
                std::string str = rowCell.value().get<std::string>();

                if (cabinetFlag)
                {
                    _rawSchedule[dayIndex].back()->_cabinet =
                            QString::fromStdString( rowCell.value().get<std::string>() );
                    cabinetFlag = false;
                }
                else
                {
                    _rawSchedule[dayIndex].push_back(new Lesson{number,
                                                        QString::fromStdString( rowCell.value().get<std::string>() ),
                                                        QString::fromStdString("")}
                                                     );
                    cabinetFlag = true;
                }
            }
            else
            {
                cabinetFlag = false;
            }
        }

        if (count % 6 == 0)
        {
            ++dayIndex;
        }
    }

    doc.close();
}

int Parser::groupIndex(const QString& group)
{
    QString allGroups;
    int groupIndex = 0;

    for (auto& row : _table.rows(2))
    {
        for (auto& cell : row.cells(1))
        {
            allGroups = QString::fromStdString( cell.value().get<std::string>() );
        }
    }

    QList result = allGroups.split(" ");

    for (auto& item : result)
    {
        if ( item.isEmpty() )
        {
            continue;
        }

        if (item == group)
        {
            return groupIndex;
        }

        ++groupIndex;
    }

    return 0;
}

void Parser::writeXML()
{
    QString path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);

    if ( path.isEmpty() )
    {
        return;
    }

    QFile file(path + "/" + _fileNameXML);

    if ( !file.open(QIODevice::WriteOnly) )
    {
        return;
    }

    QXmlStreamWriter stream(&file);
    stream.setAutoFormatting(true);

    stream.writeStartDocument();
    stream.writeStartElement("schedule");

    for (auto& day : _rawSchedule)
    {
        stream.writeStartElement("day");

        for (auto& lesson : day)
        {
            stream.writeStartElement("lesson");
            stream.writeStartElement("week");

            QString name = lesson->_name;

            if ( name.contains("IIн") )
            {
                stream.writeCharacters("II");
                name.remove("IIн ", Qt::CaseInsensitive);
            }
            else if ( lesson->_name.contains("Iн") )
            {
                stream.writeCharacters("I");
                name.remove("Iн ", Qt::CaseInsensitive);
            }
            else
            {
                QString line;
                bool flag = true;

                while ( '0' <= name[0] && name[0] <= '9' || name[0] == ',' || name[0] == "н"[0] || name[0] == ' ')
                {
                    if ('0' <= name[0] && name[0] <= '9')
                    {
                        if (!flag)
                        {
                            line.append(" ");
                        }

                        line.append(name[0]);
                        flag = true;
                    }
                    else
                    {
                        flag = false;
                    }

                    name.remove(0, 1);
                }

                if ( !line.isEmpty() )
                {
                    stream.writeCharacters(line);
                }
            }

            stream.writeEndElement();
            stream.writeStartElement("subgroup");

            if ( name.contains("(1пг)") )
            {
                stream.writeCharacters("1");
                name.remove("(1пг)", Qt::CaseInsensitive);
            }
            else if ( name.contains("(1*пг)") )
            {
                stream.writeCharacters("1");
                name.remove("(1*пг)", Qt::CaseInsensitive);
            }
            else if ( name.contains("(2пг)") )
            {
                stream.writeCharacters("2");
                name.remove("(2пг)", Qt::CaseInsensitive);
            }
            else if ( name.contains("(2*пг)") )
            {
                stream.writeCharacters("2");
                name.remove("(2*пг)", Qt::CaseInsensitive);
            }

            stream.writeEndElement();
            stream.writeTextElement( "number", QString::number(lesson->_number) );

            if (name.back() == ' ')
            {
                name.remove(name.length() - 1, 1);
            }

            stream.writeTextElement("name", name);
            stream.writeTextElement("cabinet", lesson->_cabinet);
            stream.writeEndElement();
        }

        stream.writeEndElement();
    }

    stream.writeEndElement();
    stream.writeEndDocument();
}

QVector<QVector<Lesson*>> Parser::readXML()
{
    QString path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);

    if ( path.isEmpty() )
    {
        //return;
    }

    QFile file(path + "/" + _fileNameXML);

    if ( !file.open(QIODevice::ReadOnly) )
    {
        //return;
    }

    QXmlStreamReader stream(&file);

    QVector<QVector<Lesson*>> schedule(6);
    QString week;
    QString subgroup;
    QString number;
    QString name;
    QString cabinet;
    int index = 0;

    while ( !stream.atEnd() && !stream.hasError() )
    {
        stream.readNext();

        QString token = stream.name().toString();

        if ( stream.isStartElement() )
        {
            if (token == "week")
            {
                week = stream.readElementText();
            }
            else if (token == "subgroup")
            {
                subgroup = stream.readElementText();
            }
            else if (token == "number")
            {
                number = stream.readElementText();
            }
            else if (token == "name")
            {
                name = stream.readElementText();
            }
            else if (token == "cabinet")
            {
                cabinet = stream.readElementText();
            }
        }
        else
        {
            if (token == "day")
            {
                ++index;
            }
            else if (token == "lesson")
            {
                schedule[index].push_back(new Lesson{number.toInt(), name, cabinet});
            }
        }
    }

    for (auto& a : schedule)
    {
        qDebug() << a.length();

        for (auto& b : a)
        {
            qDebug() << b->_name;
        }
    }

    return schedule;
}
