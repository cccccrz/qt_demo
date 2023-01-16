#ifndef TIPS_H
#define TIPS_H

#include <QWidget>

class QLabel;
class QTimer;
class Tips : public QWidget
{
    Q_OBJECT
public:
    enum TIPS_STATUS {
        S_SUCCESS,
        S_WARN,
        S_ERROR
    };
//    explicit Tips(QWidget *parent = nullptr);
    Tips(const QString& text, QWidget* parent,
         TIPS_STATUS status = S_WARN,int interval = 3000);

    void resize();

protected:
    virtual void playShowAnimation();
    virtual void playCloseAnimation();

private:
    void initForm();
    void setText(const QString& text, TIPS_STATUS status);
    void flash(int interval = 3000);
    void showEvent(QShowEvent* event) override;
    void closeEvent(QCloseEvent* event) override;

    bool played_ = false;
    QLabel* status_;
    QLabel* text_;
    QTimer* timer_;

};

#endif // TIPS_H
