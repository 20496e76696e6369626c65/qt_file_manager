#ifndef TABLE_VIEW_H
#define TABLE_VIEW_H

#include <QTableView>

class TableHeaderView;

class TableView : public QTableView
{
public:
    explicit TableView(QWidget* parent = nullptr);

    static QModelIndex item;

    void    mouseDoubleClickEvent(QMouseEvent*);
    void    resizeEvent(QResizeEvent*);
protected:

    void    mousePressEvent(QMouseEvent*);
private:

    void    OpenItem(const QModelIndex&);
    void    CdUp();

private:
    TableHeaderView*    headers_;
};

#endif // TABLE_VIEW_H
