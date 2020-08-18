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
    // Make sure robot is stopped
    if (CommunicationProtocol::setRobotMotion(CommunicationProtocol::ROBOT_MOTION_STOP) != 0)
    {
        CommunicationProtocol::displayConnectionLostMessage(this);
        return;
    }
    ui->labelRobotMotion->setText(tr("Robot motion: <b>stopped</b>"));

    // Turn light off
    _isLightEnabled = false;
    if (CommunicationProtocol::setLightEnabled(false) != 0)
    {
        CommunicationProtocol::displayConnectionLostMessage(this);
        return;
    }
    ui->labelLightState->setText(tr("State: <b>OFF</b>"));
}

void FormRemoteControl::keyPressEvent(QKeyEvent *pointerEvent)
{
    // Ignore auto repeat key events
    if (!pointerEvent->isAutoRepeat())
    {
        switch (pointerEvent->key())
        {
            case Qt::Key_Up:
                if (CommunicationProtocol::setRobotMotion(CommunicationProtocol::ROBOT_MOTION_FORWARD) != 0)
                {
                    CommunicationProtocol::displayConnectionLostMessage(this);
                    return;
                }
                ui->labelRobotMotion->setText(tr("Robot motion: <b>forward</b>"));
                break;

            case Qt::Key_Down:
                if (CommunicationProtocol::setRobotMotion(CommunicationProtocol::ROBOT_MOTION_BACKWARD) != 0)
                {
                    CommunicationProtocol::displayConnectionLostMessage(this);
                    return;
                }
                ui->labelRobotMotion->setText(tr("Robot motion: <b>backward</b>"));
                break;

            case Qt::Key_Left:
                if (CommunicationProtocol::setRobotMotion(CommunicationProtocol::ROBOT_MOTION_LEFT) != 0)
                {
                    CommunicationProtocol::displayConnectionLostMessage(this);
                    return;
                }
                ui->labelRobotMotion->setText(tr("Robot motion: <b>left</b>"));
                break;

            case Qt::Key_Right:
                if (CommunicationProtocol::setRobotMotion(CommunicationProtocol::ROBOT_MOTION_RIGHT) != 0)
                {
                    CommunicationProtocol::displayConnectionLostMessage(this);
                    return;
                }
                ui->labelRobotMotion->setText(tr("Robot motion: <b>right</b>"));
                break;

            case Qt::Key_L:
                // Toggle light state
                _isLightEnabled = !_isLightEnabled;
                if (CommunicationProtocol::setLightEnabled(_isLightEnabled) != 0)
                {
                    CommunicationProtocol::displayConnectionLostMessage(this);
                    return;
                }
                // Display new light state in user interface
                if (_isLightEnabled) ui->labelLightState->setText(tr("State: <b>ON</b>"));
                else ui->labelLightState->setText(tr("State: <b>OFF</b>"));
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
                if (CommunicationProtocol::setRobotMotion(CommunicationProtocol::ROBOT_MOTION_STOP) != 0)
                {
                    CommunicationProtocol::displayConnectionLostMessage(this);
                    return;
                }
                ui->labelRobotMotion->setText(tr("Robot motion: <b>stopped</b>"));
                break;
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

    // Turn light off
    if (CommunicationProtocol::setLightEnabled(false) != 0)
    {
        CommunicationProtocol::displayConnectionLostMessage(this);
        return;
    }

    // Display main menu
    pointerMainWindow->changeView(MainWindow::VIEW_ID_MAIN_MENU);
}
