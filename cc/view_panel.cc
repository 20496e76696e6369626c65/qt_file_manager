#include "h/view_panel.h"

#include "h/view_panel_tab.h"
#include "h/view_panel_top.h"
#include "h/view_panel_tabs.h"
#include <QVBoxLayout>

ViewPanel::ViewPanel(QWidget *parent) : QWidget (parent)
{
    QVBoxLayout* layout = new QVBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(top_ = new ViewPanelTop(this, this));
    layout->addWidget(tabs_ = new ViewPanelTabs);

    top_->setFocusPolicy(Qt::ClickFocus);

    top_->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);
    tabs_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    connect(top_,  SIGNAL(SelectDeviceSignal(QString)), this, SLOT(SelectDeviceSlot(QString)));

    setLayout(layout);
}

void ViewPanel::SetDir(const QString& path)
{
    tabs_->SetDir(path);
    top_->SetDir(path);

}

void ViewPanel::ShowDeviceSelector()
{
    top_->ShowDeviceSelector();
}

void ViewPanel::SelectDeviceSlot(QString val)
{
    tabs_->SetDir(val);
}
