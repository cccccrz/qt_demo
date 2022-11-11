#ifndef PUBLICSTRUCTS_H
#define PUBLICSTRUCTS_H

#include <QtCore>

enum class FileType {
    kUnkown,
    kTxt,
    kExe,
    kImg,
    kPpt,
    kPdf
};

struct FileInfo
{
    QString fileName;
    QString filePath;
    qint64 size;
    qint64 date;
    FileType type;
};

#endif // PUBLICSTRUCTS_H
