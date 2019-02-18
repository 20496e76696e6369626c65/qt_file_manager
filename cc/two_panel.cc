#include "h/two_panel.h"

#include <QVBoxLayout>
#include <QKeyEvent>
#include <QSplitter>
#include <QDir>

#include "h/view_panel.h"
#include "h/view_panel_tab.h"

TwoPanel::TwoPanel(QWidget *parent) : QWidget (parent)
{
    QVBoxLayout* layout = new QVBoxLayout;

    splitter_ = new QSplitter(Qt::Horizontal, this);
    splitter_->setContentsMargins(0, 0, 0, 0);
    splitter_->addWidget(left_ = new ViewPanel(splitter_));
    splitter_->addWidget(right_ = new ViewPanel(splitter_));
    left_->SetDir(QDir::rootPath());
    right_->SetDir(QDir::rootPath());

    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(splitter_);

    setLayout(layout);
}
void TwoPanel::SelectPanel(Panel panel)
{
    slected_panel_ = panel;
    if(panel == Panel::LEFT_PANEL)
    {
        left_->setFocus();
    }
    else
    {
        right_->setFocus();
    }
}


void TwoPanel::ShowDeviceSelector()
{
    ViewPanels()->ShowDeviceSelector();
}

ViewPanel *TwoPanel::ViewPanels()
{
    if(slected_panel_ == Panel::LEFT_PANEL)
    {
        return left_;
    }
    else
    {
        return right_;
    }
}

