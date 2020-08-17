/** @file Configuration.cpp
 * See Configuration.hpp for description.
 * @author Adrien RICCIARDI
 */
#include <Configuration.hpp>
#include <QSettings>

namespace Configuration
{
    /** The INI file. */
    static QSettings *_pointerSettings = nullptr;

    int initialize()
    {
        // Use an INI file stored in user "home" directory
        _pointerSettings = new QSettings(QSettings::IniFormat, QSettings::UserScope, "CyclopeRobot", "Cyclope");

        return 0;
    }

    void uninitialize()
    {
        if (_pointerSettings != nullptr) _pointerSettings->sync();
    }

    QVariant getValue(const QString &referenceKey, const QVariant &referenceDefaultValue)
    {
        return _pointerSettings->value(referenceKey, referenceDefaultValue);
    }

    void setValue(const QString &referenceKey, const QVariant &referenceValue)
    {
        _pointerSettings->setValue(referenceKey, referenceValue);
    }
}
