#ifndef FILE_SYSTEM_NODE_H
#define FILE_SYSTEM_NODE_H


#include <QString>
#include <QVector>
#include <QFileInfo>
#include <QDir>


class FileSystemNode
{
public:

    FileSystemNode();
    FileSystemNode(const FileSystemNode*, const QString&);
    ~FileSystemNode();
    static FileSystemNode* CreateNode(const QString&);
    int ChildrenCount() const;
    const FileSystemNode* Child(const QString&) const;
    const FileSystemNode* Child(int) const;
    int Index(const QString&) const;
    bool IsValide() const;
    QString Path() const;
    const FileSystemNode* Parent() const;
    bool IsDir() const;

    QString FileName() const;
    QString FileExt() const;
    QString FileSize() const;
    QString FileDate() const;
    QString FilePermExt() const;

    void SetDir(const QString&);

private:
    mutable QVector<FileSystemNode*> children_;
    QVector<QFileInfo>               files_;
    bool                             is_dir_;
    bool                             is_valid_;
    QFileInfo                        info_;
    QDir                             dir_;
    const FileSystemNode*            parent_;
};


#endif // FILE_SYSTEM_NODE_H
