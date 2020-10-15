#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myvideocapture.h"
#include "staticframedifference.h"
#include "gaussianmodelmixutre.h"
#include "adaptivebackgroundlearning.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    mOpenCV_videoCapture->terminate();
}


void MainWindow::on_pushButton_clicked()
{
    staticframedifference sfd;
    sfd.start();
}

void MainWindow::on_pushButton_2_clicked()
{
    gaussianmodelmixutre gmm;
    gmm.start();
}

void MainWindow::on_pushButton_5_clicked()
{
    adaptivebackgroundlearning abl;
    abl.start();
}
void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}
