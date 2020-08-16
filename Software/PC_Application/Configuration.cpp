/** @file Configuration.cpp
 * See Configuration.hpp for description.
 * @author Adrien RICCIARDI
 */
#include <Configuration.hpp>
#include <QDir>
#include <QMessageBox>
#include <QObject>
#include <QSettings>
#include <QStandardPaths>

namespace Configuration
{
    /** The INI file. */
    static QSettings *_pointerSettings = nullptr;

    /** Cache the path where application will store configuration data and results. */
    static QString _applicationDataDirectoryPath;

    int initialize()
    {
        // Generate data directory path
        QStringList documentsPaths = QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation);
        if (documentsPaths.length() == 0)
        {
            QMessageBox::critical(nullptr, QObject::tr("Error"), QObject::tr("Failed to retrieve 'Documents' directory path."));
            return -1;
        }
        _applicationDataDirectoryPath = QDir::toNativeSeparators(documentsPaths[0] + "/Cyclope");

        // Is application data directory present ?
        QDir applicationDataDirectory(_applicationDataDirectoryPath);
        if (!applicationDataDirectory.exists())
        {
            if (!applicationDataDirectory.mkdir(_applicationDataDirectoryPath))
            {
                QMessageBox::critical(nullptr, QObject::tr("Error"), QObject::tr("Failed to create application data directory to path '%1'.").arg(_applicationDataDirectoryPath));
                return -2;
            }
        }

        // Initialize configuration .ini file
        QString configurationFilePath = QDir::toNativeSeparators(_applicationDataDirectoryPath + "/Configuration.ini");
        _pointerSettings = new QSettings(configurationFilePath, QSettings::IniFormat);

        return 0;
    }

    void uninitialize()
    {
        if (_pointerSettings != nullptr) _pointerSettings->sync();
    }

    QString getApplicationDataDirectory()
    {
        return _applicationDataDirectoryPath;
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
