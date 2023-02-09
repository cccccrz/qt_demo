#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCore>
#include <QtWidgets>
#include "common/PublicStructs.h"
#include "model/FileListModel.h"
#include "model/FileSortFilterProxyModel.h"
#include "delegate/FileInfoDelegate.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // item代理
    FileInfoDelegate* delegate = new FileInfoDelegate(ui->listView_2);
    ui->listView_2->setItemDelegate(delegate);

    // 排序筛选数据模型
    file_proxy_model_ = new FileSortFilterProxyModel(this);
    ui->listView_2->setModel(file_proxy_model_);
    file_proxy_model_->setDynamicSortFilter(true);
    file_proxy_model_->setFilterRole(tty::FilterByFilename);
    file_proxy_model_->setSortRole(tty::SortByFileSize);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::filter()
{
    // 筛选
    file_proxy_model_->setFilterFixedString(ui->lineEdit->text());
}


void MainWindow::on_pushButton_clicked()
{
    auto GetFileType = [](QMimeType type) -> tty::FileType {
        QString typestr = type.name();
        if (typestr.contains("text")) {
            return tty::kTxt;
        } else if (typestr.contains("image")) {
            return tty::kImg;
        } else if (typestr.contains("pdf")) {
            return tty::kPdf;
        } else if (typestr.contains("exe")) {
            return tty::kExe;
        } else {
            return tty::kUnkown;
        }
    };
    QString dir = QFileDialog::getExistingDirectory(this);
    QDir d(dir);
    QFileInfoList finfo_list = d.entryInfoList();
    QMimeDatabase mdb;
    QList<tty::FileInfo> datas;
    for (const auto& finfo : finfo_list) {
        tty::FileInfo file_data;
        file_data.fileName = finfo.fileName();
        file_data.filePath = finfo.filePath();
        file_data.size = finfo.size();
        file_data.date = finfo.birthTime().toSecsSinceEpoch();
        file_data.type = GetFileType(mdb.mimeTypeForFile(finfo));
        datas.append(file_data);
    }

    FileListModel* model = new FileListModel(datas, this);
    ui->listView->setModel(model);
    file_proxy_model_->setSourceModel(model);
    // 排序
    file_proxy_model_->sort(0, Qt::DescendingOrder);
}

void MainWindow::on_pushButton_3_clicked()
{
    filter();
}


void MainWindow::on_lineEdit_returnPressed()
{
    filter();
}

