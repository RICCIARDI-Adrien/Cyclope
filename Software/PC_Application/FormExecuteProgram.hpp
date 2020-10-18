/** @file FormExecuteProgram.hpp
 * Run the selected AI program until stopped by the user.
 * @author Adrien RICCIARDI
 */
#ifndef FORMEXECUTEPROGRAM_HPP
#define FORMEXECUTEPROGRAM_HPP

#include <FormBase.hpp>

namespace Ui
{
    class FormExecuteProgram;
}

class FormExecuteProgram : public FormBase
{
    Q_OBJECT

    // See base class documentation
    virtual void enterView();

public:
    explicit FormExecuteProgram(QWidget *parent = nullptr);
    ~FormExecuteProgram();

private:
    Ui::FormExecuteProgram *ui;
};

#endif // FORMEXECUTEPROGRAM_HPP
