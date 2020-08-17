/** @file FormMainMenu.cpp
 * See FormMainMenu.hpp for description.
 * @author Adrien RICCIARDI
 */
#include <FormMainMenu.hpp>
#include <ui_FormMainMenu.h>

FormMainMenu::FormMainMenu(QWidget *parent) :
    FormBase(parent),
    ui(new Ui::FormMainMenu)
{
    ui->setupUi(this);
}

FormMainMenu::~FormMainMenu()
{
    delete ui;
}

// See base class documentation
void FormMainMenu::enterView()
{
    // TODO
}
