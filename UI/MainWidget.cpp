#include "MainWidget.h"

MainWidget::MainWidget(QWidget* parent) : QWidget(parent), _mainLayout( new QVBoxLayout() )
{
    appConfig();

    if (_showEmptyLessons)
    {
        this->setFixedHeight( this->height() + EXTRA_SIZE );
    }
    else
    {
        this->setFixedHeight( this->height() );
    }

    Downloader downloader(_fileNameXLSX, _standardPath);
    QString url;
    Parser parser;

    slotCheckSystemTheme();
    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL( timeout() ), this, SLOT( slotCheckSystemTheme() ));
    timer->start(100);

    try
    {
        url = downloader.getDownloadUrl();

        if ( (_url != url || !_settings.contains("/Settings/url")) && !url.isEmpty() )
        {
            _url = url;
            downloader.downloadFile(_url);

            parser.readXLSX(_standardPath, _fileNameXLSX, _groupIndex);
            parser.writeXML(_standardPath, _fileNameXML);
        }
    }
    catch (...)
    {}

    if ( !_settings.contains("/Settings/groupIndex") && !_url.isEmpty() )
    {
        SettingsTab* settingsTab = new SettingsTab(Parser::groups(_standardPath, _fileNameXLSX), _groupIndex, _subgroup,
                                                   _currentWeekNumber, MAX_WEEK_NUMBER, _showEmptyLessons, this);
        _mainLayout->addWidget(settingsTab);
        _currentTabIndex = SETTINGS_TAB_INDEX;
    }
    else
    {
        ScheduleTab* scheduleTab = new ScheduleTab(parser.readXML(_standardPath, _fileNameXML, _subgroup,
                                                                  _currentWeekNumber), _showEmptyLessons, this);
        _mainLayout->addWidget(scheduleTab);
        _currentTabIndex = SCHEDULE_TAB_INDEX;
    }

    qobject_cast<QVBoxLayout*>(_mainLayout)->addLayout( createTabBarLayout() );

    if ( _url.isEmpty() )
    {
        qobject_cast<settingsButton*>( _mainLayout->itemAt(1)->layout()->itemAt(SETTINGS_TAB_INDEX)->widget() )
                                     ->setDisabled(true);
    }

    setLayout(_mainLayout);
}

QHBoxLayout* MainWidget::createTabBarLayout()
{
    QHBoxLayout* tabBarLayout = new QHBoxLayout();

    scheduleButton* schedule = new scheduleButton();
    connect(schedule, SIGNAL( clicked() ), SLOT( slotScheduleButtonClicked() ));

    settingsButton* settings = new settingsButton();
    connect(settings, SIGNAL( clicked() ), SLOT( slotSettingsButtonClicked() ));

    tabBarLayout->addWidget(schedule);
    tabBarLayout->addWidget(settings);

    if (_currentTabIndex == SCHEDULE_TAB_INDEX)
    {
        schedule->setChecked(true);
        schedule->setDisabled(true);
    }
    else if (_currentTabIndex == SETTINGS_TAB_INDEX)
    {
        settings->setChecked(true);
        settings->setDisabled(true);
    }

    return tabBarLayout;
}

void MainWidget::appConfig()
{
    _standardPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir dir(_standardPath);

    if ( !dir.exists() )
    {
        if ( !dir.mkpath(_standardPath) )
        {
            return;
        }
    }

    _settings.beginGroup("/Settings");

    _url = _settings.value("url", "").toString();
    _groupIndex = _settings.value("groupIndex", 0).toInt();
    _subgroup = _settings.value("subgroup", 1).toInt();
    _date = _settings.value("date", QDateTime::currentDateTime().date() ).toDate();
    _week = _settings.value("week", 1).toInt();
    _showEmptyLessons = _settings.value("showEmptyLessons", false).toBool();
    this->move( _settings.value("position", this->pos()).toPoint() );
    this->resize( _settings.value("geometry", this->size()).toSize() );
    this->resize( this->size() );

    _settings.endGroup();

    calulateCurrentWeekNumber();
}

void MainWidget::saveSettingsFromTab()
{
    SettingsTab* settings = qobject_cast<SettingsTab*>( _mainLayout->itemAt(0)->widget() );

    if (settings->getShowEmptyLessons() != _showEmptyLessons)
    {
        if (_showEmptyLessons)
        {
            this->setFixedHeight( this->height() - EXTRA_SIZE );
        }
        else
        {
            this->setFixedHeight( this->height() + EXTRA_SIZE );
        }
    }

    _groupIndex = settings->getGroupIndex();
    _subgroup = settings->getSubgroup();

    if (QDateTime::currentDateTime().date().dayOfWeek() == Qt::Sunday && settings->getWeek() == _currentWeekNumber)
    {
        _week = settings->getWeek() - 1;
    }
    else
    {
        _week = settings->getWeek();
    }

    _date = QDateTime::currentDateTime().date();
    _showEmptyLessons = settings->getShowEmptyLessons();

    calulateCurrentWeekNumber();
}

void MainWidget::calulateCurrentWeekNumber()
{
    QDate currentDate = QDateTime::currentDateTime().date();

    _currentWeekNumber = currentDate.weekNumber() - _date.weekNumber() + _week;

    if (currentDate.dayOfWeek() == 7)
    {
        ++_currentWeekNumber;
    }

    if (_currentWeekNumber < 1 || _currentWeekNumber > MAX_WEEK_NUMBER)
    {
        _currentWeekNumber = MAX_WEEK_NUMBER;
    }
}

void MainWidget::closeEvent(QCloseEvent* event)
{
    if (_currentTabIndex == SETTINGS_TAB_INDEX)
    {
        this->saveSettingsFromTab();

        Parser parser;
        parser.readXLSX(_standardPath, _fileNameXLSX, _groupIndex);
        parser.writeXML(_standardPath, _fileNameXML);
    }

    _settings.beginGroup("/Settings");

    _settings.setValue("url", _url);
    _settings.setValue("groupIndex", _groupIndex);
    _settings.setValue("subgroup", _subgroup);
    _settings.setValue("showEmptyLessons", _showEmptyLessons);
    _settings.setValue("date", _date);
    _settings.setValue("week", _week);
    _settings.setValue( "position", this->pos() );

    if (_showEmptyLessons)
    {
        this->setFixedHeight( this->height() - EXTRA_SIZE );
        _settings.setValue( "geometry", this->size() );
    }
    else
    {
        _settings.setValue( "geometry", this->size() );
    }

    _settings.endGroup();
}

void MainWidget::slotScheduleButtonClicked()
{
    if ( _currentTabIndex == SCHEDULE_TAB_INDEX )
    {
        return;
    }

    this->saveSettingsFromTab();

    Parser parser;
    parser.readXLSX(_standardPath, _fileNameXLSX, _groupIndex);
    parser.writeXML(_standardPath, _fileNameXML);

    _mainLayout->replaceWidget(_mainLayout->itemAt(0)->widget(), new ScheduleTab(
            Parser::readXML(_standardPath, _fileNameXML, _subgroup, _currentWeekNumber), _showEmptyLessons, this))
            ->widget()->deleteLater();

    qobject_cast<settingsButton*>( _mainLayout->itemAt(1)->layout()->itemAt(SETTINGS_TAB_INDEX)->widget() )
                                   ->setChecked(false);
    qobject_cast<settingsButton*>( _mainLayout->itemAt(1)->layout()->itemAt(SETTINGS_TAB_INDEX)->widget() )
                                   ->setDisabled(false);
    qobject_cast<scheduleButton*>( _mainLayout->itemAt(1)->layout()->itemAt(SCHEDULE_TAB_INDEX)->widget() )
                                   ->setDisabled(true);

    _currentTabIndex = SCHEDULE_TAB_INDEX;
}

void MainWidget::slotSettingsButtonClicked()
{
    if (_currentTabIndex == SETTINGS_TAB_INDEX || _url.isEmpty() )
    {
        return;
    }

    Parser parser;
    _mainLayout->replaceWidget(_mainLayout->itemAt(0)->widget(), new SettingsTab(
            Parser::groups(_standardPath, _fileNameXLSX), _groupIndex, _subgroup, _currentWeekNumber,
            MAX_WEEK_NUMBER, _showEmptyLessons, this))->widget()->deleteLater();

    qobject_cast<scheduleButton*>( _mainLayout->itemAt(1)->layout()->itemAt(SCHEDULE_TAB_INDEX)->widget() )
                                   ->setChecked(false);
    qobject_cast<scheduleButton*>( _mainLayout->itemAt(1)->layout()->itemAt(SCHEDULE_TAB_INDEX)->widget() )
                                   ->setDisabled(false);
    qobject_cast<settingsButton*>( _mainLayout->itemAt(1)->layout()->itemAt(SETTINGS_TAB_INDEX)->widget() )
                                   ->setDisabled(true);

    _currentTabIndex = SETTINGS_TAB_INDEX;
}

void MainWidget::slotCheckSystemTheme()
{
    QColor backgroundColor = QWidget::palette().color( QWidget::backgroundRole() );

    std::array<int, 3> color;
    color[0] = backgroundColor.red();
    color[1] = backgroundColor.green();
    color[2] = backgroundColor.blue();

    int count = 0;

    for (auto&& item : color)
    {
        count += (item > 150) ? 1 : 0;
    }

    if ( count < 2 && (_appTheme == LIGHT_THEME || _appTheme == START_UP_THEME) )
    {
        QFile style(":/dark_theme.qss");
        style.open(QFile::ReadOnly);

        static_cast<QApplication*>( QCoreApplication::instance() )->setStyleSheet( style.readAll() );
        _appTheme = DARK_THEME;
    }
    else if ( count > 2 && (_appTheme == DARK_THEME || _appTheme == START_UP_THEME) )
    {
        QFile style(":/light_theme.qss");
        style.open(QFile::ReadOnly);

        static_cast<QApplication*>( QCoreApplication::instance() )->setStyleSheet( style.readAll() );
        _appTheme = LIGHT_THEME;
    }
}
