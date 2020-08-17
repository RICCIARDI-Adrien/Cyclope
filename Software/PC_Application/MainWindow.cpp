/** @file MainWindow.cpp
 * See MainWindow.hpp for description.
 * @author Adrien RICCIARDI
 */
#include <FormConnectToRobot.hpp>
#include <FormMainMenu.hpp>
#include <FormRemoteControl.hpp>
#include <MainWindow.hpp>
#include <ui_MainWindow.h>

// Public variables
MainWindow *pointerMainWindow;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Add all stacked widget pages
    ui->stackedWidget->addWidget(new FormConnectToRobot(this));
    ui->stackedWidget->addWidget(new FormMainMenu(this));
    ui->stackedWidget->addWidget(new FormRemoteControl(this));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeView(ViewId id)
{
    Q_ASSERT(id < VIEW_IDS_COUNT);

    // Tell current view that is will be hidden
    FormBase *pointerView = reinterpret_cast<FormBase *>(ui->stackedWidget->currentWidget());
    pointerView->exitView();

    // Tell next view that it will be displayed
    pointerView = reinterpret_cast<FormBase *>(ui->stackedWidget->widget(id));
    pointerView->enterView();

    // Display next view
    ui->stackedWidget->setCurrentIndex(id);
}
