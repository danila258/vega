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
    appConfig();
    Downloader d;

    Parser parser;
    parser.readXLSX();
    parser.writeXML();

    _scheduleTab = new scheduleTab( parser.readXML() );

    _mainLayout = new QVBoxLayout();
    _mainLayout->addWidget(_scheduleTab);
    qobject_cast<QVBoxLayout*>(_mainLayout)->addLayout( createTabBarLayout() );

    _currentTabIndex = 0;

    setLayout(_mainLayout);
}

QHBoxLayout* MainWidget::createTabBarLayout()
{
    QHBoxLayout* tabBarLayout = new QHBoxLayout();

    scheduleButton* schedule = new scheduleButton();
    schedule->setActiveStyle();
    connect(schedule, SIGNAL( clicked() ), SLOT( slotTabButtonClicked() ));

    settingsButton* settings = new settingsButton();
    settings->setInactiveStyle();
    connect(settings, SIGNAL( clicked() ), SLOT( slotTabButtonClicked() ));

    tabBarLayout->addWidget(schedule);
    tabBarLayout->addWidget(settings);

    _currentTabIndex = 0;

    return tabBarLayout;
}

void MainWidget::appConfig()
{
    QString path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir dir(path);

    if ( !dir.exists() )
    {
        dir.mkpath(path);
    }
}

void MainWidget::slotTabButtonClicked()
{
    tabButton* button = qobject_cast<tabButton*>( sender() );

    if (button->getIndex() == _currentTabIndex)
    {
        return;
    }

    qobject_cast<tabButton*>( _mainLayout->itemAt(1)->layout()->itemAt(_currentTabIndex)->widget() )->setInactiveStyle();
    button->setActiveStyle();

    _currentTabIndex = button->getIndex();
}

