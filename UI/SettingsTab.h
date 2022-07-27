#ifndef VEGA_SETTINGSTAB_H
#define VEGA_SETTINGSTAB_H

#include <QWidget>
#include <QLayout>
#include <QFormLayout>
#include <QComboBox>
#include <QString>
#include <QStringList>


class SettingsTab : public QWidget
{
    Q_OBJECT

public:
    SettingsTab(const QStringList& groups, int groupIndex, int subgroup, int week, QWidget* parent = nullptr);

    int getGroupIndex();
    int getSubgroup();
    int getWeek();

private:
    int _groupIndex;
    int _subgroup;
    int _week;

private slots:
    void slotGroup(int index);
    void slotSubgroup(int index);
    void slotWeek(int index);
};


#endif //VEGA_SETTINGSTAB_H
