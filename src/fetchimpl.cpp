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

void FetchImpl::ok_activated() {

	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

	bool success;
	QString remote = checkBoxFetchAllRemotes->isChecked()
		? ""
		: comboBoxRemote->currentText();

	success = git->fetch(remote, checkBoxFetchTags->isChecked(), checkBoxPrune->isChecked());

	QApplication::restoreOverrideCursor();

	if (success) {
		//emit repositorySelected(cloneTo);
		accept();
	}
}