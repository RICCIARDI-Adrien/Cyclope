/** @file FormRemoteControl.cpp
 * See FormRemoteControl.hpp for description.
 * @author Adrien RICCIARDI
 */
#include <FormRemoteControl.hpp>
#include <ui_FormRemoteControl.h>

FormRemoteControl::FormRemoteControl(QWidget *parent) :
    FormBase(parent),
    ui(new Ui::FormRemoteControl)
{
    ui->setupUi(this);
}

FormRemoteControl::~FormRemoteControl()
{
    delete ui;
}

void FormRemoteControl::enterView()
{
    // TODO
}
