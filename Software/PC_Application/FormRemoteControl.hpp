/** @file FormRemoteControl.hpp
 * Allow to remote control the robot.
 * @author Adrien RICCIARDI
 */
#ifndef FORMREMOTECONTROL_HPP
#define FORMREMOTECONTROL_HPP

#include <FormBase.hpp>
#include <QMediaPlayer>
#include <QTimer>

namespace Ui
{
    class FormRemoteControl;
}

class FormRemoteControl : public FormBase
{
    Q_OBJECT

public:
    explicit FormRemoteControl(QWidget *parent = nullptr);
    ~FormRemoteControl();

    // See base class documentation
    virtual void enterView();

    // See base class documentation
    virtual void exitView();

private:
    Ui::FormRemoteControl *ui;

    /** Tell whether light is lighted. */
    bool _isLightEnabled;

    /** Tell whether "up arrow" keyboard key is pressed. */
    volatile bool _isUpDirectionKeyPressed = false;
    /** Tell whether "down arrow" keyboard key is pressed. */
    volatile bool _isDownDirectionKeyPressed = false;
    /** Tell whether "left arrow" keyboard key is pressed. */
    volatile bool _isLeftDirectionKeyPressed = false;
    /** Tell whether "right arrow" keyboard key is pressed. */
    volatile bool _isRightDirectionKeyPressed = false;
    /** Automatically set to true if the last pressed key was "up arrow" or "down arrow", otherwise it is set to false. */
    volatile bool _isLastPressedDirectionKeyOnVerticalAxis = false;

    /** Retrieve battery voltage from robot and display it. */
    QTimer _timerBatteryVoltagePolling;
    /** Give some time to the camera to start, then connect to it. */
    QTimer _timerStreamingCameraConnection;

protected:
    // See base class documentation
    void keyPressEvent(QKeyEvent *pointerEvent);
    // See base class documentation
    void keyReleaseEvent(QKeyEvent *pointerEvent);

private:
    /** TODO */
    QMediaPlayer *_pointerMediaPlayer;

    /** Set best robot motion according to pressed keyboard keys. */
    void _selectRobotMotion();

private slots:
    /** Called when "back" button is clicked. */
    void _slotPushButtonBackClicked(bool);

    /** Called when battery voltage polling timer times out. */
    void _slotTimerBatteryVoltagePollingTimeout();
    /** Called when streaming camera connection timer times out. */
    void _slotTimerStreamingCameraConnectionTimeout();
};

#endif // FORMREMOTECONTROL_HPP
