#include "tips.h"
#include <QtCore>
#include <QtWidgets>

//Tips::Tips(QWidget *parent)
//    : QWidget{parent}
//{
//
//}

Tips::Tips(const QString &text, QWidget *parent, TIPS_STATUS status, int interval)
    : QWidget{parent}
{
    initForm();
    setText(text, status);
    flash(interval);
}

void Tips::resize()
{
    QFontMetrics fm(this->font());
    int text_w = fm.horizontalAdvance(text_->text());
    int max_w = parentWidget()->width() / 2 - 50 - status_->width();
    if (text_w > max_w) {
        text_w = max_w;
    }
    text_->setFixedWidth(text_w);
    adjustSize();
    move(parentWidget()->width() / 2 - width() / 2, 0);
    update();
}

void Tips::playShowAnimation()
{
    if (played_) return;

    QPropertyAnimation* showAnimation = new QPropertyAnimation(this, "pos");
    showAnimation->setDuration(200);
    int pos_x = this->x();
    showAnimation->setStartValue(QPoint(pos_x, -height()));
    showAnimation->setEndValue(QPoint(pos_x, 30));
    showAnimation->setEasingCurve(QEasingCurve::InOutQuad);
    connect(showAnimation, &QAbstractAnimation::finished, this, [this](){
        played_ = false;
    });
    showAnimation->start(QAbstractAnimation::DeleteWhenStopped);
    played_ = true;
}

void Tips::playCloseAnimation()
{
    if (played_) return;

    QPropertyAnimation* closeAnimation = new QPropertyAnimation(this, "pos");
    closeAnimation->setDuration(200);
    int pos_x = this->x();
    closeAnimation->setEndValue(QPoint(pos_x, -height()));
    closeAnimation->setStartValue(QPoint(pos_x, 30));
    closeAnimation->setEasingCurve(QEasingCurve::InOutQuad);
    connect(closeAnimation, &QAbstractAnimation::finished, this, &Tips::close);
    closeAnimation->start(QAbstractAnimation::DeleteWhenStopped);
    played_ = true;
}

void Tips::initForm()
{
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_DeleteOnClose);

    QWidget* p_main = new QWidget(this);
    p_main->setObjectName("widgetMain");

    QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect->setOffset(0, 0);
    shadowEffect->setBlurRadius(10);
    p_main->setGraphicsEffect(shadowEffect);

    QVBoxLayout* main_layout = new QVBoxLayout(this);
    main_layout->addWidget(p_main);
    main_layout->setSpacing(0);
    main_layout->setMargin(10);

    status_ = new QLabel(p_main);
    status_->setScaledContents(true);
    status_->setFixedSize(18, 18);
    status_->setFrameShape(QFrame::NoFrame);

    text_ = new QLabel(p_main);
    text_->setWordWrap(true);
    text_->setFrameShape(QFrame::NoFrame);

    QHBoxLayout* text_layout = new QHBoxLayout(p_main);
    text_layout->setMargin(10);
    text_layout->setSpacing(10);
    text_layout->addWidget(status_, 0, Qt::AlignVCenter);
    text_layout->addWidget(text_, 1, Qt::AlignVCenter);

    setStyleSheet("#widgetMain{border:1px solid #BBBBBB; background:white; border-radius: 4px;}");

    timer_ = new QTimer(this);
    timer_->setSingleShot(true);
    connect(timer_, &QTimer::timeout, this, &Tips::close);
}

void Tips::setText(const QString &text, TIPS_STATUS status)
{
    switch (status) {
    case S_SUCCESS:
        status_->setPixmap(qApp->style()->standardPixmap(QStyle::SP_MessageBoxInformation));
        break;
    case S_WARN:
        status_->setPixmap(qApp->style()->standardPixmap(QStyle::SP_MessageBoxWarning));
        break;
    case S_ERROR:
        status_->setPixmap(qApp->style()->standardPixmap(QStyle::SP_MessageBoxCritical));
        break;
    default:
        status_->setPixmap(qApp->style()->standardPixmap(QStyle::SP_MessageBoxCritical));
        break;
    }
    text_->setText(text);
    this->resize();
}

void Tips::flash(int interval)
{
    show();
    timer_->start(interval);
}

void Tips::showEvent(QShowEvent *event)
{
    playShowAnimation();
    event->accept();
}

void Tips::closeEvent(QCloseEvent *event)
{
    if (!played_) {
        playCloseAnimation();
        event->ignore();
    } else {
        event->accept();
        played_ = false;
    }
}
