#ifndef FORMSTARTPROGRAM_HPP
#define FORMSTARTPROGRAM_HPP

#include <FormBase.hpp>

namespace Ui
{
    class FormStartProgram;
}

class FormStartProgram : public FormBase
{
    Q_OBJECT

public:
    explicit FormStartProgram(QWidget *parent = nullptr);
    ~FormStartProgram();

    // See base class documentation
    virtual void enterView();

private:
    Ui::FormStartProgram *ui;
};

#endif // FORMSTARTPROGRAM_HPP
