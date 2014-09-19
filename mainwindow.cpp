/*
 * (c)2014 James Hudson - www.disconnectionist.com
 * Released under GPL v2.0
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "eventgenerator.h"

#include <QTimer>
#include <QDebug>
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>

#import <opencv2/video/tracking.hpp>

#include <opencv2/highgui/highgui.hpp>

static const int minTimeBetweenActionsMs = 1000;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    if( !mCapture.isOpened() )
        if( !mCapture.open( 0 ) )
            return;

    lastAction.start();
    startTimer(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QDesktopServices::openUrl (QUrl("https://itunes.apple.com/us/app/hands-free-browser-use-gestures/id609652505?mt=8"));
}


void MainWindow::timerEvent(QTimerEvent *event)
{
    cv::Mat image;

    mCapture >> image;

        cv::flip(image, image, 1);

    int halfSquareSize= image.cols / 5;
    int midx = image.cols - halfSquareSize - 8;
    int midy = image.rows / 2;


    cv::Rect myROI(midx-halfSquareSize, midy-halfSquareSize, halfSquareSize*2, halfSquareSize*2);

    cv::Mat cropped = image(myROI);

    cv::rectangle(image, cv::Point2f(midx-halfSquareSize, midy-halfSquareSize),
                  cv::Point2f(midx+halfSquareSize, midy+halfSquareSize), 0xffffffff, 6);

    float scale = 10;
    cv::Mat shrunk(cropped.rows / scale, cropped.cols / scale, cropped.type() );
    cv::resize(cropped, shrunk, shrunk.size(), CV_INTER_NN);

    cv::cvtColor(shrunk, shrunk, CV_BGR2GRAY);


    if (last.rows == shrunk.rows && last.cols == shrunk.cols && last.channels() == shrunk.channels()) {
        cv::Mat flow(shrunk.rows, shrunk.cols, CV_32FC2);

        cv::calcOpticalFlowFarneback( last, shrunk, flow, 0.5, 3, 14, 4, 3, 1.4, 0);

        cv::Mat mean;
        cv::reduce(flow, mean, CV_REDUCE_AVG, 1);

        detectedMovement(mean.at<float>(0,0), mean.at<float>(0,1));

    }

    last = shrunk;

    ui->openCVviewer->showImage( image );
}

void MainWindow::detectedMovement(float xf, float yf)
{
    if (lastAction.elapsed() < minTimeBetweenActionsMs) {
        return;
    }

    int y = xf*2.0f;

    if (y != 0) {
        frame++;
    }
    else {
        frame = 0;
    }

    if (frame < 3) {
        return;
    }

    if (y > 1) {
        EventGenerator::keyPressDownArrow();
        ui->statusBar->showMessage(QString("NEXT detected"), minTimeBetweenActionsMs);
        lastAction.start();
        //qDebug() << "NEXT";
    }
    else if (y < -1) {
        EventGenerator::keyPressUpArrow();
        ui->statusBar->showMessage(QString("PREVIOUS detected"), minTimeBetweenActionsMs);
        lastAction.start();
        //qDebug() << "PREV";
    }

    //ui->statusBar->showMessage(QString("X:%1 Y:%2").arg((int)x).arg((int)y));
}

void MainWindow::on_help_clicked()
{
    QDesktopServices::openUrl (QUrl("https://docs.google.com/document/d/1z9XX1UKDzKAxUIC79hfACiBqaktVHlHnM8lFAJaAndw/edit?usp=sharing"));

}
