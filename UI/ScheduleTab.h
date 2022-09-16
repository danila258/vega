#ifndef WIDGET_H
#define WIDGET_H

#include "Backend/Parser.h"
#include "CustomElements.h"
#include "CommonFunctions.h"

#include <QWidget>
#include <QLayout>
#include <QPushButton>
#include <QLabel>
#include <QFile>
#include <QDir>
#include <QDateTime>
#include <QResizeEvent>
#include <QSizePolicy>

#include <array>

enum
{
    NONE = -1, MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY, SUNDAY
};


class ScheduleTab : public QWidget
{
    Q_OBJECT

public:
    explicit ScheduleTab(const QVector<QVector<Lesson*>>& schedule, bool showEmptyLessons, QWidget* parent = nullptr);

private:
    QHBoxLayout* createDayBarLayout();       // top buttons
    QHBoxLayout* createWideLayout();         // horizontal position of the phone or monitor
    QVBoxLayout* createNarrowLayout();       // vertical position of the phone or monitor
    QString getFormatText(Lesson* lesson);   // return html text
    int getWeekdayNumber();

    QVBoxLayout* _scheduleTabLayout;

    bool _wideMode;                         // true - wide layout, false - narrow layout
    bool _showEmptyLessons;
    int _currentWeekday = NONE;             // if the narrow layout - is equal to the index of the active button

    std::array<QString, 6> _dayName = {"Пн", "Вт", "Ср", "Чт", "Пт", "Сб"};
    std::array<QString, 7> _lessonTime = {" 9:00 - 10:30", "10:40 - 12:10", "12:40 - 14:10", "14:20 - 15:50",
                                          "16:20 - 17:50", "18:00 - 19:30", "19:40 - 21:00"};
    QVector<QVector<Lesson*>> _schedule;

protected:
    void resizeEvent(QResizeEvent* event) override;      // switches layouts depending on the orientation of the device

public slots:
    void slotDayButtonClicked();
};


#endif // WIDGET_H
