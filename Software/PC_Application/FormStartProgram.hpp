/** @file FormStartProgram.hpp
 * Allow to choose an AI program to start from a list.
 * @author Adrien RICCIARDI
 */
#ifndef FORMSTARTPROGRAM_HPP
#define FORMSTARTPROGRAM_HPP

#include <FormBase.hpp>
#include <QListWidgetItem>

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

private slots:
    /** Called when an item of the list is clicked. */
    void _slotListWidgetItemClicked(QListWidgetItem *);

    /** Called when "run" button is clicked. */
    void _slotPushButtonRunClicked(bool);
    /** Called when "back" button is clicked. */
    void _slotPushButtonBackClicked(bool);
};

#endif // FORMSTARTPROGRAM_HPP
