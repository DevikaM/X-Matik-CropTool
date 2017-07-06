#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->SuccessLabel->hide();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_GoButton_clicked()
{
    QString err = "Crop Values Not Valid";
    try{
        RootPath = ui->RootPathTextField->text();
        RootDir = QDir(RootPath);
        TopCrop = std::stoi(ui->TopCropTextField->text().toStdString());
        BottomCrop = std::stoi(ui->BottomCropTextField->text().toStdString());
        if(RootDir.exists() && IsValid())
        {
            TargetPath = Combine(RootPath,CROPPED_DIR);
            TargetDir = QDir(TargetPath);
            RecursiveCopy(RootPath, TargetPath);
            Success();
        }
        else
            err = "Path Not Valid";
    }
    catch(std::exception ex)
    {
        QMessageBox messageBox;
                    messageBox.critical(0,"Error",err);
                    messageBox.setFixedSize(500,200);
        return;

    }

}

void MainWindow::Success()
{
    ui->SuccessLabel->show();
    QGraphicsOpacityEffect *out = new QGraphicsOpacityEffect(ui->SuccessLabel);
    ui->SuccessLabel->setGraphicsEffect(out);
    QPropertyAnimation *OpacityOut = new QPropertyAnimation(out,"opacity");
    OpacityOut->setDuration(3000);
    OpacityOut->setStartValue(1);
    OpacityOut->setEndValue(0);
    OpacityOut->setEasingCurve(QEasingCurve::OutBack);
    OpacityOut->start(QPropertyAnimation::DeleteWhenStopped);
    connect(OpacityOut,SIGNAL(finished()),this,SLOT(FadeOutLabel()));
}
void MainWindow::RecursiveCopy(const QString& Source, const QString& Target)
{
    QFileInfo SourceInfo(Source);
    if(SourceInfo.isDir())
    {
        QDir SourceDir(Source);
        QDir TargetDir(Target);
        if(!TargetDir.exists()) QDir().mkdir(Target);
        QStringList FileTypes = SourceDir.entryList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot | QDir::Hidden | QDir::System);
        for(const QString &file : FileTypes)
            if(file != CROPPED_DIR) RecursiveCopy(Combine(Source, file),Combine(Target, file));

    }
    else
    {
        if(SourceInfo.completeSuffix() == "png"){
            cv::Mat img = cv::imread(Source.toStdString()), cropped;
            cropped = cv::Mat(img, cv::Rect(0,TopCrop, img.size().width,((img.size().height-TopCrop)-BottomCrop))).clone();
            cv::imwrite(Target.toStdString(),cropped);
        }/*else if(SourceInfo.completeSuffix() == "txt")
            QFile::copy(Source,Target);*/
    }

}

bool MainWindow::IsValid()
{
    for(const std::string &folder : DIR_STRUCT)
        if(!QDir(Combine(RootPath,QString::fromStdString(folder))).exists())
            return false;
    return true;
}

QString MainWindow::Combine(const QString& First, const QString& Second)
{
    return QDir::cleanPath(First + QDir::separator() + Second);
}

void MainWindow::FadeOutLabel()
{
    ui->SuccessLabel->hide();
}

void MainWindow::on_ClearButton_clicked()
{
    ui->RootPathTextField->clear();
    ui->TopCropTextField->clear();
    ui->BottomCropTextField->clear();
}
