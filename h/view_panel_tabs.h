#ifndef VIEW_PANEL_TABS_H
#define VIEW_PANEL_TABS_H

#include <QTabWidget>

class ViewPanelTab;

class ViewPanelTabs : public QTabWidget
{
    Q_OBJECT
public:
    explicit ViewPanelTabs(QWidget* parent = nullptr);
    void SetDir(const QString&);
public slots:
    void ChangeDirSlot(const QString&);
private:
    ViewPanelTab* first_;
};

#endif // VIEW_PANEL_TABS_H
