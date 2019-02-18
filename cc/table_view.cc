#include "h/table_view.h"
#include "h/view_panel_tab.h"
#include "h/table_header_view.h"

#include <QResizeEvent>
#include <QSortFilterProxyModel>

QModelIndex TableView::item;

TableView::TableView(QWidget *parent): QTableView (parent)
{
    setShowGrid(false);
    verticalHeader()->hide();
    horizontalHeader()->hide();

    setAlternatingRowColors(true);
    setWordWrap(false);

    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setHorizontalHeader(headers_ = new TableHeaderView(this));

    setSortingEnabled(true);
    horizontalHeader()->setSectionsClickable(true);
    horizontalHeader()->setSortIndicatorShown(true);
}

void TableView::mouseDoubleClickEvent(QMouseEvent *event)
{
    QTableView::mouseDoubleClickEvent(event);
    OpenItem(indexAt(event->pos()));
}

void TableView::resizeEvent(QResizeEvent *event)
{
    QTableView::resizeEvent(event);

    int w = 0;
    for(int i = 1; i < model()->columnCount(); ++i)
    {
        w += columnWidth(i);
    }
    setColumnWidth(0, width() - w - 20);
}

void TableView::OpenItem(const QModelIndex &index)
{
    QWidget* w = parentWidget();
    if(w == nullptr)
    {
        return;
    }

    ViewPanelTab* vp = dynamic_cast<ViewPanelTab*>(w);
    if(vp == nullptr)
    {
        return;
    }
    setCurrentIndex(model()->index(0, 0, rootIndex()));

    model()->removeRows(0, model()->rowCount());
    vp->OpenItem(index.row());
}

void TableView::CdUp()
{
    QWidget* w = parentWidget();
    if(w == nullptr)
    {
        return;
    }

    ViewPanelTab* vp = dynamic_cast<ViewPanelTab*>(w);
    if(vp == nullptr)
    {
        return;
    }
    setCurrentIndex(model()->index(0, 0, rootIndex()));

    model()->removeRows(0, model()->rowCount());
    vp->CdUp();
}

void TableView::mousePressEvent(QMouseEvent *event)
{
    QTableView::mousePressEvent(event);

    if(event->button() == Qt::LeftButton )
    {
        QModelIndex show = indexAt(event->pos());
        item = show;
    }
}
