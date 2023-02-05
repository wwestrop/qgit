#include "clone.h"
#include "git.h"
#include "qclipboard.h"
#include "qmessagebox.h"
#include "ui_clone.h"
#include "wait.h"

#include <QDir>
#include <QFileDialog>

Clone::Clone(Git *git, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Clone)
{
    this->git = git;

    ui->setupUi(this);
    ui->cloneTo->setText(QDir::homePath());   // TODO or read default from settings TODO this line causes memory bugs when closing this form...

    auto gitCloneUrl = checkClipboardForGitUrl();
    if (gitCloneUrl != nullptr) {
        ui->cloneFrom->setText(gitCloneUrl);
    }
}

QString Clone::checkClipboardForGitUrl() const {
    auto *clipboard = QApplication::clipboard();
    auto text = clipboard->text();

    if (text.endsWith("/")) text = text.left(text.length() - 1);

    // TODO be more thorough about supported formats (e.g. raw github URL can also be cloned)
    return text.endsWith(gitUrlSuffix)
        ? text
        : nullptr;
}

void Clone::ok_activated() {
    auto cloneUrl = ui->cloneFrom->text();
    auto cloneTo = ui ->cloneTo->text() + "/" + ui->cloneAs->text();
    cloneTo = getAbsolutePath(cloneTo);
    bool recurse = ui->cloneSubmodules->checkState();

    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    bool success = performGitClone(cloneUrl, cloneTo, recurse);
    QApplication::restoreOverrideCursor();

    if (success) {
        emit repositorySelected(cloneTo);
        accept();
    }
}

QString Clone::getAbsolutePath(QString& path) const {
    // TODO find a way to do this in the general case
    if (path.startsWith("~/")) {
        return QDir::homePath() + path.right(path.length() - 1);
    }
    else {
        return path;
    }
}

bool Clone::performGitClone(QString& cloneUrl, QString& cloneTo, bool recurse) {
    return git->clone(cloneUrl, cloneTo, recurse);
}

void Clone::cloneFrom_textChanged(QString gitCloneUrl) {

    QString suggestedName;
    auto stringIndex = gitCloneUrl.lastIndexOf("/") + 1;
    suggestedName = gitCloneUrl.right(gitCloneUrl.length() - stringIndex);
    if (suggestedName.endsWith("/")) suggestedName = suggestedName.left(suggestedName.length() - 1);
    if (suggestedName.endsWith(gitUrlSuffix)) {
        suggestedName = suggestedName.left(suggestedName.length() - gitUrlSuffix.length());
    }

    ui->cloneAs->setText(suggestedName);
}

void Clone::chooseDir_activated() {
    auto dirName = QFileDialog::getExistingDirectory(this, "Choose a directory", ui->cloneTo->text());
    if (!dirName.isEmpty()) {
        ui->cloneTo->setText(dirName);
    }
}

Clone::~Clone()
{
    delete ui;
}
