/** @file FormExecuteProgram.cpp
 * See FormExecuteProgram.hpp for description.
 * @author Adrien RICCIARDI
 */
#include <CommunicationProtocol.hpp>
#include <FormExecuteProgram.hpp>
#include <MainWindow.hpp>
#include <ui_FormExecuteProgram.h>

FormExecuteProgram::FormExecuteProgram(QWidget *parent) :
    FormBase(parent),
    ui(new Ui::FormExecuteProgram)
{
    ui->setupUi(this);

    // Connect slots
    connect(&_timerBatteryVoltagePolling, &QTimer::timeout, this, &FormExecuteProgram::_slotTimerBatteryVoltagePollingTimeout);
    connect(ui->pushButtonStop, &QPushButton::clicked, this, &FormExecuteProgram::_slotPushButtonStopClicked);
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

void FormExecuteProgram::_slotPushButtonStopClicked(bool)
{
    // Tell robot to stop current program
    if (CommunicationProtocol::stopArtificialIntelligenceProgram() != 0)
    {
        CommunicationProtocol::displayConnectionLostMessage(this);
        return;
    }

    pointerMainWindow->changeView(MainWindow::VIEW_ID_MAIN_MENU);
}
