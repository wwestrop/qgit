#ifndef CLONE_H
#define CLONE_H

#include <QDialog>

namespace Ui {
class Clone;
}

class Clone : public QDialog
{
    Q_OBJECT

public:
    explicit Clone(QWidget *parent = nullptr);
    ~Clone();

private:
    Ui::Clone *ui;
};

#endif // CLONE_H
