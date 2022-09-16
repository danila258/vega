#include "SettingsTab.h"

SettingsTab::SettingsTab(const QStringList& groups, int groupIndex, int subgroup, int week, int maxWeekNumber,
                         bool showEmptyLessons, QWidget* parent) : QWidget(parent), _showEmptyLessons(showEmptyLessons)
{
    QFormLayout* settingsLayout = new QFormLayout();

    QComboBox* groupComboBox = new QComboBox(this);
    QComboBox* subgroupComboBox = new QComboBox(this);
    QComboBox* weekComboBox = new QComboBox(this);
    QComboBox* showEmptyLessonsComboBox = new QComboBox(this);

    connect(groupComboBox, SIGNAL( currentIndexChanged(int) ), SLOT( slotGroup(int) ));
    connect(subgroupComboBox, SIGNAL( currentIndexChanged(int) ), SLOT( slotSubgroup(int) ));
    connect(weekComboBox, SIGNAL( currentIndexChanged(int) ), SLOT( slotWeek(int) ));
    connect(showEmptyLessonsComboBox, SIGNAL( currentIndexChanged(int) ), SLOT( slotShowEmptyLessons(int) ));

    groupComboBox->addItems(groups);
    subgroupComboBox->addItems( {"1", "2"} );
    showEmptyLessonsComboBox->addItems( {"Нет" , "Да"});

    for (int i = 1; i < maxWeekNumber + 1; ++i)
    {
        weekComboBox->addItem( QString::number(i) );
    }

    groupComboBox->setCurrentIndex(groupIndex);
    subgroupComboBox->setCurrentIndex(subgroup - 1);
    weekComboBox->setCurrentIndex(week - 1);
    showEmptyLessonsComboBox->setCurrentIndex( int(showEmptyLessons) );

    groupComboBox->setMaxVisibleItems(COUNT_MAX_VISIBLE_ITEMS);
    weekComboBox->setMaxVisibleItems(COUNT_MAX_VISIBLE_ITEMS);

    settingsLayout->addRow("Группа:", groupComboBox);
    settingsLayout->addRow("Подгруппа:", subgroupComboBox);
    settingsLayout->addRow("Неделя:", weekComboBox);
    settingsLayout->addRow("Показывать пустые пары:", showEmptyLessonsComboBox);

    setLayout(settingsLayout);
}

int SettingsTab::getGroupIndex() const
{
    return _groupIndex;
}

int SettingsTab::getSubgroup() const
{
    return _subgroup;
}

int SettingsTab::getWeek() const
{
    return _week;
}

bool SettingsTab::getShowEmptyLessons() const
{
    return _showEmptyLessons;
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

void SettingsTab::slotShowEmptyLessons(int index)
{
    _showEmptyLessons = index;
}
