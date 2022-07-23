#ifndef WIDGET_H
#define WIDGET_H

#include <Backend/Parser.h>
#include <QWidget>
#include <QLayout>
#include <QPushButton>
#include <QLabel>
#include <QFile>
#include <QDir>
#include <QDateTime>
#include <QResizeEvent>
#include <QGuiApplication>
#include <QScreen>


enum
{
    None = -1, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday
};


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

    void setInactiveStyle();    // it turns white
    void setActiveStyle();      // it turns accent color

    int _weekday;               // weekday = button index
};


class scheduleTab : public QWidget
{
    Q_OBJECT

public:
    explicit scheduleTab(QVector<QVector<Lesson*>> schedule, QWidget* parent = nullptr);

private:
    QHBoxLayout* createDayBarLayout();

    QHBoxLayout* createWideLayout();        // horizontal position of the phone or monitor
    QVBoxLayout* createNarrowLayout();      // vertical position of the phone or monitor

    bool checkOrientation(int width);       // return true if horizontal orientation

    QVBoxLayout* _scheduleTabLayout = new QVBoxLayout();

    bool _wideMode;                         // true - wide layout, false - narrow layout
    int _currentWeekday = None;             // if the narrow layout is equal to the index of the active button

    QVector<QString> _dayName = {"Пн", "Вт", "Ср", "Чт", "Пт", "Сб"};
    QVector<QVector<Lesson*>> _schedule;

protected:
    virtual void resizeEvent(QResizeEvent* event);      // switches layouts depending on the orientation of the device

public slots:
    void slotDayButtonClicked();
};


#endif // WIDGET_H
