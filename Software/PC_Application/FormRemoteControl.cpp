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
        bool isRobotMotionUpdateNeeded = false;

        switch (pointerEvent->key())
        {
            case Qt::Key_Up:
                _isUpDirectionKeyPressed = true;
                _isLastPressedDirectionKeyOnVerticalAxis = true;
                isRobotMotionUpdateNeeded = true;
                break;

            case Qt::Key_Down:
                _isDownDirectionKeyPressed = true;
                _isLastPressedDirectionKeyOnVerticalAxis = true;
                isRobotMotionUpdateNeeded = true;
                break;

            case Qt::Key_Left:
                _isLeftDirectionKeyPressed = true;
                _isLastPressedDirectionKeyOnVerticalAxis = false;
                isRobotMotionUpdateNeeded = true;
                break;

            case Qt::Key_Right:
                _isRightDirectionKeyPressed = true;
                _isLastPressedDirectionKeyOnVerticalAxis = false;
                isRobotMotionUpdateNeeded = true;
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
                break;
            }

            // Set new robot motion if needed
            if (isRobotMotionUpdateNeeded) _selectRobotMotion();
    }

    // Handle other keys in the normal way
    QWidget::keyPressEvent(pointerEvent);
}

void FormRemoteControl::keyReleaseEvent(QKeyEvent *pointerEvent)
{
    // Ignore auto repeat key events
    if (!pointerEvent->isAutoRepeat())
    {
        bool isRobotMotionUpdateNeeded = false;

        switch (pointerEvent->key())
        {
            case Qt::Key_Up:
                _isUpDirectionKeyPressed = false;
                isRobotMotionUpdateNeeded = true;
                break;

            case Qt::Key_Down:
                _isDownDirectionKeyPressed = false;
                isRobotMotionUpdateNeeded = true;
                break;

            case Qt::Key_Left:
                _isLeftDirectionKeyPressed = false;
                isRobotMotionUpdateNeeded = true;
                break;

            case Qt::Key_Right:
                _isRightDirectionKeyPressed = false;
                isRobotMotionUpdateNeeded = true;
                break;
        }

        // Set new robot motion if needed
        if (isRobotMotionUpdateNeeded) _selectRobotMotion();
    }

    // Handle other keys in the normal way
    QWidget::keyPressEvent(pointerEvent);
}

void FormRemoteControl::_selectRobotMotion()
{
    // Stop robot if all direction keys are released
    if (!_isUpDirectionKeyPressed && !_isDownDirectionKeyPressed && !_isLeftDirectionKeyPressed && !_isRightDirectionKeyPressed)
    {
        if (CommunicationProtocol::setRobotMotion(CommunicationProtocol::ROBOT_MOTION_STOP) != 0) goto Exit_Connection_Lost;
        ui->labelRobotMotion->setText(tr("Robot motion: <b>stopped</b>"));
    }
    else
    {
        // Handle both vertical and horizontal direction movement
        if ((_isUpDirectionKeyPressed || _isDownDirectionKeyPressed) && (_isLeftDirectionKeyPressed || _isRightDirectionKeyPressed))
        {
            // Keep trace of the last direction the user took to favor it, and when this key will be released the previous direction will be favored
            if (_isLastPressedDirectionKeyOnVerticalAxis)
            {
                if (_isUpDirectionKeyPressed)
                {
                    if (CommunicationProtocol::setRobotMotion(CommunicationProtocol::ROBOT_MOTION_FORWARD) != 0) goto Exit_Connection_Lost;
                    ui->labelRobotMotion->setText(tr("Robot motion: <b>forward</b>"));
                }
                else
                {
                    if (CommunicationProtocol::setRobotMotion(CommunicationProtocol::ROBOT_MOTION_BACKWARD) != 0) goto Exit_Connection_Lost;
                    ui->labelRobotMotion->setText(tr("Robot motion: <b>backward</b>"));
                }
            }
            else
            {
                if (_isLeftDirectionKeyPressed)
                {
                    // Forward turn if going forward
                    if (_isUpDirectionKeyPressed)
                    {
                        if (CommunicationProtocol::setRobotMotion(CommunicationProtocol::ROBOT_MOTION_FORWARD_LEFT) != 0) goto Exit_Connection_Lost;
                    }
                    // Backward turn if going backward
                    else
                    {
                        if (CommunicationProtocol::setRobotMotion(CommunicationProtocol::ROBOT_MOTION_BACKWARD_LEFT) != 0) goto Exit_Connection_Lost;
                    }
                    ui->labelRobotMotion->setText(tr("Robot motion: <b>left</b>"));
                }
                else
                {
                    // Forward turn if going forward
                    if (_isUpDirectionKeyPressed)
                    {
                        if (CommunicationProtocol::setRobotMotion(CommunicationProtocol::ROBOT_MOTION_FORWARD_RIGHT) != 0) goto Exit_Connection_Lost;
                    }
                    // Backward turn if going backward
                    else
                    {
                        if (CommunicationProtocol::setRobotMotion(CommunicationProtocol::ROBOT_MOTION_BACKWARD_RIGHT) != 0) goto Exit_Connection_Lost;
                    }
                    ui->labelRobotMotion->setText(tr("Robot motion: <b>right</b>"));
                }
            }
        }
        // Handle a single key press
        else
        {
            if (_isUpDirectionKeyPressed)
            {
                if (CommunicationProtocol::setRobotMotion(CommunicationProtocol::ROBOT_MOTION_FORWARD) != 0) goto Exit_Connection_Lost;
                ui->labelRobotMotion->setText(tr("Robot motion: <b>forward</b>"));
            }
            else if (_isDownDirectionKeyPressed)
            {
                if (CommunicationProtocol::setRobotMotion(CommunicationProtocol::ROBOT_MOTION_BACKWARD) != 0) goto Exit_Connection_Lost;
                ui->labelRobotMotion->setText(tr("Robot motion: <b>backward</b>"));
            }
            else if (_isLeftDirectionKeyPressed)
            {
                if (CommunicationProtocol::setRobotMotion(CommunicationProtocol::ROBOT_MOTION_FORWARD_LEFT) != 0) goto Exit_Connection_Lost;
                ui->labelRobotMotion->setText(tr("Robot motion: <b>left</b>"));
            }
            else if (_isRightDirectionKeyPressed)
            {
                if (CommunicationProtocol::setRobotMotion(CommunicationProtocol::ROBOT_MOTION_FORWARD_RIGHT) != 0) goto Exit_Connection_Lost;
                ui->labelRobotMotion->setText(tr("Robot motion: <b>right</b>"));
            }
        }
    }

    // No error occurred
    return;

Exit_Connection_Lost:
    CommunicationProtocol::displayConnectionLostMessage(this);
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
