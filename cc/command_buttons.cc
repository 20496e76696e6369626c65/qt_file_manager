#include "h/command_buttons.h"

#include <QInputDialog>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QFileInfo>
#include <QDir>
#include <QDesktopServices>
#include <QUrl>

#include "h/table_view.h"
#include "h/view_panel_tab.h"

CommandButtons::CommandButtons(QWidget *parent) : QWidget (parent)
{

    QHBoxLayout* layout = new QHBoxLayout;

    layout->addWidget(view_ = new QPushButton(tr("View")));
    layout->addWidget(edit_ = new QPushButton(tr("Rename")));
    layout->addWidget(mk_file_ = new QPushButton(tr("New File")));
    layout->addWidget(move_ = new QPushButton(tr("Move")));
    layout->addWidget(mk_dir_ = new QPushButton(tr("Make Dir")));
    layout->addWidget(delete_ = new QPushButton(tr("Delete")));
    layout->addWidget(exit_ = new QPushButton(tr("Exit")));

    QMargins margins(0, 0, 0, 0);

    view_->setContentsMargins(margins);
    edit_->setContentsMargins(margins);
    mk_file_->setContentsMargins(margins);
    move_->setContentsMargins(margins);
    exit_->setContentsMargins(margins);
    mk_dir_->setContentsMargins(margins);
    delete_->setContentsMargins(margins);
    layout->setMargin(0);

    setLayout(layout);

    connect(view_,     SIGNAL(pressed()), this, SLOT(PushView()));
    connect(edit_,     SIGNAL(pressed()), this, SLOT(PushEdit()));
    connect(mk_file_,  SIGNAL(pressed()), this, SLOT(PushMkFile()));
    connect(move_,     SIGNAL(pressed()), this, SLOT(PushMove()));
    connect(mk_dir_,   SIGNAL(pressed()), this, SLOT(PushMkDir()));
    connect(delete_,   SIGNAL(pressed()), this, SLOT(PushDelete()));
    connect(exit_,     SIGNAL(pressed()), this, SLOT(PushExit()));

}
void CommandButtons::PushView()
{
    QString path = ViewPanelTab::path + QDir::separator();
    QString to_open = path + TableView::item.data().toString();

    if (!QFileInfo(to_open).isDir())
    {
        QFileInfo info(to_open);
        QString file_path = info.absoluteFilePath();
        QUrl file_url = QUrl::fromUserInput(file_path);
        QDesktopServices::openUrl(file_url);
    }
}

void CommandButtons::PushEdit()
{
    QString current_path = ViewPanelTab::path + QDir::separator();
    QString current_name = TableView::item.data().toString();
    qDebug()<<current_name;
    qDebug()<<current_path;
    QInputDialog dialog;
    dialog.setWindowTitle("Rename");
    dialog.setLabelText("Enter your new file/folder name:");
    dialog.setTextValue(current_name);
    if (dialog.exec())
    {
        QString new_name = dialog.textValue();
        if ((new_name==current_name)||(QFile(current_path+new_name).exists()))
        {
            QMessageBox msg;
            msg.setWindowTitle("Error");
            msg.setIcon(QMessageBox::Critical);
            msg.setText("A file or folder already exists with that same name.");
            msg.exec();
        }
        else
        {
            QString new_path = current_path+new_name;
            QString old_path = current_path+current_name;
            bool ret = QFile(old_path).rename(new_path);
            if (ret==false)
            {
                QMessageBox msg;
                msg.setWindowTitle("Error");
                msg.setIcon(QMessageBox::Critical);
                msg.setText("There was an error renaming this file or folder!");
                msg.setDetailedText("This could mean that the file is read-only, "
                                    "or that you do not have the proper permissions "
                                    "to access it.");
                msg.exec();
            }
        }
    }
}

void CommandButtons::PushMkFile()
{
    QInputDialog dialog;
    dialog.setWindowTitle("Create File");
    dialog.setLabelText("What do you want to name your file?");
    dialog.setTextValue("untitled file");
    if (dialog.exec())
    {
        QString val = dialog.textValue();
        QString path = ViewPanelTab::path + QDir::separator();
        path+=val;
        if (QDir(path).exists())
        {
            QMessageBox msg;
            msg.setWindowTitle("Error");
            msg.setIcon(QMessageBox::Critical);
            msg.setText("A file or folder with that name already exists.");
            msg.exec();
        }
        else
        {
            QFile file(path);
            if (file.open(QFile::WriteOnly))
            {
                file.close();
            }
        }
    }
}

void CommandButtons::PushMove()
{

}


void CommandButtons::PushMkDir()
{
    QInputDialog dialog;
    dialog.setWindowTitle("Create Folder");
    dialog.setLabelText("What do you want to name your folder?");
    dialog.setTextValue("untitled folder");
    if (dialog.exec())
    {
        QString val = dialog.textValue();
        QString path = ViewPanelTab::path + QDir::separator();
        path+=val;
        if (QDir(path).exists())
        {
            QMessageBox msg;
            msg.setWindowTitle("Error");
            msg.setIcon(QMessageBox::Critical);
            msg.setText("A file or folder with that name already exists.");
            msg.exec();
        }
        else
        {
            QDir().mkdir(path);
        }
    }
}

void CommandButtons::PushDelete()
{
    QMessageBox msg;
    msg.setWindowTitle("Warning!");
    msg.setIcon(QMessageBox::Warning);
    msg.setText("This will permanently delete these file(s) or folder(s).\n"
                "If it is a folder, all its contents will be deleted also.\n"
                "This CANNOT be undone!\n\n"
                "Do you wish to continue?");
    msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    int ret = msg.exec();
    if (ret==QMessageBox::Yes)
    {
        QString path = ViewPanelTab::path + QDir::separator();
        QString to_delete = path + TableView::item.data().toString();
        bool ret;
        if (QFileInfo(to_delete).isDir())
        {
            ret = QDir(to_delete).removeRecursively();
        } else
        {
            ret = QFile(to_delete).remove();
        }
        if (ret==false)
        {
            QMessageBox msg;
            msg.setWindowTitle("Error");
            msg.setIcon(QMessageBox::Critical);
            msg.setText("There was an error deleting this file or folder!");
            msg.setDetailedText("This could mean that the file is read-only, "
                                "or that you do not have the proper permissions "
                                "to access it.");
            msg.exec();
        }
    }

}

void CommandButtons::PushExit()
{
    int answer;
    answer = QMessageBox::information(this, tr("Exit"), "Are you sure you want to exit ? <p><b></b>",QMessageBox::Yes | QMessageBox::No);
    if(answer == QMessageBox::Yes)
        exit(0);
    if(answer == QMessageBox::No)
        return;
}

