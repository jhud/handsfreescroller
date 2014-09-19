#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTime>

#include <opencv2/highgui/highgui.hpp>

namespace Ui {
class MainWindow;
}
/*
 * (c)2014 James Hudson - www.disconnectionist.com
 * Released under GPL v2.0
 */

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void on_pushButton_clicked();

    void on_help_clicked();

private:
    Ui::MainWindow *ui;

    cv::VideoCapture mCapture;

    cv::Mat last;
    int frame;

    QTime lastAction;

protected:
    void timerEvent(QTimerEvent *event);

    void detectedMovement(float xf, float yf);
};

#endif // MAINWINDOW_H
