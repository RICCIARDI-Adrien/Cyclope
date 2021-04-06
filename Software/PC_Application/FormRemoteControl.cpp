/** @file FormRemoteControl.cpp
 * See FormRemoteControl.hpp for description.
 * @author Adrien RICCIARDI
 */
#include <CommunicationProtocol.hpp>
#include <Configuration.hpp>
#include <FormRemoteControl.hpp>
#include <MainWindow.hpp>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QKeyEvent>
#include <ui_FormRemoteControl.h>

FormRemoteControl::FormRemoteControl(QWidget *parent) :
    FormBase(parent),
    ui(new Ui::FormRemoteControl)
{
    ui->setupUi(this);

    // Configure media player once
    _pointerMediaPlayer = new QMediaPlayer(nullptr, QMediaPlayer::LowLatency);
    _pointerMediaPlayer->setVideoOutput(ui->videoWidget);

    // Camera connection timer must trigger only once when called
    _timerStreamingCameraConnection.setSingleShot(true);

    // Connect slots
    connect(ui->pushButtonBack, &QPushButton::clicked, this, &FormRemoteControl::_slotPushButtonBackClicked);
    connect(&_timerBatteryVoltagePolling, &QTimer::timeout, this, &FormRemoteControl::_slotTimerBatteryVoltagePollingTimeout);
    connect(&_timerStreamingCameraConnection, &QTimer::timeout, this, &FormRemoteControl::_slotTimerStreamingCameraConnectionTimeout);
}

FormRemoteControl::~FormRemoteControl()
{
    // Cleanfully stop video playing
    _pointerMediaPlayer->stop();
    delete _pointerMediaPlayer;

    delete ui;
}

void FormRemoteControl::enterView()
{
    // Start streaming camera
    if (CommunicationProtocol::setStreamingCameraEnabled(true) != 0)
    {
        CommunicationProtocol::displayConnectionLostMessage(this);
        return;
    }

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

    // Start displaying voltage
    _timerBatteryVoltagePolling.start(3000);
    _slotTimerBatteryVoltagePollingTimeout(); // Immediately display values

    // Wait for camera to start, then connect to video stream
    _timerStreamingCameraConnection.start(3000);
}

void FormRemoteControl::exitView()
{
    // Battery voltage is no more needed
    _timerBatteryVoltagePolling.stop();

    // Stop trying to connect to video streaming
    _timerStreamingCameraConnection.stop();

    // Stop video playing
    _pointerMediaPlayer->stop();

    // Stop streaming camera
    CommunicationProtocol::setStreamingCameraEnabled(false);
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

void FormRemoteControl::_slotTimerBatteryVoltagePollingTimeout()
{
    // Retrieve values from robot
    int voltageMillivolts, chargePercentage;
    if (CommunicationProtocol::getBatteryValues(&voltageMillivolts, &chargePercentage) != 0)
    {
        ui->labelBattery->setText(tr("Battery: <b>ERROR</b>"));
        return;
    }

    // Display values
    ui->labelBattery->setText(tr("Battery: <b>%1% (%2V)</b>").arg(chargePercentage).arg(voltageMillivolts / 1000.));
}

void FormRemoteControl::_slotTimerStreamingCameraConnectionTimeout()
{
    // Connect to video stream
    QString ipAddress = Configuration::getValue("LastUsedIpAddress", "127.0.0.1").toString();
    _pointerMediaPlayer->setMedia(QUrl("gst-pipeline: tcpclientsrc host=\"" + ipAddress + "\" port=1234 ! decodebin latency=0 ! xvimagesink name=\"qtvideosink\""));
    _pointerMediaPlayer->play();
}
