#ifndef VIEW_PANEL_H
#define VIEW_PANEL_H

#include <QWidget>

class ViewPanelTop;
class ViewPanelTabs;

class ViewPanel : public QWidget
{
    Q_OBJECT
public:
    explicit ViewPanel(QWidget* parent = nullptr);

    void SetDir(const QString&);
    void ShowDeviceSelector();
public slots:
    void SelectDeviceSlot(QString);
private:
    ViewPanelTop* top_;
    ViewPanelTabs* tabs_;
};



#endif // VIEW_PANEL_H
