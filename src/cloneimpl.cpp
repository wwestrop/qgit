#include <QDir>
#include <QFileDialog>
#include <QClipboard>
#include <QSettings>
#include "common.h"
#include "cloneimpl.h"
#include "git.h"

using namespace QGit;

CloneImpl::CloneImpl(Git *git, QWidget *parent) : QDialog(parent) {

	this->git = git;

	setupUi(this);

	QSettings settings;
	lineEditCloneTo->setText(settings.value(DEF_CLONE_DIR, QDir::homePath()).toString());

	auto clipboardContent = QApplication::clipboard()->text();
	if (isLikelyGitUrl(clipboardContent)) {
		lineEditCloneFrom->setText(clipboardContent);
	}
}

bool CloneImpl::isLikelyGitUrl(const QString& s) const {

	auto normalised = s.endsWith("/")
		? s.chopped(1)
		: s;

	if (normalised.endsWith(gitUrlSuffix)) return true;

	if (normalised.startsWith("https://github.com/")) return true;
	if (normalised.startsWith("https://gitlab.com/")) return true;

	// These patterns match Azure DevOps
	auto hostPortion = normalised.left(normalised.indexOf("/"));
	if (normalised.startsWith("https://dev.azure.com/")) return true;
	if (hostPortion.endsWith(".visualstudio.com/")) return true;
	if (hostPortion.endsWith("@vs-ssh.visualstudio.com:v3/")) return true;

	return false;
}

void CloneImpl::ok_activated() {

	auto cloneUrl = lineEditCloneFrom->text();
	auto cloneTo = lineEditCloneTo->text() + "/" + lineEditCloneAs->text();
	cloneTo = getAbsolutePath(cloneTo);
	bool recurse = checkBoxCloneSubmodules->checkState();

	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
	bool success = git->clone(cloneUrl, cloneTo, recurse);
	QApplication::restoreOverrideCursor();

	if (success) {
		emit repositorySelected(cloneTo);
		accept();
	}
}

QString CloneImpl::getAbsolutePath(const QString& path) const {

	if (path.startsWith("~/")) {
		return QDir::homePath() + path.right(path.length() - 1);
	}
	else {
		return path;
	}
}

void CloneImpl::cloneFrom_textChanged(const QString& gitCloneUrl) {

	auto stringIndex = gitCloneUrl.lastIndexOf("/") + 1;
	auto suggestedName = gitCloneUrl.right(gitCloneUrl.length() - stringIndex);
	if (suggestedName.endsWith("/")) suggestedName.chop(1);
	if (suggestedName.endsWith(gitUrlSuffix)) {
		suggestedName.chop(gitUrlSuffix.length());
	}

	lineEditCloneAs->setText(suggestedName);
}

void CloneImpl::chooseDir_activated() {

	auto dirName = QFileDialog::getExistingDirectory(this, "Choose a directory", lineEditCloneTo->text());
	if (!dirName.isEmpty()) {
		lineEditCloneTo->setText(dirName);
	}
}
