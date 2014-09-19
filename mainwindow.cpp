#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "eventgenerator.h"

#include <QTimer>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// see here for mappings: http://web.archive.org/web/20100501161453/http://www.classicteck.com/rbarticles/mackeyboard.php
void MainWindow::on_pushButton_clicked()
{
    QTimer *timer = new QTimer(this);
    timer->setSingleShot(true);

    connect(timer, &QTimer::timeout, [=]() {
    EventGenerator::keyPressDownArrow();
    QMessageBox(QMessageBox::Information, "Event generated", "Just generated a down arrow press.").exec();
      timer->deleteLater();
    } );

    timer->start(3000);

}
