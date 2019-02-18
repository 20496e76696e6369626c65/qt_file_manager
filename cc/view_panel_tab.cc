#include "h/view_panel_tab.h"
#include "h/file_system_model.h"
#include "h/table_view.h"

#include <QVBoxLayout>
#include <QDir>

QString ViewPanelTab::path;

ViewPanelTab::ViewPanelTab(QWidget *parent): QWidget (parent)
{
    QVBoxLayout* layout = new QVBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(view_ = table_ = new TableView);

    model_ = new FileSystemModel;
    model_->SetDir(QDir::rootPath());

    view_->setModel(model_);

    view_->setRootIndex(model_->index(0,0,QModelIndex()));
    setFocusProxy(view_);
    setLayout(layout);
}


void ViewPanelTab::ChangeDir(const QString &dir)
{
    path = "";
    path = dir;
    model_->SetDir(dir);
}

void ViewPanelTab::OpenItem(int row)
{
    model_->OpenRow(row);
    path = model_->Path();
    emit ChangeDirSignal(model_->Path());
}

QString ViewPanelTab::Path()
{
    return model_->Path();
}

void ViewPanelTab::CdUp()
{
    model_->CdUp();
}

