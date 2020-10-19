/** @file FormExecuteProgram.cpp
 * See FormExecuteProgram.hpp for description.
 * @author Adrien RICCIARDI
 */
#include <CommunicationProtocol.hpp>
#include <FormExecuteProgram.hpp>
#include <ui_FormExecuteProgram.h>

FormExecuteProgram::FormExecuteProgram(QWidget *parent) :
    FormBase(parent),
    ui(new Ui::FormExecuteProgram)
{
    ui->setupUi(this);

    // Connect slots
    connect(&_timerBatteryVoltagePolling, &QTimer::timeout, this, &FormExecuteProgram::_slotTimerBatteryVoltagePollingTimeout);
}

FormExecuteProgram::~FormExecuteProgram()
{
    delete ui;
}

void FormExecuteProgram::enterView()
{
    // Start displaying voltage
    _timerBatteryVoltagePolling.start(3000);
    _slotTimerBatteryVoltagePollingTimeout(); // Immediately display values
}

void FormExecuteProgram::exitView()
{
    // Battery voltage is no more needed
    _timerBatteryVoltagePolling.stop();
}

void FormExecuteProgram::_slotTimerBatteryVoltagePollingTimeout()
{
    // Retrieve values from robot
    int voltageMillivolts, chargePercentage;
    if (CommunicationProtocol::getBatteryValues(&voltageMillivolts, &chargePercentage) != 0)
    {
        ui->labelBattery->setText(tr("Battery: <b>ERROR</b>"));
        return;
    }

    // Display values
    ui->labelBattery->setText(tr("Battery: <b>%1% (%2V)</b>").arg(chargePercentage).arg(voltageMillivolts / 1000.));
}
