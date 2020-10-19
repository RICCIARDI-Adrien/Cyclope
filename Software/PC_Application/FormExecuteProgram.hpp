/** @file FormExecuteProgram.hpp
 * Run the selected AI program until stopped by the user.
 * @author Adrien RICCIARDI
 */
#ifndef FORMEXECUTEPROGRAM_HPP
#define FORMEXECUTEPROGRAM_HPP

#include <FormBase.hpp>
#include <QTimer>

namespace Ui
{
    class FormExecuteProgram;
}

class FormExecuteProgram : public FormBase
{
    Q_OBJECT

    // See base class documentation
    virtual void enterView();

    // See base class documentation
    virtual void exitView();

public:
    explicit FormExecuteProgram(QWidget *parent = nullptr);
    ~FormExecuteProgram();

private:
    Ui::FormExecuteProgram *ui;

    /** Retrieve battery voltage from robot and display it. */
    QTimer _timerBatteryVoltagePolling;

private slots:
    /** Called when battery voltage polling timer times out. */
    void _slotTimerBatteryVoltagePollingTimeout();
};

#endif // FORMEXECUTEPROGRAM_HPP
