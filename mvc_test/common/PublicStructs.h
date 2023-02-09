#ifndef PUBLICSTRUCTS_H
#define PUBLICSTRUCTS_H

#include <QtCore>

namespace tty {
    enum FileType {
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

    enum Role {
        // data role
        FileRole = Qt::UserRole+1,

        // 排序role
        NoSort,
        SortByFilename,
        SortByFileSize,

        // 筛选role
        NoFilter,
        FilterByFilename,
    };
}
Q_DECLARE_METATYPE(tty::FileInfo)
Q_DECLARE_METATYPE(tty::Role)

#endif // PUBLICSTRUCTS_H
