/** @file FormBase.hpp
 * Abstract class from which each application form must inherit.
 * @author Adrien RICCIARDI
 */
#ifndef FORMBASE_HPP
#define FORMBASE_HPP

#include <QWidget>

class FormBase : public QWidget
{
    Q_OBJECT

public:
    explicit FormBase(QWidget *parent = nullptr);
    ~FormBase();

    /** Called just before the view is displayed. */
    virtual void enterView() = 0;

    /** Called just before the view is hidden. */
    virtual void exitView();
};

#endif // FORMBASE_HPP
