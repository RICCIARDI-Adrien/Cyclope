/** @file CommunicationProtocol.hpp
 * Communicate with robot through a TCP connection.
 * @author Adrien RICCIARDI
 */
#ifndef COMMUNICATIONPROTOCOL_HPP
#define COMMUNICATIONPROTOCOL_HPP

#include <QString>
#include <QWidget>

namespace CommunicationProtocol
{
    /** All robot known commands. */
    typedef enum
    {
        COMMUNICATION_PROTOCOL_COMMAND_SET_MOTION,
        COMMUNICATION_PROTOCOL_COMMAND_GET_BATTERY_VOLTAGE,
        COMMUNICATION_PROTOCOL_COMMAND_GET_MOTOR_DUTY_CYCLE,
        COMMUNICATION_PROTOCOL_COMMAND_SET_MOTOR_DUTY_CYCLE,
        COMMUNICATION_PROTOCOL_COMMAND_SET_LIGHT_ENABLED,
        COMMUNICATION_PROTOCOL_COMMAND_POWER_OFF,
        COMMUNICATION_PROTOCOL_COMMAND_LIST_AVAILABLE_AI_PROGRAMS,
        COMMUNICATION_PROTOCOL_COMMAND_START_AI_PROGRAM,
        COMMUNICATION_PROTOCOL_COMMAND_STOP_CURRENT_AI_PROGRAM,
        COMMUNICATION_PROTOCOL_COMMAND_SET_STREAMING_CAMERA_ENABLED,
        COMMUNICATION_PROTOCOL_COMMANDS_COUNT
    } CommunicationProtocolCommand;

    /** All possible motions the robot can perform. */
    typedef enum
    {
        ROBOT_MOTION_STOP,
        ROBOT_MOTION_FORWARD,
        ROBOT_MOTION_BACKWARD,
        ROBOT_MOTION_FORWARD_LEFT,
        ROBOT_MOTION_FORWARD_RIGHT,
        ROBOT_MOTION_BACKWARD_LEFT,
        ROBOT_MOTION_BACKWARD_RIGHT
    } RobotMotion;

    /** Connect to the robot.
     * @param ipAddress Robot IP address.
     * @param referenceErrorMessage On output, contain an error message if an error occurred.
     * @return -1 if a connection error occurred,
     * @return 0 on success.
     */
    int connectToRobot(QString ipAddress, QString &referenceErrorMessage); // It's better not to use 'connect()' method name to avoid messing with Qt signal system

    /** Display a dialog telling that connection with server has been lost, close network connection has gracefully as possible and return to connection view.
     * @param pointerParentWidget The widget into which the dialog will be centered.
     */
    void displayConnectionLostMessage(QWidget *pointerParentWidget);

    /** Tell robot to move or to stop.
     * @param robotMotion The motion to set.
     * @return -1 if an error occurred,
     * @return 0 on success.
     */
    int setRobotMotion(RobotMotion robotMotion);

    /** Sample battery voltage from ADC and convert it to usable values.
     * @param pointerVoltageMillivolts On output, contain the battery voltage in mV.
     * @param pointerPercentage On output, contain the battery charge percentage. See method implementation for more details about computing charge percentage.
     * @return -1 if an error occurred,
     * @return 0 on success.
     */
    int getBatteryValues(int *pointerVoltageMillivolts, int *pointerChargePercentage);

    /** Turn light on or off.
     * @param isEnabled Set to false to turn light off, set to true to turn light on.
     * @return -1 if an error occurred,
     * @return 0 on success.
     */
    int setLightEnabled(bool isEnabled);

    /** Tell robot to immediately shutdown.
     * @return -1 if an error occurred,
     * @return 0 on success.
     */
    int powerRobotOff();

    /** Run a specific AI program on the robot.
     * @param programIndex The program to run. Robot does nothing if it does not know the requested program.
     * @return -1 if an error occurred,
     * @return 0 on success.
     */
    int startArtificialIntelligenceProgram(int programIndex);

    /** Stop currently running AI program.
     * @return -1 if an error occurred,
     * @return 0 on success.
     */
    int stopArtificialIntelligenceProgram();

    /** Turn streaming camera on or off.
     * @param isEnabled Set to false to disable camera, set to true to enable camera.
     * @return -1 if an error occurred,
     * @return 0 on success.
     * @note Do not enable streaming camera when an AI program is running, this could conflict with AI program camera usage.
     * @note The streaming camera is automatically stopped when an AI program starts execution.
     */
    int setStreamingCameraEnabled(bool isEnabled);
}

#endif // COMMUNICATIONPROTOCOL_HPP
