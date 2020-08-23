/** @file FormMainMenu.cpp
 * See FormMainMenu.hpp for description.
 * @author Adrien RICCIARDI
 */
#include <CommunicationProtocol.hpp>
#include <FormMainMenu.hpp>
#include <MainWindow.hpp>
#include <ui_FormMainMenu.h>

FormMainMenu::FormMainMenu(QWidget *parent) :
    FormBase(parent),
    ui(new Ui::FormMainMenu)
{
    ui->setupUi(this);

    // Connect slots
    connect(ui->pushButtonRemoteControl, &QPushButton::clicked, this, &FormMainMenu::_slotPushButtonRemoteControlClicked);
    connect(ui->pushButtonPowerRobotOff, &QPushButton::clicked, this, &FormMainMenu::_slotPushButtonPowerRobotOffClicked);
    connect(ui->pushButtonExit, &QPushButton::clicked, this, &FormMainMenu::_slotPushButtonExitClicked);
}

FormMainMenu::~FormMainMenu()
{
    delete ui;
}

void FormMainMenu::enterView()
{
    // Focus first button
    ui->pushButtonStartProgram->setFocus();
}

void FormMainMenu::_slotPushButtonRemoteControlClicked(bool)
{
    pointerMainWindow->changeView(MainWindow::VIEW_ID_REMOTE_CONTROL);
}

void FormMainMenu::_slotPushButtonPowerRobotOffClicked(bool)
{
    if (CommunicationProtocol::powerRobotOff() != 0)
    {
        CommunicationProtocol::displayConnectionLostMessage(this);
        return; // Exit as displayConnectionLostMessage() method already returns to connection view
    }

    // Return to connection view
    pointerMainWindow->changeView(MainWindow::VIEW_ID_CONNECT_TO_ROBOT);
}

void FormMainMenu::_slotPushButtonExitClicked(bool)
{
    qApp->exit();
}
