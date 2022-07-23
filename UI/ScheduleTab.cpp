#include "ScheduleTab.h"

scheduleLabel::scheduleLabel(const QString& str, QWidget* parent) : QLabel(str, parent)
{
    QFile style(":/scheduleLabel.qss");
    style.open(QFile::ReadOnly);
    setStyleSheet( style.readAll() );
}


dayButton::dayButton(const QString& str, int weekday, QWidget* parent) : QPushButton(str, parent),
    _weekday(weekday)
{
    setInactiveStyle();
}

void dayButton::setInactiveStyle()
{
    QFile style(":/dayButton_Inactive.qss");
    style.open(QFile::ReadOnly);
    setStyleSheet( style.readAll() );
}

void dayButton::setActiveStyle()
{
    QFile style(":/dayButton_Active.qss");
    style.open(QFile::ReadOnly);
    setStyleSheet( style.readAll() );
}


scheduleTab::scheduleTab(QVector<QVector<Lesson*>> schedule, QWidget* parent) : QWidget(parent), _schedule(schedule)
{
    _scheduleTabLayout->addLayout( createDayBarLayout() );

    if (checkOrientation( geometry().width() ))
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

QHBoxLayout* scheduleTab::createDayBarLayout() {
    QHBoxLayout* dayBarLayout = new QHBoxLayout();

    for (int i = 0; i < _dayName.length(); ++i)
    {
        dayButton* button = new dayButton(_dayName[i], i);

        dayBarLayout->addWidget(button);
        dayBarLayout->setAlignment(button, Qt::AlignHCenter);

        connect(button, SIGNAL( clicked() ), SLOT( slotDayButtonClicked() ));
    }

    return dayBarLayout;
}

QHBoxLayout* scheduleTab::createWideLayout()
{
    _wideMode = true;

    QHBoxLayout* wideLayout = new QHBoxLayout();

    for (int i = 0; i < _dayName.length(); ++i)
    {
        QVBoxLayout* columnLayout = new QVBoxLayout();
        columnLayout->setAlignment(Qt::AlignTop);

        for (auto&& label : _schedule[i])
        {
            columnLayout->addWidget( new scheduleLabel(label->_name) );
        }

        wideLayout->addLayout(columnLayout);
    }

    if (_currentWeekday != None)
    {
        qobject_cast<dayButton*>( _scheduleTabLayout->itemAt(0)->layout()->itemAt(_currentWeekday)->widget() )
                ->setInactiveStyle();
    }

    return wideLayout;
}

QVBoxLayout* scheduleTab::createNarrowLayout()
{
    QDateTime time;
    int weekday = time.currentDateTime().date().dayOfWeek() - 1;    // monday = 0, tuesday = 1 ...

    if (weekday == Sunday || weekday == None)
    {
        weekday = Monday;
    }

    if (_wideMode)
    {
        weekday = _currentWeekday;
    }
    else
    {
        _currentWeekday = weekday;
    }

    _wideMode = false;

    qobject_cast<dayButton*>( _scheduleTabLayout->itemAt(0)->layout()->itemAt(weekday)->widget() )
            ->setActiveStyle();

    QVBoxLayout* narrowLayout = new QVBoxLayout();
    narrowLayout->setAlignment(Qt::AlignTop);

    for (auto&& lesson : _schedule[weekday])
    {
        narrowLayout->addWidget( new scheduleLabel(lesson->_name) );
    }

    return narrowLayout;
}

bool scheduleTab::checkOrientation(int width)
{
    #if defined(Q_OS_IOS) || defined(Q_OS_ANDROID)

        if (QGuiApplication::primaryScreen()->primaryOrientation() == Qt::LandscapeOrientation)
        {
            return true;
        }

        return false;

    #else

        if (width > 700)
        {
            return true;
        }

        return false;

    #endif
}

void scheduleTab::resizeEvent(QResizeEvent* event) {
    if (checkOrientation( event->size().width() ))
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

void scheduleTab::slotDayButtonClicked()
{
    if (_wideMode)    // in wideMode dayQPushButtons not active
    {
        return;
    }

    int weekday = qobject_cast<dayButton*>( sender() )->_weekday;    // weekday = button index

    if (weekday == _currentWeekday)
    {
        return;
    }

    qobject_cast<dayButton*>( _scheduleTabLayout->itemAt(0)->layout()->itemAt(_currentWeekday)->widget() )
            ->setInactiveStyle();

    _currentWeekday = weekday;

    qobject_cast<dayButton*>( _scheduleTabLayout->itemAt(0)->layout()->itemAt(weekday)->widget() )
            ->setActiveStyle();

    QVBoxLayout* narrowLayout = qobject_cast<QVBoxLayout*>( _scheduleTabLayout->itemAt(1)->layout() );

    while ( !narrowLayout->isEmpty() )
    {
        narrowLayout->takeAt(0)->widget()->deleteLater();
    }

    for (auto&& lesson : _schedule[weekday])
    {
         narrowLayout->addWidget( new scheduleLabel(lesson->_name) );
    }
}
