/** @file MainWindow.hpp
 * Cyclope application main window.
 * @author Adrien RICCIARDI
 */
#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /** All available application views. */
    typedef enum
    {
        VIEW_ID_CONNECT_TO_ROBOT,
        VIEW_ID_MAIN_MENU,
        VIEW_ID_REMOTE_CONTROL,
        VIEW_ID_START_PROGRAM,
        VIEW_ID_EXECUTE_PROGRAM,
        VIEW_IDS_COUNT
    } ViewId;

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    /** Display a specific application view.
     * @param id The next view to display.
     */
    void changeView(ViewId id);

private:
    Ui::MainWindow *ui;
};

/** Allow main window to be accessed from everywhere. */
extern MainWindow *pointerMainWindow;

#endif // MAINWINDOW_HPP
