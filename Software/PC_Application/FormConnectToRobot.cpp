/** @file FormConnectToRobot.cpp
 * See FormConnectToRobot.hpp for description.
 * @author Adrien RICCIARDI
 */
#include <FormConnectToRobot.hpp>
#include <ui_FormConnectToRobot.h>

FormConnectToRobot::FormConnectToRobot(QWidget *parent) :
    FormBase(parent),
    ui(new Ui::FormConnectToRobot)
{
    ui->setupUi(this);
}

FormConnectToRobot::~FormConnectToRobot()
{
    delete ui;
}

// See base class documentation
void FormConnectToRobot::enterView()
{
    // TODO
}
