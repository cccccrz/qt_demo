#include "FileSortFilterProxyModel.h"
#include "common/PublicStructs.h"

FileSortFilterProxyModel::FileSortFilterProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{
}

bool FileSortFilterProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    QModelIndex index = sourceModel()->index(source_row, 0, source_parent);
    auto data = index.data(tty::FileRole).value<tty::FileInfo>();

    switch (filterRole()) {
    case tty::FilterByFilename:
        return data.fileName.contains(filterRegExp());
    default:
        break;
    }
    return true;
}

bool FileSortFilterProxyModel::lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const
{
    bool less = false;
    auto ldata = source_left.data(tty::FileRole).value<tty::FileInfo>();
    auto rdata = source_right.data(tty::FileRole).value<tty::FileInfo>();

    switch (sortRole()) {
    case tty::SortByFilename:
        less = QString::localeAwareCompare(ldata.fileName, rdata.fileName) < 0;
        break;
    case tty::SortByFileSize:
        less = ldata.size < rdata.size;
    default:
        break;
    }
    return less;
}
