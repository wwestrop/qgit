#include "common.h"
#include "fetchimpl.h"
#include "git.h"

FetchImpl::FetchImpl(QWidget *parent, Git *git) : QDialog(parent), git(git) {

    setupUi(this);
	checkBoxFetchAllRemotes->setChecked(true);

	comboBoxRemote->clear();
	FOREACH_SL(it, git->getRemotes())
		comboBoxRemote->addItem(*it);
}

void FetchImpl::checkboxFetchAll_toggled(bool b) {

	widgetRemote->setEnabled(!b);
}