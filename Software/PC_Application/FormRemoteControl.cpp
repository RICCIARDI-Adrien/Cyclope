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

void FormRemoteControl::keyPressEvent(QKeyEvent *pointerEvent)
{
    // Ignore auto repeat key events
    if (!pointerEvent->isAutoRepeat())
    {
        switch (pointerEvent->key())
        {
            case Qt::Key_Up:
                if (CommunicationProtocol::setRobotMotion(CommunicationProtocol::ROBOT_MOTION_FORWARD) != 0) CommunicationProtocol::displayConnectionLostMessage(this);
                break;

            case Qt::Key_Down:
                if (CommunicationProtocol::setRobotMotion(CommunicationProtocol::ROBOT_MOTION_BACKWARD) != 0) CommunicationProtocol::displayConnectionLostMessage(this);
                break;

            case Qt::Key_Left:
                if (CommunicationProtocol::setRobotMotion(CommunicationProtocol::ROBOT_MOTION_LEFT) != 0) CommunicationProtocol::displayConnectionLostMessage(this);
                break;

            case Qt::Key_Right:
                if (CommunicationProtocol::setRobotMotion(CommunicationProtocol::ROBOT_MOTION_RIGHT) != 0) CommunicationProtocol::displayConnectionLostMessage(this);
                break;

            // TODO lights
        }
    }

    // Handle other keys in the normal way
    QWidget::keyPressEvent(pointerEvent);
}

void FormRemoteControl::keyReleaseEvent(QKeyEvent *pointerEvent)
{
    // Ignore auto repeat key events
    if (!pointerEvent->isAutoRepeat())
    {
        switch (pointerEvent->key())
        {
            // Stop robot if one of direction keys was released
            case Qt::Key_Up:
            case Qt::Key_Down:
            case Qt::Key_Left:
            case Qt::Key_Right:
                if (CommunicationProtocol::setRobotMotion(CommunicationProtocol::ROBOT_MOTION_STOP) != 0) CommunicationProtocol::displayConnectionLostMessage(this);
                break;

            // TODO lights
        }
    }

    // Handle other keys in the normal way
    QWidget::keyPressEvent(pointerEvent);
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
