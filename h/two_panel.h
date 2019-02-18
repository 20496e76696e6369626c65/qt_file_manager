#ifndef TWO_PANEL_H
#define TWO_PANEL_H

#include <QWidget>
#include "general.h"

class QSplitter;
class ViewPanel;

class TwoPanel : public QWidget
{
    Q_OBJECT
public:

    explicit TwoPanel(QWidget* parent = nullptr);
    void SelectPanel(Panel);
private:

    void ShowDeviceSelector();
    ViewPanel* ViewPanels();

private:
    QSplitter* splitter_;
    ViewPanel* left_;
    ViewPanel* right_;
    Panel slected_panel_;
};

#endif // TWO_PANEL_H
