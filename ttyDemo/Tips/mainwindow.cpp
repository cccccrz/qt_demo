#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tips.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    new Tips("hello", this, Tips::S_SUCCESS);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    QList<Tips*> tips_list = findChildren<Tips*>();
    for (auto tips : tips_list) {
        tips->resize();
    }
}


void MainWindow::on_pushButton_2_clicked()
{
    // TODO 英文自动换行无效
    new Tips("中文中文", this, Tips::S_WARN);
}

void MainWindow::on_pushButton_3_clicked()
{
    new Tips("中文中文中文中文中文中文中文中文中文中文中文中文中文中文中文中文中文中文中文中文中文中文", this, Tips::S_ERROR);
}

