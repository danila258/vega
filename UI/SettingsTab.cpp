#include "SettingsTab.h"

SettingsTab::SettingsTab(const QStringList& groups, int groupIndex, int subgroup, int week, QWidget* parent)
    : QWidget(parent)
{
    QFormLayout* settingsLayout = new QFormLayout();

    QComboBox* groupComboBox = new QComboBox();
    QComboBox* subgroupComboBox = new QComboBox();
    QComboBox* weekComboBox = new QComboBox();

    connect(groupComboBox, SIGNAL( currentIndexChanged(int) ), SLOT( slotGroup(int) ));
    connect(subgroupComboBox, SIGNAL( currentIndexChanged(int) ), SLOT( slotSubgroup(int) ));
    connect(weekComboBox, SIGNAL( currentIndexChanged(int) ), SLOT( slotWeek(int) ));

    groupComboBox->addItems(groups);
    subgroupComboBox->addItems( {"1", "2"} );

    for (int i = 1; i < 21; ++i)
    {
        weekComboBox->addItem( QString::number(i) );
    }

    groupComboBox->setCurrentIndex(groupIndex);
    subgroupComboBox->setCurrentIndex(subgroup - 1);
    weekComboBox->setCurrentIndex(week - 1);

    groupComboBox->setMaxVisibleItems(5);
    weekComboBox->setMaxVisibleItems(5);

    settingsLayout->addRow("Группа:", groupComboBox);
    settingsLayout->addRow("Подгруппа:", subgroupComboBox);
    settingsLayout->addRow("Неделя:", weekComboBox);

    setLayout(settingsLayout);
}

int SettingsTab::getGroupIndex()
{
    return _groupIndex;
}

int SettingsTab::getSubgroup()
{
    return _subgroup;
}

int SettingsTab::getWeek()
{
    return _week;
}

void SettingsTab::slotGroup(int index)
{
    _groupIndex = index;
}

void SettingsTab::slotSubgroup(int index)
{
    _subgroup = index + 1;
}

void SettingsTab::slotWeek(int index)
{
    _week = index + 1;
}

