#include <QClipboard>
#include <QSettings>
#include "common.h"
#include "clone.h"
#include "git.h"
#include "ui_clone.h"

#include <QDir>
#include <QFileDialog>

using namespace QGit;

Clone::Clone(Git *git, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Clone)
{
    this->git = git;

    ui->setupUi(this);

    QSettings settings;
    ui->cloneTo->setText(settings.value(DEF_CLONE_DIR).toString());

    auto clipboardContent = QApplication::clipboard()->text();
    if (isLikelyGitUrl(clipboardContent)) {
        ui->cloneFrom->setText(clipboardContent);
    }
}

bool Clone::isLikelyGitUrl(const QString& s) const {

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

QString Clone::getAbsolutePath(const QString& path) const {

    if (path.startsWith("~/")) {
        return QDir::homePath() + path.right(path.length() - 1);
    }
    else {
        return path;
    }
}

bool Clone::performGitClone(const QString& cloneUrl, const QString& cloneTo, bool recurse) {

    return git->clone(cloneUrl, cloneTo, recurse);
}

void Clone::cloneFrom_textChanged(const QString& gitCloneUrl) {

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
