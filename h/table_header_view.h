#ifndef TABLEHEADERVIEW_H
#define TABLEHEADERVIEW_H

#include <QHeaderView>

class TableHeaderView: public QHeaderView
{
    Q_OBJECT
public:
    TableHeaderView(QWidget* parent = nullptr);

protected slots:

    void  ToggleSectionVisibility(int);

protected:

    void  mousePressEvent(QMouseEvent*);

};

#endif // TABLEHEADERVIEW_H
