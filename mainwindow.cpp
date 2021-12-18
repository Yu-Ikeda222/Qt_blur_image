#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QObject>
#include <QThread>
#include <iostream>
#include <thread>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    process_image = new ProcessImage;

    process_image_thread = new QThread;
    process_image->moveToThread(process_image_thread);
    connect(this, SIGNAL(pass_image_data(data)), process_image, SLOT(get_image_data(data)));
    connect(process_image, SIGNAL(image_process(int)), this, SLOT(on_image_process(int)));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_openButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open"), "", tr("Images (*.png *.xpm *.jpg)"),0,QFileDialog::DontUseNativeDialog);
    if (!fileName.isEmpty()) {
        QFile file(fileName);
    }

    ui->pngNameLabel->setText(fileName);

    QPixmap image;
    int w = ui->inputImageLabel->width();
    int h = ui->inputImageLabel->height();

    image.load(fileName);
    ui->inputImageLabel->setPixmap(image.scaled(w,h,Qt::KeepAspectRatio));
}


void MainWindow::on_blurButton_clicked()
{
    if (ui->spinBox->value() == 0) {
        ui->blurButton->setText("error! please set value");
    }
    else {
        QString fileName = ui->pngNameLabel->text();
        QImage srcImage = QImage(fileName);
        QImage image = srcImage.copy();
        int size = ui->spinBox->value();
        process_image_data.dst = &image;
        process_image_data.size = size;

        emit pass_image_data(process_image_data);
        process_image_thread->start();


        //        process_image_thread->wait();
        if(progress_status == 100) {
            int w = ui->inputImageLabel->width();
            int h = ui->inputImageLabel->height();
            ui->outputImageLabel->setPixmap(QPixmap::fromImage(image).scaled(w,h,Qt::KeepAspectRatio));
        }
    }
}

void MainWindow::on_image_process(int num)
{
    progress_status = num;
    ui->progressBar->setValue(progress_status);
}

//void MainWindow::do_pass_image_data(data data, MainWindow main_window) {
//    emit main_window.pass_image_data(data);
//}
