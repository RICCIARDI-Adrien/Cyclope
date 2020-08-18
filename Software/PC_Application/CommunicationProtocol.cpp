/** @file CommunicationProtocol.cpp
 * See CommunicationProtocol.hpp for description.
 * @author Adrien RICCIARDI
 */
#include <CommunicationProtocol.hpp>
#include <MainWindow.hpp>
#include <QMessageBox>
#include <QTcpSocket>

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
}
