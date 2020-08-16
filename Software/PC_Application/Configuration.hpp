/** @file Configuration.hpp
 * Store all program settings in an .ini file.
 * @author Adrien RICCIARDI
 */
#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

#include <QVariant>

namespace Configuration
{
    /** Load configuration file and create all needed application data directories.
     * @return -1 if application data directory is not found,
     * @return -2 if application data directory was not existing and could not be created,
     */
    int initialize();

    /** Save configuration data and release allocated resources. */
    void uninitialize();

    /** Retrieve the base directory to store application configuration and data to.
     * @return Application data directory (located in user account standard "documents" directory).
     */
    QString getApplicationDataDirectory();

    /** Read a value from configuration file.
     * @param referenceKey The INI file key (can contain a path).
     * @param referenceDefaultValue If no value is found in the INI file, this value is provided.
     * @return The read value.
     */
    QVariant getValue(const QString &referenceKey, const QVariant &referenceDefaultValue = QVariant());

    /** Write a value to the configuration file.
     * @param referenceKey The INI file key (can contain a path).
     * @param referenceValue The value to write to the specified key.
     */
    void setValue(const QString &referenceKey, const QVariant &referenceValue);
}

#endif // CONFIGURATION_HPP
