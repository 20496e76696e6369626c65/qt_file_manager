#ifndef VIEW_PANEL_TOP_H
#define VIEW_PANEL_TOP_H

#include <QWidget>

class QComboBox;
class QLabel;
class QToolButton;

class ViewPanelTop : public QWidget
{
    Q_OBJECT
public:
    explicit ViewPanelTop(QWidget*, QWidget*);

    void SetDir(const QString&);
    void ShowDeviceSelector();
signals:
    void SelectDeviceSignal(QString);
public slots:
    void SelectDeviceSlot(QString);
    void GoRootSlot();
private:
    QComboBox*   device_;
    QLabel*      info_;
    QToolButton* root_;
    QWidget*     main_panel_;
};

#endif // VIEW_PANEL_TOP_H
