/** @file FormConnectToRobot.hpp
 * Specify robot IP address and try to connect to Cyclope controller server.
 * @author Adrien RICCIARDI
 */
#ifndef FORMCONNECTTOROBOT_HPP
#define FORMCONNECTTOROBOT_HPP

#include <FormBase.hpp>

namespace Ui
{
    class FormConnectToRobot;
}

class FormConnectToRobot : public FormBase
{
    Q_OBJECT

public:
    explicit FormConnectToRobot(QWidget *parent = nullptr);
    ~FormConnectToRobot();

    // See base class documentation
    virtual void enterView();

private:
    Ui::FormConnectToRobot *ui;
};

#endif // FORMCONNECTTOROBOT_HPP
