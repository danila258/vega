#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "ScheduleTab.h"
#include "SettingsTab.h"
#include "CommonFunctions.h"
#include "Backend/Parser.h"
#include "Backend/Downloader.h"

#include <QStandardPaths>
#include <QApplication>
#include <QSettings>
#include <QEvent>


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
    QHBoxLayout* createTabBarLayout();      // bottom buttons
    void appConfig();                       // load settings and check app directory
    void saveSettingsFromTab();

    QVBoxLayout* _mainLayout;
    ScheduleTab* _scheduleTab;
    int _currentTabIndex;

    QSettings _settings;
    QString _standardPath;      // app directory
    QString _url;
    int _groupIndex;
    int _subgroup;
    int _week;

    QString _fileNameXLSX = "Schedule.xlsx";
    QString _fileNameXML = "Data.xml";

protected:
    void closeEvent(QCloseEvent* event) override;

    void paletteEvent(QEvent* event)
    {
            qDebug() << event->type();
    }

    void palette2Event(QEvent* event)
    {
        if (event->type() == QEvent::StyleChange)
        {
            qDebug() << "смена темы 2";
        }
    }

    void palette3Event(QEvent* event)
    {
        if (event->type() == QEvent::UpdateRequest)
        {
            qDebug() << "смена темы 3";
        }
    }

private slots:
    void slotTabButtonClicked();
};


#endif // MAINWIDGET_H
