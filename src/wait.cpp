#include "wait.h"
#include "ui_wait.h"

//Wait::Wait(QWidget *parent) :
//    QDialog(parent),
//    ui(new Ui::Wait)
//{
//    ui->setupUi(this);

//    setFixedSize(width(), height());
//    //setWindowFlags(windowFlags() & ~Qt::WindowCloseButtonHint);
//}

Wait::Wait(QWidget *parent, std::function<void()> awaitedAction, QString caption) :
    QDialog(parent),
    //Wait(parent),
    ui(new Ui::Wait)
{
    ui->setupUi(this);

    setFixedSize(width(), height());
    //setWindowFlags(windowFlags() & ~Qt::WindowCloseButtonHint);

    ui->caption->setText(caption + "...");
    this->awaitedAction = awaitedAction;

    // TODO really this probably needs to be put on another thread, oh well I'm making this up as I go along
    awaitedAction();

    close();
}

void Wait::showEvent(QShowEvent *e)
{
//    // TODO really this probably needs to be put on another thread, oh well I'm making this up as I go along
//    awaitedAction();

//    close();
}

Wait::~Wait()
{
    delete ui;
}
