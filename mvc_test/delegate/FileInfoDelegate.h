#ifndef FILEINFODELEGATE_H
#define FILEINFODELEGATE_H

#include <QStyledItemDelegate>
#include <QObject>

class FileInfoDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit FileInfoDelegate(QObject *parent = nullptr);

    virtual QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

private:
    void drawIcon(QPainter *painter, const QRect& rect, const QIcon& icon) const;
    void drawText(QPainter* painter, const QRect& rect, const QString& text,
                  const QFont& font, int flags, const QColor& fontColor = Qt::black) const;

    int item_h_ = 50;
    int h_padding_ = 10;
    int v_padding_ = 5;
    int h_spacing_ = 10;
    int v_spacing_ = 10;
    int date_w_ = 30;
};

#endif // FILEINFODELEGATE_H
