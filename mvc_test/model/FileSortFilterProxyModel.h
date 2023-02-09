#ifndef FILESORTFILTERPROXYMODEL_H
#define FILESORTFILTERPROXYMODEL_H

#include <QAbstractItemModel>
#include <QSortFilterProxyModel>

class FileSortFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    explicit FileSortFilterProxyModel(QObject *parent = nullptr);

private:
    virtual bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const;
    virtual bool lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const;
};

#endif // FILESORTFILTERPROXYMODEL_H
