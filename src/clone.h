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

signals:
    //void repositorySelected(QString cloneUrl, QString cloneTo, bool recurse);
    void repositorySelected(QString repositoryPath);

private slots:
    void cloneFromChanged(QString gitCloneUrl);
    void ok_activated();

private:
    Ui::Clone *ui;
    QString checkClipboardForGitUrl();
    QString cloneToDefault = "~/";
    const QString gitUrlSuffix = ".git";
    void performGitClone(QString cloneUrl, QString cloneTo, bool recurse);
    QString getAbsolutePath(QString path);
};

#endif // CLONE_H
