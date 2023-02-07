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
    void cloneFrom_textChanged(const QString& gitCloneUrl);
    void chooseDir_activated();
    void ok_activated();

//protected:
//    virtual void focusInEvent( QFocusEvent* e);

private:
    Ui::Clone *ui;
    bool isLikelyGitUrl(const QString& s) const;
    const QString gitUrlSuffix = ".git";
    bool performGitClone(const QString& cloneUrl, const QString& cloneTo, bool recurse);
    QString getAbsolutePath(const QString& path) const;
    Git* git;
};

#endif // CLONE_H
