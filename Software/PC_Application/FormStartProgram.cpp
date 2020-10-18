#include <FormStartProgram.hpp>
#include <ui_FormStartProgram.h>

FormStartProgram::FormStartProgram(QWidget *parent) :
    FormBase(parent),
    ui(new Ui::FormStartProgram)
{
    ui->setupUi(this);

    // Fill list
    ui->listWidget->addItem(tr("Follow tennis ball"));
}

FormStartProgram::~FormStartProgram()
{
    delete ui;
}

void FormStartProgram::enterView()
{
    // Focus the AI program list
    ui->listWidget->setFocus();
}
