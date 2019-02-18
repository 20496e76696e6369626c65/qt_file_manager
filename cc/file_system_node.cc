#include "h/file_system_node.h"

#include <QDateTime>

FileSystemNode::FileSystemNode() : parent_(nullptr)
{

}

FileSystemNode::FileSystemNode(const FileSystemNode* parent, const QString& path) : info_(path), parent_(parent)
{
    is_dir_ = info_.isDir();
    is_valid_ = info_.exists();

    if(is_dir_)
    {
        QDir dir(path);
        QFileInfoList list = dir.entryInfoList(QDir::NoFilter, QDir::DirsFirst);

        files_.resize(list.size());
        qCopy(list.begin(), list.end(), files_.begin());
        children_.fill(nullptr, files_.size());
    }

}

FileSystemNode::~FileSystemNode()
{
    foreach(FileSystemNode* node, children_)
    {
        delete node;
    }
}

FileSystemNode *FileSystemNode::CreateNode(const QString& path)
{
    return new FileSystemNode(nullptr, path);
}

int FileSystemNode::ChildrenCount() const
{
    return files_.size();
}

const FileSystemNode *FileSystemNode::Child(const QString &name) const
{
    int i = 0;
    for (; i < files_.size(); ++i)
    {
        if(files_[i].fileName() == name)
        {
            break;
        }
    }

    if(i > files_.size())
    {
        return nullptr;
    }

    QString path = files_[i].path()+ QDir::separator() + name;

    if(children_[i] == nullptr)
    {
        children_[i] = new FileSystemNode(this, path);
    }

    return children_[i];
}

const FileSystemNode *FileSystemNode::Child(int index) const
{
    if(index >= files_.size() || index<0)
    {
        return nullptr;
    }
    if(children_[index] != nullptr)
    {
        return children_[index];
    }
    QString path = files_[index].path() + QDir::separator() +
            files_[index].fileName();

    if(children_[index] == nullptr)
    {
        children_[index] = new FileSystemNode(this, files_[index].path() +
                                              QDir::separator() + files_[index].fileName());
    }
    return children_[index];
}

int FileSystemNode::Index(const QString& path) const
{
    return files_.indexOf(QFileInfo(path));
}

bool FileSystemNode::IsValide() const
{
    return info_.exists();
}

QString FileSystemNode::Path() const
{
    return info_.filePath();
}

const FileSystemNode *FileSystemNode::Parent() const
{
    return parent_;
}

bool FileSystemNode::IsDir() const
{
    return is_dir_;
}

QString FileSystemNode::FileName() const
{
    return info_.fileName();
}

QString FileSystemNode::FileExt() const
{
    if(!info_.isDir())
    {
        return info_.suffix();
    }
    return "";
}

QString FileSystemNode::FileSize() const
{
    if(info_.isDir())
    {
        return "<DIR>";
    }

    qint64 sz = info_.size();
    QString res;

    if(sz < 1000)
    {
        res = "%1 B";
    }
    else if(sz < 1000000)
    {
        res = "%1 KB";
        sz /= 1000;
    }
    else if(sz < 1000000000)
    {
        res = "%1 MB";
        sz /= 1000000;
    }
    else
    {
        res = "%1 GB";
        sz /= 1000000000;
    }

    return res.arg(sz);
}

QString FileSystemNode::FileDate() const
{
    return info_.lastModified().toString();
}

QString FileSystemNode::FilePermExt() const
{
    QFile::Permissions perm = info_.permissions();
    QString result = "---------";

    if (perm.testFlag(QFileDevice::ReadOwner)) {
        result[0] = 'r';
    }

    if (perm.testFlag(QFileDevice::WriteOwner)) {
        result[1] = 'w';
    }

    if (perm.testFlag(QFileDevice::ExeOwner)) {
        result[2] = 'x';
    }

    if (perm.testFlag(QFileDevice::ReadGroup)) {
        result[3] = 'r';
    }

    if (perm.testFlag(QFileDevice::WriteGroup)) {
        result[4] = 'w';
    }

    if (perm.testFlag(QFileDevice::ExeGroup)) {
        result[5] = 'x';
    }

    if (perm.testFlag(QFileDevice::ReadOther)) {
        result[6] = 'r';
    }

    if (perm.testFlag(QFileDevice::WriteOther)) {
        result[7] = 'w';
    }

    if (perm.testFlag(QFileDevice::ExeOther)) {
        result[8] = 'x';
    }

    return result;
}

void FileSystemNode::SetDir(const QString& path)
{
    QDir dir(path);
    QFileInfoList list = dir.entryInfoList(QDir::NoFilter, QDir::DirsFirst);

    if(list.empty())
    {
        return;

    }
    children_.clear();

    info_.setFile(path);

    QString str = dir.path() + ".";

    list.removeOne(QFileInfo(dir.path() + QDir::separator() + "."));

    if(info_.isRoot())
    {
        list.removeOne(QFileInfo(dir.path() + QDir::separator() + ".."));
    }
    is_valid_ = info_.exists();
    is_dir_    = info_.isDir();

    if(!(is_valid_ && is_dir_))
    {
        info_.setFile(QDir::homePath());
        is_valid_ = true;
    }

    files_.resize(list.size());
    qCopy(list.begin(), list.end(), files_.begin());

    children_.fill(nullptr, files_.size());
}
