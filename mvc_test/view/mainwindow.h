#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class FileSortFilterProxyModel;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void filter();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_lineEdit_returnPressed();

private:
    Ui::MainWindow *ui;
    FileSortFilterProxyModel* file_proxy_model_;
};
#endif // MAINWINDOW_H
