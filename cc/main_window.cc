#include "h/main_window.h"

#include "h/main_panel.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow (parent)
{
    panel_ = new MainPanel(this);
    setCentralWidget(panel_);
    panel_->setContentsMargins(0, 0, 0, 0);
    setContentsMargins(0, 0, 0, 0);

    resize(800, 600);
    showMaximized();
}

MainWindow::~MainWindow()
{
}
