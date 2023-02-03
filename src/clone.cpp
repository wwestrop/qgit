#include "clone.h"
#include "qclipboard.h"
#include "qmessagebox.h"
#include "ui_clone.h"
#include "wait.h"

Clone::Clone(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Clone)
{
    ui->setupUi(this);

    auto gitCloneUrl = checkClipboardForGitUrl();
    if (gitCloneUrl != nullptr) {
        ui->cloneFrom->setText(gitCloneUrl);
    }
}

QString Clone::checkClipboardForGitUrl() {
    auto *clipboard = QApplication::clipboard();
    auto text = clipboard->text();

    if (text.endsWith("/")) text = text.left(text.length() - 1);

    return text.endsWith(gitUrlSuffix)
        ? text
        : nullptr;
}

void Clone::ok_activated() {
    auto cloneUrl = ui->cloneFrom->text();
    auto cloneTo = ui ->cloneTo->text(); // TODO append "as" and ensure proper dir separators
    bool recurse = ui->cloneSubmodules->checkState();

    auto x = [&]() { this->performGitClone(cloneUrl, cloneTo, recurse); };

//    Wait waitDialog(this, x, "Cloning repository");
//    waitDialog.exec();

    x();


    emit repositorySelected(cloneTo);
    accept();
}

void Clone::performGitClone(QString cloneUrl, QString cloneTo, bool recurse) {
    QMessageBox::warning(this, "Windows", "Let's pretend this is doing the clone");
}

void Clone::cloneFromChanged(QString gitCloneUrl) {

    QString suggestedName;
    auto stringIndex = gitCloneUrl.lastIndexOf("/") + 1;
    suggestedName = gitCloneUrl.right(gitCloneUrl.length() - stringIndex);
    if (suggestedName.endsWith("/")) suggestedName = suggestedName.left(suggestedName.length() - 1);
    if (suggestedName.endsWith(gitUrlSuffix)) {
        suggestedName = suggestedName.left(suggestedName.length() - gitUrlSuffix.length());
    }

    ui->cloneAs->setText(suggestedName);
}

Clone::~Clone()
{
    delete ui;
}
