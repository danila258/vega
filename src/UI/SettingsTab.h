#ifndef VEGA_SETTINGSTAB_H
#define VEGA_SETTINGSTAB_H

#include <QWidget>
#include <QLayout>
#include <QFormLayout>
#include <QComboBox>
#include <QString>
#include <QStringList>
#include <QDateTime>

enum
{
    COUNT_MAX_VISIBLE_ITEMS = 5
};


class SettingsTab : public QWidget
{
    Q_OBJECT

public:
    SettingsTab(const QStringList& groups, int groupIndex, int subgroup, int week, int maxWeekNumber,
                bool showEmptyLessons, QWidget* parent = nullptr);

    int getGroupIndex() const;
    int getSubgroup() const;
    int getWeek() const;
    bool getShowEmptyLessons() const;

private:
    int _groupIndex;
    int _subgroup;
    int _week;
    bool _showEmptyLessons;

private slots:
    void slotGroup(int index);
    void slotSubgroup(int index);
    void slotWeek(int index);
    void slotShowEmptyLessons(int index);
};


#endif //VEGA_SETTINGSTAB_H
