#include "CommonFunctions.h"

bool checkOrientation(const QWidget* widget)
{
    #if defined(Q_OS_IOS) || defined(Q_OS_ANDROID)

        if (QGuiApplication::primaryScreen()->primaryOrientation() == Qt::LandscapeOrientation)
        {
            return true;
        }

    #else

        if (widget->size().width() > 700)
        {
            return true;
        }

    #endif

        return false;
}

