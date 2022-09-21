#include "CustomElements.h"

scheduleLabel::scheduleLabel(const QString& str, QWidget* parent) : QLabel(str, parent)
{}


dayButton::dayButton(const QString& str, int weekday, QWidget* parent) : QPushButton(str, parent),
    _weekday(weekday)
{
    this->setCheckable(true);
}


scheduleButton::scheduleButton(QWidget* parent) : QPushButton(parent)
{
    setCheckable(true);
}


settingsButton::settingsButton(QWidget* parent) : QPushButton(parent)
{
    setCheckable(true);
}

