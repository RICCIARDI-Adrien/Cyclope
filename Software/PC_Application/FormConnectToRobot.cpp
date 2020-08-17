/** @file FormConnectToRobot.cpp
 * See FormConnectToRobot.hpp for description.
 * @author Adrien RICCIARDI
 */
#include <CommunicationProtocol.hpp>
#include <FormConnectToRobot.hpp>
#include <QMessageBox>
#include <ui_FormConnectToRobot.h>

FormConnectToRobot::FormConnectToRobot(QWidget *parent) :
    FormBase(parent),
    ui(new Ui::FormConnectToRobot)
{
    ui->setupUi(this);

    // Connect slots
    connect(ui->lineEditIpAddress, &QLineEdit::textChanged, this, &FormConnectToRobot::_slotLineEditIpAddressTextChanged);
    connect(ui->lineEditIpAddress, &QLineEdit::returnPressed, this, &FormConnectToRobot::_slotLineEditIpAddressReturnPressed);
    connect(ui->pushButtonConnect, &QPushButton::clicked, this, &FormConnectToRobot::_slotPushButtonConnectClicked);
}

FormConnectToRobot::~FormConnectToRobot()
{
    delete ui;
}

void FormConnectToRobot::enterView()
{
    // TODO
}

void FormConnectToRobot::_slotLineEditIpAddressTextChanged(const QString &referenceText)
{
    // Enable "connect" button only if some text is present in the line edit
    if (referenceText.length() > 0) ui->pushButtonConnect->setEnabled(true);
    else ui->pushButtonConnect->setEnabled(false);
}

void FormConnectToRobot::_slotLineEditIpAddressReturnPressed()
{
    // Simulate a button press only if there is some text in the line edit
    if (ui->lineEditIpAddress->text().length() > 0) _slotPushButtonConnectClicked(false);
}

void FormConnectToRobot::_slotPushButtonConnectClicked(bool)
{
    // Try to connect to robot
    QString errorMessage;
    if (CommunicationProtocol::connectToRobot(ui->lineEditIpAddress->text(), errorMessage) != 0)
    {
        QMessageBox::critical(this, tr("Connection error"), tr("Error: can't connect to wrench.\n%1.").arg(errorMessage));
        return;
    }

    // TODO display next view
}
