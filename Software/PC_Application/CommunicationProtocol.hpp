/** @file CommunicationProtocol.hpp
 * Communicate with robot through a TCP connection.
 * @author Adrien RICCIARDI
 */
#ifndef COMMUNICATIONPROTOCOL_HPP
#define COMMUNICATIONPROTOCOL_HPP

#include <QString>

namespace CommunicationProtocol
{
    /** Connect to the robot.
     * @param ipAddress Robot IP address.
     * @param referenceErrorMessage On output, contain an error message if an error occurred.
     * @return -1 if a connection error occurred,
     * @return 0 on success.
     */
    int connectToRobot(QString ipAddress, QString &referenceErrorMessage); // It's better not to use 'connect()' method name to avoid messing with Qt signal system
}

#endif // COMMUNICATIONPROTOCOL_HPP
