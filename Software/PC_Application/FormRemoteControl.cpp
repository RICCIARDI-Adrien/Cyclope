/** @file FormRemoteControl.cpp
 * See FormRemoteControl.hpp for description.
 * @author Adrien RICCIARDI
 */
#include <CommunicationProtocol.hpp>
#include <FormRemoteControl.hpp>
#include <MainWindow.hpp>
#include <QKeyEvent>
#include <ui_FormRemoteControl.h>

FormRemoteControl::FormRemoteControl(QWidget *parent) :
    FormBase(parent),
    ui(new Ui::FormRemoteControl)
{
    ui->setupUi(this);

    // Connect slots
    connect(ui->pushButtonBack, &QPushButton::clicked, this, &FormRemoteControl::_slotPushButtonBackClicked);
}

FormRemoteControl::~FormRemoteControl()
{
    delete ui;
}

void FormRemoteControl::enterView()
{
    // TODO
}
#include <QDebug>
void FormRemoteControl::keyPressEvent(QKeyEvent *pointerEvent)
{
    switch (pointerEvent->key())
    {
        case Qt::Key_Up:
            //if (CommunicationProtocol::setRobotMotion(CommunicationProtocol::ROBOT_MOTION_FORWARD)) /* TODO */ ;
            qDebug() << "up";
            break;

        case Qt::Key_Down:
            qDebug() << "down";
            break;

        default:
            QWidget::keyPressEvent(pointerEvent);
            break;
    }
}

void FormRemoteControl::_slotPushButtonBackClicked(bool)
{
    // Stop robot
    if (CommunicationProtocol::setRobotMotion(CommunicationProtocol::ROBOT_MOTION_STOP) != 0)
    {
        CommunicationProtocol::displayConnectionLostMessage(this);
        return;
    }
    // Turn lights off
    // TODO

    // Display main menu
    pointerMainWindow->changeView(MainWindow::VIEW_ID_MAIN_MENU);
}
