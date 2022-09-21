#ifndef CUSTOMELEMENTS_H
#define CUSTOMELEMENTS_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QString>


class scheduleLabel : public QLabel
{
    Q_OBJECT

public:
    explicit scheduleLabel(const QString& str, QWidget* parent = nullptr);
};


class dayButton : public QPushButton
{
    Q_OBJECT

public:
    explicit dayButton(const QString& str, int weekday, QWidget* parent = nullptr);

    int _weekday;               // weekday = button index
};


class scheduleButton : public QPushButton
{
    Q_OBJECT

public:
    scheduleButton(QWidget* parent = nullptr);
};


class settingsButton : public QPushButton
{
    Q_OBJECT

public:
    settingsButton(QWidget* parent = nullptr);
};


#endif // CUSTOMELEMENTS_H
