#include "MainWidget.h"

tabButton::tabButton(QString inactiveStyle, QString activeStyle, QWidget* parent)
    : QPushButton(parent), _inactiveStyle(inactiveStyle), _activeStyle(activeStyle)
{
    setInactiveStyle();
}

void tabButton::setInactiveStyle()
{
    QFile style(_inactiveStyle);
    style.open(QFile::ReadOnly);
    setStyleSheet( style.readAll() );
}

void tabButton::setActiveStyle()
{
    QFile style(_activeStyle);
    style.open(QFile::ReadOnly);
    setStyleSheet( style.readAll() );
}

int tabButton::getIndex()
{
    return _index;
}

MainWidget::MainWidget(QWidget* parent) : QWidget(parent)
{
    _settings.clear();
    appConfig();

    _mainLayout = new QVBoxLayout();

    Downloader downloader(_fileNameXLSX, _standardPath);
    QString url = downloader.getDownloadLink();

    _fileNameXLSX = "2022spr8.xlsx";
    Parser parser;

    if ( _url != url || !_settings.contains("groupIndex") )
    {
        _url = std::move(url);
        downloader.downloadFile(_url);

        parser.readXLSX(_standardPath, _fileNameXLSX, _groupIndex);
        parser.writeXML(_standardPath, _fileNameXML);
    }

    if ( !_settings.contains("groupIndex") )
    {
        SettingsTab* settingsTab = new SettingsTab(parser.groups(_standardPath, _fileNameXLSX), _groupIndex,
                                                   _subgroup, _week, this);
        _mainLayout->addWidget(settingsTab);
        _currentTabIndex = 1;
    }
    else
    {
        _scheduleTab = new ScheduleTab( parser.readXML(_standardPath, _fileNameXML, _subgroup, _week) );

        _mainLayout->addWidget(_scheduleTab);
        _currentTabIndex = 0;
    }

    qobject_cast<QVBoxLayout*>(_mainLayout)->addLayout( createTabBarLayout() );
    setLayout(_mainLayout);
}

QHBoxLayout* MainWidget::createTabBarLayout()
{
    QHBoxLayout* tabBarLayout = new QHBoxLayout();

    scheduleButton* schedule = new scheduleButton();
    connect(schedule, SIGNAL( clicked() ), SLOT( slotTabButtonClicked() ));

    settingsButton* settings = new settingsButton();
    connect(settings, SIGNAL( clicked() ), SLOT( slotTabButtonClicked() ));

    tabBarLayout->addWidget(schedule);
    tabBarLayout->addWidget(settings);

    if (_currentTabIndex == 0)
    {
        schedule->setActiveStyle();
    }
    else if (_currentTabIndex == 1)
    {
        settings->setActiveStyle();
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
            return ;
        }
    }

    _settings.beginGroup("/SettingsTab");

    _url = _settings.value("url", "").toString();
    _groupIndex = _settings.value("groupIndex", 0).toInt();
    _subgroup = _settings.value("subgroup", 1).toInt();
    _week = _settings.value("week", 1).toInt();
    this->move(_settings.value("position", this->pos()).toPoint() );
    this->resize(_settings.value("geometry", this->size()).toSize() );

    _settings.endGroup();
}

void MainWidget::saveSettingsFromTab()
{
    SettingsTab* settings = qobject_cast<SettingsTab*>( _mainLayout->itemAt(0)->widget() );
    _groupIndex = settings->getGroupIndex();
    _subgroup = settings->getSubgroup();
    _week = settings->getWeek();
}

void MainWidget::closeEvent(QCloseEvent* event)
{
    _settings.beginGroup("/SettingsTab");

    _settings.setValue("url", _url);
    _settings.setValue("groupIndex", _groupIndex);
    _settings.setValue("subgroup", _subgroup);
    _settings.setValue("week", _week);
    _settings.setValue("position", this->pos());
    //_settings.setValue("geometry", this->size());

    _settings.endGroup();
}

void MainWidget::slotTabButtonClicked()
{
    tabButton* button = qobject_cast<tabButton*>( sender() );

    if (button->getIndex() == _currentTabIndex)
    {
        return;
    }

    if (button->getIndex() == 0)
    {
        this->saveSettingsFromTab();
        Parser parser;
        parser.readXLSX(_standardPath, _fileNameXLSX, _groupIndex);
        parser.writeXML(_standardPath, _fileNameXML);

        _mainLayout->replaceWidget(_mainLayout->itemAt(0)->widget(), new ScheduleTab(
                Parser::readXML(_standardPath, _fileNameXML, _subgroup, _week), this))->widget()->deleteLater();
    }
    else if (button->getIndex() == 1)
    {
        Parser parser;
        parser.readXLSX(_standardPath, _fileNameXLSX, _groupIndex);
        _mainLayout->replaceWidget(_mainLayout->itemAt(0)->widget(), new SettingsTab(
                Parser::groups(_standardPath, _fileNameXLSX), _groupIndex, _subgroup, _week))->widget()->deleteLater();
    }

    qobject_cast<tabButton*>(_mainLayout->itemAt(1)->layout()->itemAt(_currentTabIndex)->widget())->setInactiveStyle();
    button->setActiveStyle();

    _currentTabIndex = button->getIndex();
}

