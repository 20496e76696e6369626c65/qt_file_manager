#ifndef MAIN_PANEL_H
#define MAIN_PANEL_H

#include <QWidget>

class TwoPanel;
class CommandButtons;

class MainPanel : public QWidget
{
    Q_OBJECT
public:

    MainPanel(QWidget* parent = nullptr);

private:
    TwoPanel* panel_;
    CommandButtons* buttons_;
};

#endif // MAIN_PANEL_H
