/** @file CommunicationProtocol.cpp
 * See CommunicationProtocol.hpp for description.
 * @author Adrien RICCIARDI
 */
#include <CommunicationProtocol.hpp>
#include <MainWindow.hpp>
#include <QMessageBox>
#include <QTcpSocket>
#include <QtEndian>

/** How many milliseconds to wait for data to be received from the robot. */
#define COMMUNICATION_PROTOCOL_RECEPTION_TIMEOUT 3000

namespace CommunicationProtocol
{
    /** The socket used to communicate with the robot. */
    static QTcpSocket _socket;

    int connectToRobot(QString ipAddress, QString &referenceErrorMessage)
    {
        // Make sure previous connection is closed
        _socket.disconnectFromHost();

        // Try to connect to server
        _socket.connectToHost(ipAddress, 1235);
        if (!_socket.waitForConnected(COMMUNICATION_PROTOCOL_RECEPTION_TIMEOUT))
        {
            referenceErrorMessage = _socket.errorString();
            return -1;
        }

        return 0;
    }

    void displayConnectionLostMessage(QWidget *pointerParentWidget)
    {
        // Close connection
        _socket.close();

        // Inform user
        QMessageBox::critical(pointerParentWidget, QObject::tr("Robot connection lost"), QObject::tr("Network connection with robot has been lost. Please reconnect."), QMessageBox::Ok);

        // Display connection view
        pointerMainWindow->changeView(MainWindow::VIEW_ID_CONNECT_TO_ROBOT);
    }

    int setRobotMotion(RobotMotion robotMotion)
    {
        static RobotMotion lastMotion = ROBOT_MOTION_STOP;

        // Do not send twice the same command
        if (lastMotion == robotMotion) return 0;

        // Create the command to send
        unsigned char command[2];
        command[0] = COMMUNICATION_PROTOCOL_COMMAND_SET_MOTION;
        command[1] = robotMotion;

        // Send command
        if (_socket.write(reinterpret_cast<char *>(command), sizeof(command)) != sizeof(command))
        {
            // Connection has been lost, consider robot is stopped
            lastMotion = ROBOT_MOTION_STOP;
            return -1;
        }
        else
        {
            // Keep currrent motion for next call
            lastMotion = robotMotion;
            return 0;
        }
    }

    int getBatteryValues(int *pointerVoltageMillivolts, int *pointerChargePercentage)
    {
        // Create the command to send
        unsigned char command = COMMUNICATION_PROTOCOL_COMMAND_GET_BATTERY_VOLTAGE;

        // Send command
        if (_socket.write(reinterpret_cast<char *>(&command), sizeof(command)) != sizeof(command)) return -1;

        // Wait for answer
        if (!_socket.waitForReadyRead(COMMUNICATION_PROTOCOL_RECEPTION_TIMEOUT)) return -1; // Were some data received in time ?

        // Receive answer
        char answer[3];
        if (_socket.read(answer, sizeof(answer)) != sizeof(answer)) return -1;

        // Extract voltage in mV
        quint16 word = qFromBigEndian<quint16>(answer);
        *pointerVoltageMillivolts = word;

        // Extract charge percentage
        *pointerChargePercentage = answer[2];

        return 0;
    }

    int setLightEnabled(bool isEnabled)
    {
        // Create the command to send
        unsigned char command[2];
        command[0] = COMMUNICATION_PROTOCOL_COMMAND_SET_LIGHT_ENABLED;
        command[1] = isEnabled;

        // Send command
        if (_socket.write(reinterpret_cast<char *>(command), sizeof(command)) != sizeof(command)) return -1;
        return 0;
    }

    int powerRobotOff()
    {
        // Create the command to send
        unsigned char command = COMMUNICATION_PROTOCOL_COMMAND_POWER_OFF;

        // Send command
        if (_socket.write(reinterpret_cast<char *>(&command), sizeof(command)) != sizeof(command)) return -1;

        // Cleanfully close network connection
        _socket.close();

        return 0;
    }

    int startArtificialIntelligenceProgram(int programIndex)
    {
        // Create the command to send
        unsigned char command[2];
        command[0] = COMMUNICATION_PROTOCOL_COMMAND_START_AI_PROGRAM;
        command[1] = static_cast<unsigned char>(programIndex);

        // Send command
        if (_socket.write(reinterpret_cast<char *>(command), sizeof(command)) != sizeof(command)) return -1;
        return 0;
    }

    int stopArtificialIntelligenceProgram()
    {
        // Create the command to send
        unsigned char command = COMMUNICATION_PROTOCOL_COMMAND_STOP_CURRENT_AI_PROGRAM;

        // Send command
        if (_socket.write(reinterpret_cast<char *>(&command), sizeof(command)) != sizeof(command)) return -1;
        return 0;
    }

    int setStreamingCameraEnabled(bool isEnabled)
    {
        // Create the command to send
        unsigned char command[2];
        command[0] = COMMUNICATION_PROTOCOL_COMMAND_SET_STREAMING_CAMERA_ENABLED;
        command[1] = isEnabled;

        // Send command
        if (_socket.write(reinterpret_cast<char *>(command), sizeof(command)) != sizeof(command)) return -1;
        return 0;
    }
}
