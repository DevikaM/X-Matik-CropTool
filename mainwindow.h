#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QMessageBox>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include "opencv2/opencv.hpp"

const std::string DIR_STRUCT [3] = {"pos","neg","raw"};
const QString CROPPED_DIR = "cropped";

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void RecursiveCopy(const QString& Source, const QString& Target);


private slots:
    void on_GoButton_clicked();
    void FadeOutLabel();
    void on_ClearButton_clicked();

private:
    Ui::MainWindow *ui;
    QString RootPath;
    QString TargetPath;
    QDir RootDir;
    QDir TargetDir;
    int TopCrop;
    int BottomCrop;

    bool IsValid();
    QString Combine(const QString& First, const QString& Second);
    void Success();


};

#endif // MAINWINDOW_H
