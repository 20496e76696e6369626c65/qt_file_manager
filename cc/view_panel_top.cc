#include "h/view_panel_top.h"

#include <QHBoxLayout>
#include <QDir>
#include <QComboBox>
#include <QLabel>
#include <QToolButton>

ViewPanelTop::ViewPanelTop(QWidget *parent, QWidget *main_panel) : QWidget (parent), main_panel_(main_panel)
{
    QHBoxLayout* layout = new QHBoxLayout;

    layout->addWidget(device_  = new QComboBox);
    layout->addWidget(info_    = new QLabel("[_none_]"));
    layout->addWidget(root_    = new QToolButton);

    device_->setContentsMargins(0, 0, 10, 0);
    root_->setContentsMargins(0, 0, 0, 0);

    device_->setMinimumWidth(100);

    device_->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    root_->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);

    QSize btn_size(20,20);

    root_->resize(btn_size);
    root_->setText("root");

    layout->setMargin(0);

    QFileInfoList list = QDir::drives();

    foreach(const QFileInfo& device, list)
        device_->addItem(device.filePath());

    connect(device_, SIGNAL(currentIndexChanged(QString)),   this, SLOT(SelectDeviceSlot(QString)));
    connect(root_,   SIGNAL(pressed()),                      this, SLOT(GoRootSlot()));

    setLayout(layout);
}

void ViewPanelTop::SetDir(const QString& path)
{
    QDir dir(path);
    while (dir.cdUp())
    {

    }
    int i = device_->findText(dir.path());
    if(i >= 0)
    {
        device_->setCurrentIndex(i);
    }
}

void ViewPanelTop::ShowDeviceSelector()
{
    device_->showPopup();
}

void ViewPanelTop::SelectDeviceSlot(QString val)
{
    emit SelectDeviceSignal(val);
}

void ViewPanelTop::GoRootSlot()
{
    emit SelectDeviceSignal(QDir::rootPath());
}


