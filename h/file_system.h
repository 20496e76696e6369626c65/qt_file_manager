#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

#include "file_system_node.h"

class FileSystem
{
public:

    FileSystem();   
    const FileSystemNode* DefaultNode() const;
    const FileSystemNode* CreateNode(const QString&) const;
    const FileSystemNode* RootNode() const;
    void SetDir(const QString&);

private:
    FileSystemNode root_;
};

#endif // FILE_SYSTEM_H
