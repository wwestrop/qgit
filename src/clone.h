#ifndef CLONE_H
#define CLONE_H

#include "git.h"
#include <QDialog>

namespace Ui {
class Clone;
}

class Clone : public QDialog
{
    Q_OBJECT

public:
    explicit Clone(Git *git, QWidget *parent = nullptr);
    ~Clone();

signals:
    void repositorySelected(QString repositoryPath);

private slots:
    void cloneFromChanged(QString gitCloneUrl);
    void ok_activated();

private:
    Ui::Clone *ui;
    QString checkClipboardForGitUrl() const;
    QString cloneToDefault = "~/";
    const QString gitUrlSuffix = ".git";
    bool performGitClone(QString& cloneUrl, QString& cloneTo, bool recurse);
    QString getAbsolutePath(QString& path) const;
    Git* git;
};

#endif // CLONE_H
