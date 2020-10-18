/** @file FormExecuteProgram.cpp
 * See FormExecuteProgram.hpp for description.
 * @author Adrien RICCIARDI
 */
#include <FormExecuteProgram.hpp>
#include <ui_FormExecuteProgram.h>

FormExecuteProgram::FormExecuteProgram(QWidget *parent) :
    FormBase(parent),
    ui(new Ui::FormExecuteProgram)
{
    ui->setupUi(this);
}

FormExecuteProgram::~FormExecuteProgram()
{
    delete ui;
}

void FormExecuteProgram::enterView()
{
    // TODO
}
