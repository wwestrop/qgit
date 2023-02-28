#ifndef FETCHIMPL_H
#define FETCHIMPL_H

#include "git.h"
#include "ui_fetch.h"

class FetchImpl : public QDialog, public Ui_fetchBase {
Q_OBJECT

public:
    FetchImpl(QWidget *parent, Git *git);

public slots:
	void checkboxFetchAll_toggled(bool);

private:
    Git* git;
};

#endif // FETCHIMPL_H
