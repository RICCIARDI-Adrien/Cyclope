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

private slots:
    /** Called when IP address line edit text is modified (either by user or programmatically). */
    void _slotLineEditIpAddressTextChanged(const QString &referenceText);
    /** Called when user pressed enter key while IP address line edit is focused. */
    void _slotLineEditIpAddressReturnPressed();

    /** Called when "connect" button is clicked. */
    void _slotPushButtonConnectClicked(bool);
};

#endif // FORMCONNECTTOROBOT_HPP
