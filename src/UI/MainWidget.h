#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "ScheduleTab.h"
#include "SettingsTab.h"
#include "CustomElements.h"
#include "CommonFunctions.h"
#include "Backend/Parser.h"
#include "Backend/Downloader.h"

#include <QStandardPaths>
#include <QApplication>
#include <QSettings>
#include <QTimer>

enum
{
    SCHEDULE_TAB_INDEX = 0,
    SETTINGS_TAB_INDEX = 1,

    START_UP_THEME,
    LIGHT_THEME,
    DARK_THEME,

    MAX_WEEK_NUMBER = 20,

    EXTRA_SIZE = 120
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
    void calulateCurrentWeekNumber();

    QVBoxLayout* _mainLayout;

    int _currentTabIndex;
    int _appTheme = START_UP_THEME;
    bool _showEmptyLessons;

    QSettings _settings;
    QString _standardPath;      // app directory
    QString _url;               // url for download schedule
    int _groupIndex;
    int _subgroup;

    QDate _date;                // when user change week in settings
    int _week;                  // what week select user when last change
    int _currentWeekNumber;     // calculated using _date and _week

    QString _fileNameXLSX = "Schedule.xlsx";    // downloaded from vega
    QString _fileNameXML = "Data.xml";          // created after parsing .xlsx

protected:
    void closeEvent(QCloseEvent* event) override;

private slots:
    void slotScheduleButtonClicked();
    void slotSettingsButtonClicked();
    void slotCheckSystemTheme();        // check background color of application
};


#endif // MAINWIDGET_H
