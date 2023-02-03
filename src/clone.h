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

private slots:
    void cloneFromChanged(QString gitCloneUrl);

private:
    Ui::Clone *ui;
    QString checkClipboardForGitUrl();
    QString cloneToDefault = "~/";
    const QString gitUrlSuffix = ".git";
};

#endif // CLONE_H
