/** @file Main.cpp
 * Cyclope robot mission control software.
 * @author Adrien RICCIARDI
 */
#include <MainWindow.hpp>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);

    MainWindow mainWindow;
    mainWindow.showMaximized();

    return application.exec();
}
