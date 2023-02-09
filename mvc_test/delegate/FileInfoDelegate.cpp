#include "FileInfoDelegate.h"
#include <QPainter>
#include <QFileIconProvider>
#include <common/PublicStructs.h>

FileInfoDelegate::FileInfoDelegate(QObject *parent)
    : QStyledItemDelegate{parent}
{

}

QSize FileInfoDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index)
    return QSize(option.rect.width(), item_h_);
}

void FileInfoDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (!index.isValid()) return QStyledItemDelegate::paint(painter, option, index);

    auto finfo = index.data(tty::FileRole).value<tty::FileInfo>();

    // 背景
    if (option.state & QStyle::State_Selected)
        painter->fillRect(option.rect, option.palette.highlight());
    else if (option.state & QStyle::State_MouseOver)
        painter->fillRect(option.rect, option.palette.light());
    else
        painter->fillRect(option.rect, option.palette.base());

    // 图标
    QFileIconProvider iconProvider;
    QIcon ficon = iconProvider.icon(QFileInfo(finfo.filePath));
    QRect ficonRect = option.rect;
    ficonRect.setX(ficonRect.x() + h_padding_);
    ficonRect.setWidth((ficonRect.height()/2-v_padding_) * 2);
    ficonRect.setY(ficonRect.y()+v_padding_);
    ficonRect.setHeight(ficonRect.width());
    this->drawIcon(painter, ficonRect, ficon);

    // 日期
    int date_w = date_w_;
    QString dateStr;
    QDateTime fdate = QDateTime::fromSecsSinceEpoch(finfo.date);
    QDateTime curDate = QDateTime::currentDateTime();
    // today
    if (fdate.daysTo(curDate) > 0) {
        dateStr = fdate.toString("hh:mm");
    } else if (fdate.toString("yyyy") == curDate.toString("yyyy")) {
        dateStr = fdate.toString("mm/dd");
    } else {
        date_w += 20;
        dateStr = fdate.toString("yy/mm/dd");
    }
    QRect dateRect = option.rect;
    dateRect.setX(dateRect.width() - h_padding_ - date_w);
    dateRect.setWidth(date_w);
    dateRect.setY(dateRect.y() + v_padding_);
    dateRect.setHeight(ficonRect.height()/2);
    QFont dateFont = option.font;
    dateFont.setPixelSize(10);
    this->drawText(painter, dateRect, dateStr, dateFont, Qt::AlignRight | Qt::AlignBottom, QColor(169, 181, 204));

    // 文件名
    QRect nameRect = option.rect;
    nameRect.setX(ficonRect.x() + ficonRect.width() + h_spacing_);
    nameRect.setWidth(dateRect.x() - ficonRect.x() - ficonRect.width() - 2 * h_spacing_);
    nameRect.setY(nameRect.y() + v_padding_);
    nameRect.setHeight(ficonRect.height()/2);
    this->drawText(painter, nameRect, finfo.fileName, option.font, Qt::AlignLeft | Qt::AlignBottom);
}

void FileInfoDelegate::drawIcon(QPainter *painter, const QRect &rect, const QIcon &icon) const
{
    painter->save();
    painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::transparent);
    icon.paint(painter, rect, Qt::AlignCenter, QIcon::Disabled, QIcon::On);
    painter->restore();
}

void FileInfoDelegate::drawText(QPainter *painter, const QRect &rect, const QString &text, const QFont &font, int flags, const QColor &fontColor) const
{
    painter->save();
    painter->setRenderHints(QPainter::TextAntialiasing);
    painter->setFont(font);
    painter->setPen(fontColor);
    painter->setBrush(Qt::NoBrush);
    painter->drawText(rect, flags, text);
    painter->restore();
}
