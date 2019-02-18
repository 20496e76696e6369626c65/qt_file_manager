#ifndef FILE_SYSTEM_MODEL_H
#define FILE_SYSTEM_MODEL_H

#include <QAbstractItemModel>
#include <QFileIconProvider>

#include "general.h"
#include "file_system.h"

class FileSystemModel : public QAbstractItemModel
{
    Q_OBJECT
public:

    explicit FileSystemModel(QObject* parent = nullptr);

    QModelIndex index(int,int,const QModelIndex&) const;
    int rowCount(const QModelIndex&) const;
    int columnCount(const QModelIndex&) const;
    QModelIndex parent(const QModelIndex&) const;
    QVariant data(const QModelIndex&, int) const;
    QVariant headerData(int, Qt::Orientation, int) const;

    QModelIndex SetDir(const QString&);
    void OpenRow(int);
    void CdUp();
    QString Path() const;
    QVector<HeaderInfo> Headers() const;

private:

    const FileSystemNode* Index2Node(const QModelIndex&) const;
    QVariant DisplayRole(const QModelIndex&) const;
    QVariant DecorationRole(const QModelIndex&) const;

private:
    FileSystem file_system_;
    QVector<enum HeaderInfo> columns_;
    QFileIconProvider icon_provider_;

    static QVector<QString> all_columns_;
    static bool created_;
};

#endif // FILE_SYSTEM_MODEL_H
