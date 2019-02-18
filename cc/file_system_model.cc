#include "h/file_system_model.h"
#include <QDir>
#include <QFileInfo>


QVector<QString> FileSystemModel::all_columns_;
bool FileSystemModel::created_ = false;

FileSystemModel::FileSystemModel(QObject *parent): QAbstractItemModel (parent)
{

    columns_.reserve(HeaderInfo::COUNT);
    columns_.push_back(HeaderInfo::NAME);
    columns_.push_back(HeaderInfo::EXT);
    columns_.push_back(HeaderInfo::SIZE);
    columns_.push_back(HeaderInfo::DATE);
    columns_.push_back(HeaderInfo::RWX);

    if(!created_)
    {
        created_ = true;
        all_columns_.push_back("Name");
        all_columns_.push_back("Ext");
        all_columns_.push_back("Size");
        all_columns_.push_back("Date");
        all_columns_.push_back("rwx");
    }
}

QModelIndex FileSystemModel::index(int row, int column, const QModelIndex &parent) const
{
    if(!parent.isValid())
    {
        return createIndex(0, 0, const_cast<FileSystemNode*>(file_system_.DefaultNode()));
    }

    if(row < 0 || column < 0 || row >= rowCount(parent) || column >= columnCount(parent))
    {
        return QModelIndex();
    }
    const FileSystemNode* parent_node = Index2Node(parent);

    const FileSystemNode* child_node = parent_node->Child(row);
    Q_ASSERT(child_node);

    if(child_node == nullptr)
    {
        child_node = file_system_.DefaultNode();
    }
    return createIndex(row, column, const_cast<FileSystemNode*>(child_node));
}

int FileSystemModel::rowCount(const QModelIndex &parent) const
{
    if(parent.column() > 0)
    {
        return 0;
    }

    return Index2Node(parent)->ChildrenCount();
}

int FileSystemModel::columnCount(const QModelIndex &parent) const
{
    if(parent.column() > 0)
    {
        return 0;
    }
    return columns_.size();
}

QModelIndex FileSystemModel::parent(const QModelIndex &child) const
{
    if(!child.isValid())
        return QModelIndex();

    const FileSystemNode* node = Index2Node(child);
    if(node == nullptr || !node->IsValide())
    {
        return QModelIndex();
    }
    const FileSystemNode* parent = node->Parent();
    if(parent == nullptr || !parent->IsValide())
    {
        return QModelIndex();
    }
    int row = 0;
    const FileSystemNode* grand_parent = parent->Parent();
    if(grand_parent != nullptr && grand_parent->IsValide())
    {
        row = grand_parent->Index(parent->Path());
    }
    if(row == -1)
    {
        return QModelIndex();
    }
    return createIndex(row, 0, const_cast<FileSystemNode*>(node->Parent()));
}

QVariant FileSystemModel::data(const QModelIndex &index, int role =  Qt::DisplayRole ) const
{
    if(index.column() > columns_.size())
    {
        return QVariant::Invalid;
    }
    switch (role)
    {
    case Qt::DisplayRole:
        return DisplayRole(index);
    case Qt::DecorationRole:
        return DecorationRole(index);
    default:
        return QVariant::Invalid;
    }
}



QVariant FileSystemModel::headerData(int selection, Qt::Orientation orient, int role) const
{
    if(role != Qt::DisplayRole)
    {
        return QVariant::Invalid;
    }
    if(orient == Qt::Vertical)
    {
        return "";
    }
    if(columns_.size() < selection)
    {
        return QVariant::Invalid;
    }
    return all_columns_[columns_[selection]];
}



QModelIndex FileSystemModel::SetDir(const QString& path)
{
    emit layoutAboutToBeChanged();
    file_system_.SetDir(path);
    const FileSystemNode* node      = file_system_.DefaultNode();
    const FileSystemNode* parent_node = node->Parent();

    int row = 0;

    if(parent_node)
    {
        row = parent_node->Index(node->Path());
    }

    emit layoutChanged();

    return createIndex(row, 0, const_cast<FileSystemNode*>(node));
}

void FileSystemModel::OpenRow(int row)
{
    const FileSystemNode* root = file_system_.DefaultNode();
    if(root == nullptr)
    {
        return;
    }
    const FileSystemNode* node = root->Child(row);
    if(node == nullptr)
    {
        return;
    }
    if(!node->IsDir())
    {

    }
    QString name = node->FileName();
    QString path = node->Path();

    if(name=="..")
    {
        QDir dir(path);
        path = dir.absolutePath();
    }
    SetDir(path);
}

void FileSystemModel::CdUp()
{
    const FileSystemNode* root = file_system_.DefaultNode();
    if(root == nullptr)
    {
        return;
    }
    const FileSystemNode* node = root->Child("..");
    if(node == nullptr)
    {
        return;
    }
    if(!node->IsDir())
    {
        return;
    }
    SetDir(QDir(node->Path()).absolutePath());
}

QString FileSystemModel::Path() const
{
    return file_system_.RootNode()->Path();
}

QVector<HeaderInfo> FileSystemModel::Headers() const
{
    return columns_;
}

const FileSystemNode *FileSystemModel::Index2Node(const QModelIndex &index) const
{
    if(index.isValid())
    {
        return static_cast<const FileSystemNode*>(index.internalPointer());
    }
    return file_system_.DefaultNode();
}

QVariant FileSystemModel::DisplayRole(const QModelIndex &index) const
{
    const FileSystemNode* node = Index2Node(index);

    if(node == nullptr || !node->IsValide())
        return QVariant::Invalid;

    switch(columns_[index.column()])
    {
    case HeaderInfo::NAME:
        return node->FileName();

    case HeaderInfo::EXT:
        return node->FileExt();

    case HeaderInfo::SIZE:
        return node->FileSize();

    case HeaderInfo::DATE:
        return node->FileDate();

    case HeaderInfo::RWX:
        return node->FilePermExt();

    case HeaderInfo::COUNT:
    default:
        return QVariant::Invalid;
    }
}

QVariant FileSystemModel::DecorationRole(const QModelIndex &index) const
{

    if(columns_.size() < index.column() || columns_.size() < 0 || columns_[index.column()] != HeaderInfo::NAME)
        return QVariant::Invalid;

    const FileSystemNode* node = Index2Node(index);
    QString n = QVariant(index).toString();
    QFileInfo info(n);

    if(node == nullptr || !node->IsValide())
        return QVariant::Invalid;

    if(node->IsDir())
        return icon_provider_.icon(QFileIconProvider::Folder);

    return icon_provider_.icon(QFileIconProvider::File);
}


