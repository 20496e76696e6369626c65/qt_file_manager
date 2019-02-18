#include "h/main_panel.h"

#include <QVBoxLayout>

#include "h/two_panel.h"
#include "h/command_buttons.h"

MainPanel::MainPanel(QWidget *parent): QWidget (parent)
{
    QVBoxLayout* layout = new QVBoxLayout;

    layout->addWidget(panel_     = new TwoPanel(this));
    layout->addWidget(buttons_ = new CommandButtons(this));

    panel_->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    panel_->SelectPanel(Panel::LEFT_PANEL);

    QMargins margins(0, 0, 0, 0);

    panel_->setContentsMargins(margins);
    buttons_->setContentsMargins(margins);
    layout->setMargin(0);

    setLayout(layout);

}


