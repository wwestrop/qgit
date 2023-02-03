#ifndef WAIT_H
#define WAIT_H

#include <QDialog>

namespace Ui {
class Wait;
}

class Wait : public QDialog
{
    Q_OBJECT

public:
    //explicit Wait(QWidget *parent = nullptr);
    explicit Wait(QWidget *parent, std::function<void()> awaitedAction, QString caption = "Please Wait");
    ~Wait();

protected:
    virtual void showEvent(QShowEvent *);

private:
    Ui::Wait *ui;
    std::function<void()> awaitedAction;
};

#endif // WAIT_H
