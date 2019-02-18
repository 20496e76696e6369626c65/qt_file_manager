#include "h/file_system.h"

FileSystem::FileSystem()
{
}

const FileSystemNode *FileSystem::DefaultNode() const
{
    return &root_;
}

const FileSystemNode *FileSystem::CreateNode(const QString&) const
{
    return DefaultNode();
}

const FileSystemNode *FileSystem::RootNode() const
{
    return &root_;
}

void FileSystem::SetDir(const QString& path)
{
    root_.SetDir(path);
}
