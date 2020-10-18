/** @file FormStartProgram.cpp
 * See FormStartProgram.hpp for description.
 * @author Adrien RICCIARDI
 */
#include <FormStartProgram.hpp>
#include <MainWindow.hpp>
#include <ui_FormStartProgram.h>

FormStartProgram::FormStartProgram(QWidget *parent) :
    FormBase(parent),
    ui(new Ui::FormStartProgram)
{
    ui->setupUi(this);

    // Fill list on startup as its content won't change
    ui->listWidget->addItem(tr("Follow tennis ball"));

    // Connect slots
    connect(ui->listWidget, &QListWidget::itemClicked, this, &FormStartProgram::_slotListWidgetItemClicked);
    connect(ui->pushButtonBack, &QPushButton::clicked, this, &FormStartProgram::_slotPushButtonBackClicked);
}

FormStartProgram::~FormStartProgram()
{
    delete ui;
}

void FormStartProgram::enterView()
{
    // Focus the AI program list
    ui->listWidget->setFocus();

    // Disable "run" button until a program has been selected
    ui->pushButtonRun->setEnabled(false);
}

void FormStartProgram::_slotListWidgetItemClicked(QListWidgetItem *)
{
    // Allow user to run the selected program
    ui->pushButtonRun->setEnabled(true);
}

void FormStartProgram::_slotPushButtonBackClicked(bool)
{
    pointerMainWindow->changeView(MainWindow::VIEW_ID_MAIN_MENU);
}
