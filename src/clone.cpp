#include "clone.h"
#include "ui_clone.h"

Clone::Clone(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Clone)
{
    ui->setupUi(this);
}

Clone::~Clone()
{
    delete ui;
}
