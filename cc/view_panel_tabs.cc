#include "h/view_panel_tabs.h"
#include "h/view_panel_tab.h"
#include <QKeyEvent>
#include <QDir>
#include <QDebug>


ViewPanelTabs::ViewPanelTabs(QWidget *parent) : QTabWidget (parent)
{
    addTab(first_ = new ViewPanelTab,"33333");

    QWidget* tmp = currentWidget();
    if(tmp != nullptr)
    {
        setFocusProxy(tmp);
    }

    connect(first_,  SIGNAL(ChangeDirSignal(const QString&)),this, SLOT(ChangeDirSlot(const QString&)));

    ChangeDirSlot(first_->Path());
}

void ViewPanelTabs::SetDir(const QString &dir)
{
    QWidget* tmp = currentWidget();
    if(tmp == nullptr)
    {
        return;
    }
    ViewPanelTab* vp = dynamic_cast<ViewPanelTab*>(tmp);
    if(vp == nullptr)
    {
        return;
    }
    vp->ChangeDir(dir);
    ChangeDirSlot(dir);
}


void ViewPanelTabs::ChangeDirSlot(const QString& path1)
{
    setTabText(currentIndex(), path1);
}

