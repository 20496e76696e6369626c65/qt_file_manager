#include "h/table_header_view.h"

#include <QMenu>
#include <QMouseEvent>
#include <QSignalMapper>

TableHeaderView::TableHeaderView(QWidget *parent)
    :QHeaderView (Qt::Horizontal,parent)
{

}

void TableHeaderView::mousePressEvent(QMouseEvent *e)
{

    if (e->button() == Qt::RightButton)
    {
        QMenu menu;
        QSignalMapper mapper;

        for (int col = 0; col < model()->columnCount(); ++col)
        {

            QAction *action = new QAction(&menu);

            action->setText(model()->headerData(col, Qt::Horizontal).toString());
            action->setCheckable(true);
            action->setChecked(!isSectionHidden(col));
            connect(action, SIGNAL(triggered()), &mapper, SLOT(map()));
            mapper.setMapping(action, col);
            menu.addAction(action);
        }

        connect(&mapper, SIGNAL(mapped(int)),
                this, SLOT(ToggleSectionVisibility(int)));

        menu.exec(e->globalPos());
    }

    QHeaderView::mousePressEvent(e);
}

void TableHeaderView::ToggleSectionVisibility(int section)
{
    setSectionHidden(section, !isSectionHidden(section));
}

