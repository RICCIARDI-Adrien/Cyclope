/** @file MainWindow.cpp
 * See MainWindow.hpp for description.
 * @author Adrien RICCIARDI
 */
#include <FormConnectToRobot.hpp>
#include <MainWindow.hpp>
#include <ui_MainWindow.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Add all stacked widget pages
    ui->stackedWidget->addWidget(new FormConnectToRobot(this));
}

MainWindow::~MainWindow()
{
    delete ui;
}

