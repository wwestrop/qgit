#ifndef CLONEIMPL_H
#define CLONEIMPL_H

#include <QDialog>
#include "git.h"
#include "ui_clone.h"

namespace Ui {
class CloneImpl;
}

class CloneImpl : public QDialog, public Ui_CloneBase
{
    Q_OBJECT

public:
    CloneImpl(Git *git, QWidget *parent = nullptr);

signals:
    void repositorySelected(QString repositoryPath);

private slots:
    void cloneFrom_textChanged(const QString& gitCloneUrl);
    void chooseDir_activated();
    void ok_activated();

//protected:
//    virtual void focusInEvent( QFocusEvent* e);

private:
    Ui::CloneImpl *ui;
    bool isLikelyGitUrl(const QString& s) const;
    const QString gitUrlSuffix = ".git";
    bool performGitClone(const QString& cloneUrl, const QString& cloneTo, bool recurse);
    QString getAbsolutePath(const QString& path) const;
    Git* git;
};

#endif // CLONEIMPL_H
