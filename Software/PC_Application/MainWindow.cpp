/** @file MainWindow.cpp
 * See MainWindow.hpp for description.
 * @author Adrien RICCIARDI
 */
#include <MainWindow.hpp>
#include <ui_MainWindow.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

