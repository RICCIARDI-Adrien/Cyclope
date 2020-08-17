/** @file FormMainMenu.hpp
 * Application main menu. All application features are available from this view.
 * @author Adrien RICCIARDI
 */
#ifndef FORMMAINMENU_HPP
#define FORMMAINMENU_HPP

#include <FormBase.hpp>

namespace Ui
{
    class FormMainMenu;
}

class FormMainMenu : public FormBase
{
    Q_OBJECT

public:
    explicit FormMainMenu(QWidget *parent = nullptr);
    ~FormMainMenu();

    // See base class documentation
    virtual void enterView();

private:
    Ui::FormMainMenu *ui;
};

#endif // FORMMAINMENU_HPP
