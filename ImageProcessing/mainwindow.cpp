#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myvideocapture.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mOpenCV_videoCapture = new myvideocapture(this);
    connect(mOpenCV_videoCapture, &myvideocapture::newPixmapCaptured, this, [&]()
    {
        ui->opencvFrame->setPixmap(mOpenCV_videoCapture->pixmap().scaled(500,500));
    });
}

MainWindow::~MainWindow()
{
    delete ui;
    mOpenCV_videoCapture->terminate();
}


void MainWindow::on_pushButton_clicked()
{
    mOpenCV_videoCapture->start(QThread::HighestPriority);
}
