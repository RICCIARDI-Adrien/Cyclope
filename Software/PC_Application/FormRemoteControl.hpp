/** @file FormRemoteControl.hpp
 * Allow to remote control the robot.
 * @author Adrien RICCIARDI
 */
#ifndef FORMREMOTECONTROL_HPP
#define FORMREMOTECONTROL_HPP

#include <FormBase.hpp>

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

private:
    Ui::FormRemoteControl *ui;
};

#endif // FORMREMOTECONTROL_HPP
