#ifndef VIEW_PANEL_TAB_H
#define VIEW_PANEL_TAB_H

#include <QWidget>

class TableView;
class FileSystemModel;
class QAbstractItemView;

class ViewPanelTab : public QWidget
{
    Q_OBJECT
public:
    explicit ViewPanelTab(QWidget* parent = nullptr);

    static QString path;

    void ChangeDir(const QString&);
    void OpenItem(int);
    QString Path();
    void CdUp();
signals:
    void ChangeDirSignal(const QString&);
private:
    TableView* table_;
    QAbstractItemView* view_;
    FileSystemModel* model_;
};

#endif // VIEW_PANEL_TAB_H
