#include "clone.h"
#include "qclipboard.h"
#include "ui_clone.h"

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

    return text.endsWith(gitUrlSuffix)
        ? text
        : nullptr;
}

void Clone::cloneFromChanged(QString gitCloneUrl) {

    QString suggestedName;
    auto stringIndex = gitCloneUrl.lastIndexOf("/") + 1;
    suggestedName = gitCloneUrl.right(gitCloneUrl.length() - stringIndex);
    if (suggestedName.endsWith(gitUrlSuffix)) {
        suggestedName = suggestedName.left(suggestedName.length() - gitUrlSuffix.length());
    }

    ui->cloneAs->setText(suggestedName);
}

Clone::~Clone()
{
    delete ui;
}
