#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "ScheduleTab.h"
#include "Backend/Parser.h"
#include "Backend/Downloader.h"


class tabButton : public QPushButton
{
    Q_OBJECT

public:
    tabButton(QString inactiveStyle, QString activeStyle, QWidget* parent = nullptr);

    void setInactiveStyle();        // it turns accent color
    void setActiveStyle();          // it turns white

    int getIndex();

protected:
    int _index;                     // index in layout

private:
    QString _activeStyle;
    QString _inactiveStyle;
};


class scheduleButton : public tabButton
{
    Q_OBJECT

public:
    scheduleButton(QWidget* parent = nullptr)
        : tabButton(":/scheduleButton_Inactive.qss", ":/scheduleButton_Active.qss", parent)
    {
        _index = 0;
    }
};


class settingsButton : public tabButton
{
    Q_OBJECT

public:
    settingsButton(QWidget* parent = nullptr)
        : tabButton(":/settingsButton_Inactive.qss", ":/settingsButton_Active.qss", parent)
    {
        _index = 1;
    }
};


class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget* parent = nullptr);

private:
    QHBoxLayout* createTabBarLayout();
    void appConfig();

    QLayout* _mainLayout;
    scheduleTab* _scheduleTab;
    int _currentTabIndex;

private slots:
    void slotTabButtonClicked();
};


#endif // MAINWIDGET_H
