/** @file Main.cpp
 * Cyclope robot mission control software.
 * @author Adrien RICCIARDI
 */
#include <Configuration.hpp>
#include <MainWindow.hpp>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);

    // Load application configuration as soon as possible
    if (Configuration::initialize() != 0) return -1;

    // Create application main window
    MainWindow mainWindow;
    mainWindow.showMaximized();

    // Run application main loop
    int result = application.exec();

    // Release allocated resources
    Configuration::uninitialize();

    return result;
}
