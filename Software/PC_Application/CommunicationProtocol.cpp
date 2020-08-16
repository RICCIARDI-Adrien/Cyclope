/** @file CommunicationProtocol.cpp
 * See CommunicationProtocol.hpp for description.
 * @author Adrien RICCIARDI
 */
#include <CommunicationProtocol.hpp>
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
}
