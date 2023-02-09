#include "FileListModel.h"
#include <QDateTime>

FileListModel::FileListModel(QList<tty::FileInfo> list, QObject *parent)
    : QAbstractListModel(parent), fileList_(list)
{
}

int FileListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return fileList_.count();
}

QVariant FileListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() > fileList_.count()) // 越界
        return QVariant();

    switch (role) {
    case tty::FileRole:
        return QVariant::fromValue(fileList_.at(index.row()));
        break;
    case Qt::DisplayRole:
    {
        auto info = fileList_.at(index.row());
        QString display = QString("%1|%2|%3|%4")
                .arg(info.fileName)
                .arg(QDateTime::fromSecsSinceEpoch(info.date).toString(Qt::ISODate))
                .arg(info.size)
                .arg(info.type);
        return display;
    }
    default:
        break;
    }
    return QVariant();
}

bool FileListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        tty::FileInfo index_data = index.data(role).value<tty::FileInfo>();
        switch (role) {
        case tty::FileRole:
            fileList_.replace(index.row(), index_data);
            break;
        default: // unsupport
            return false;
        }
        emit dataChanged(index, index, {role});
        return true;
    }
    return false;
}

Qt::ItemFlags FileListModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable; // FIXME: Implement me!
}

bool FileListModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    endInsertRows();
    return true;
}

bool FileListModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if (rowCount() < row + count) return false;

    beginRemoveRows(parent, row, row + count - 1);
    // 从row行开始删除count个
    for (int i=0; i<count; ++i) {
        fileList_.removeAt(row);
    }
    endRemoveRows();
    return true;
}
