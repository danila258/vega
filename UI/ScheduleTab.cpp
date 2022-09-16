#include "ScheduleTab.h"

ScheduleTab::ScheduleTab(const QVector<QVector<Lesson*>>& schedule, bool showEmptyLessons, QWidget* parent)
    : QWidget(parent), _schedule(schedule), _showEmptyLessons(showEmptyLessons), _scheduleTabLayout( new QVBoxLayout() )
{
    _scheduleTabLayout->addLayout( createDayBarLayout() );

    if ( checkOrientation(parent) )
    {
        _wideMode = true;
        _scheduleTabLayout->addLayout( createWideLayout() );
    }
    else
    {
        _wideMode = false;
        _scheduleTabLayout->addLayout( createNarrowLayout() );
    }

    setLayout(_scheduleTabLayout);
}

QHBoxLayout* ScheduleTab::createDayBarLayout() {
    QHBoxLayout* dayBarLayout = new QHBoxLayout();

    for (int i = 0; i < _dayName.size(); ++i)
    {
        dayButton* button = new dayButton(_dayName[i], i);

        dayBarLayout->addWidget(button);
        dayBarLayout->setAlignment(button, Qt::AlignHCenter);

        connect(button, SIGNAL( clicked() ), SLOT( slotDayButtonClicked() ));
    }

    return dayBarLayout;
}

QHBoxLayout* ScheduleTab::createWideLayout()
{
    int weekday = getWeekdayNumber();

    qobject_cast<dayButton*>( _scheduleTabLayout->itemAt(0)->layout()->itemAt(weekday)->widget() )
            ->setChecked(true);
    qobject_cast<dayButton*>( _scheduleTabLayout->itemAt(0)->layout()->itemAt(weekday)->widget() )
            ->setDisabled(true);

    _wideMode = true;

    QHBoxLayout* wideLayout = new QHBoxLayout();

    for (int i = 0; i < _dayName.size(); ++i)
    {
        int lastNumber = 1;

        QVBoxLayout* columnLayout = new QVBoxLayout();
        columnLayout->setAlignment(Qt::AlignTop);

        for (auto&& lesson : _schedule[i])
        {            
            if (_showEmptyLessons)
            {
                while (lastNumber != lesson->_number)
                {
                    scheduleLabel* label = new scheduleLabel( getFormatText(new Lesson{lastNumber,
                                                                                       QString::fromStdString(""),
                                                                                       QString::fromStdString("")}
                                                                            ));
                    label->setSizePolicy(QSizePolicy::Ignored , QSizePolicy::Ignored);
                    columnLayout->addWidget(label);
                    ++lastNumber;
                }
            }

            scheduleLabel* label = new scheduleLabel( getFormatText(lesson) );
            label->setSizePolicy(QSizePolicy::Ignored , QSizePolicy::Ignored);
            columnLayout->addWidget(label);
            ++lastNumber;
        }

        if (_schedule[i].length() == 0)
        {
            QLabel* hiddenLabel = new QLabel();

            QSizePolicy policy = hiddenLabel->sizePolicy();
            policy.setRetainSizeWhenHidden(true);

            hiddenLabel->setSizePolicy(policy);
            hiddenLabel->hide();

            columnLayout->addWidget(hiddenLabel);
        }

        wideLayout->addLayout(columnLayout);
    }

    return wideLayout;
}

QVBoxLayout* ScheduleTab::createNarrowLayout()
{
    int weekday = getWeekdayNumber();
    int lastNumber = 1;

    qobject_cast<dayButton*>( _scheduleTabLayout->itemAt(0)->layout()->itemAt(weekday)->widget() )
            ->setChecked(true);
    qobject_cast<dayButton*>( _scheduleTabLayout->itemAt(0)->layout()->itemAt(weekday)->widget() )
            ->setDisabled(true);

    _wideMode = false;

    QVBoxLayout* narrowLayout = new QVBoxLayout();
    narrowLayout->setAlignment(Qt::AlignTop);

    for (auto&& lesson : _schedule[weekday])
    {
        if (_showEmptyLessons)
        {
            while (lastNumber != lesson->_number)
            {
                narrowLayout->addWidget(new scheduleLabel( getFormatText(new Lesson{lastNumber,
                                                                                   QString::fromStdString(""),
                                                                                   QString::fromStdString("")}
                                                                         )));
                ++lastNumber;
            }
        }

        narrowLayout->addWidget(new scheduleLabel( getFormatText(lesson) ));
        ++lastNumber;
    }

    if (_schedule[weekday].length() == 0)
    {
        QLabel* label = new QLabel("Пар нет");
        narrowLayout->addWidget(label);
        narrowLayout->setAlignment(Qt::AlignCenter);
    }

    return narrowLayout;
}

QString ScheduleTab::getFormatText(Lesson* lesson)
{
    QString time;

    if (_wideMode)
    {
        time = QString::number(lesson->_number) + ". ";
    }
    else
    {
        time = _lessonTime[lesson->_number - 1] + "   ";
    }

    return QString("<table width=\"100%\">\
                    <td width=\"50%\" align=\"left\"><pre>%1</pre></td>\
                    <td width=\"50%\" align=\"right\">%2</td>\
                    </table>").arg(time + lesson->_name).arg(lesson->_cabinet);
}

int ScheduleTab::getWeekdayNumber()
{
    QDateTime time;
    int weekday = time.currentDateTime().date().dayOfWeek() - 1;    // monday = 0, tuesday = 1 ...

    if (weekday == SUNDAY || weekday == NONE)
    {
        weekday = MONDAY;
    }

    if (_currentWeekday != NONE)
    {
        weekday = _currentWeekday;
    }
    else
    {
        _currentWeekday = weekday;
    }

    return weekday;
}

void ScheduleTab::resizeEvent(QResizeEvent* event) {
    if ( checkOrientation(this) )
    {
        if (_wideMode)
        {
            return;
        }

        QVBoxLayout* QLabelLayout = qobject_cast<QVBoxLayout*>( _scheduleTabLayout->itemAt(1)->layout() );

        while ( !QLabelLayout->isEmpty() )
        {
            QLabelLayout->takeAt(0)->widget()->deleteLater();
        }

        QLabelLayout->deleteLater();

        _scheduleTabLayout->addLayout( createWideLayout() );
        _wideMode = true;
    }
    else
    {
        if (!_wideMode)
        {
            return;
        }

        QHBoxLayout* QLabelLayout = qobject_cast<QHBoxLayout*>( _scheduleTabLayout->itemAt(1)->layout() );

        while ( !QLabelLayout->isEmpty() )
        {
            while ( !QLabelLayout->itemAt(0)->layout()->isEmpty() )
            {
                QLabelLayout->itemAt(0)->layout()->takeAt(0)->widget()->deleteLater();
            }

            QLabelLayout->takeAt(0)->layout()->deleteLater();
        }

        QLabelLayout->deleteLater();

        _scheduleTabLayout->addLayout( createNarrowLayout() );
        _wideMode = false;
    }
}

void ScheduleTab::slotDayButtonClicked()
{
    int weekday = qobject_cast<dayButton*>( sender() )->_weekday;    // weekday = button index

    if (weekday == _currentWeekday)
    {
        return;
    }

    qobject_cast<dayButton*>( _scheduleTabLayout->itemAt(0)->layout()->itemAt(_currentWeekday)->widget() )
            ->setChecked(false);
    qobject_cast<dayButton*>( _scheduleTabLayout->itemAt(0)->layout()->itemAt(_currentWeekday)->widget() )
            ->setDisabled(false);

    _currentWeekday = weekday;

    qobject_cast<dayButton*>( _scheduleTabLayout->itemAt(0)->layout()->itemAt(weekday)->widget() )
            ->setChecked(true);
    qobject_cast<dayButton*>( _scheduleTabLayout->itemAt(0)->layout()->itemAt(weekday)->widget() )
            ->setDisabled(true);

    if (_wideMode)
    {
        return;
    }

    QVBoxLayout* narrowLayout = qobject_cast<QVBoxLayout*>( _scheduleTabLayout->itemAt(1)->layout() );
    narrowLayout->setAlignment(Qt::AlignTop);

    while ( !narrowLayout->isEmpty() )
    {
        narrowLayout->takeAt(0)->widget()->deleteLater();
    }

    int lastNumber = 1;

    for (auto&& lesson : _schedule[weekday])
    {
        if (_showEmptyLessons)
        {
            while (lastNumber != lesson->_number)
            {
                narrowLayout->addWidget(new scheduleLabel( getFormatText(new Lesson{lastNumber,
                                                                                   QString::fromStdString(""),
                                                                                   QString::fromStdString("")}
                                                                         )));
                ++lastNumber;
            }
        }

        narrowLayout->addWidget(new scheduleLabel( getFormatText(lesson) ));
        ++lastNumber;
    }

    if (_schedule[weekday].length() == 0)
    {
        QLabel* label = new QLabel("Пар нет");
        narrowLayout->addWidget(label);
        narrowLayout->setAlignment(Qt::AlignCenter);
    }
}
