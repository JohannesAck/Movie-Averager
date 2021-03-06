#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWidget::connect(ui->pbProcessVideo, SIGNAL(clicked(bool)), this, SLOT(slotProcessVideo(bool)));
    QWidget::connect(ui->tbfilePath, SIGNAL(clicked(bool)), this, SLOT(fileDialogInput()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotProcessVideo(bool)
{
    disableInput();
    std::vector<cv::Vec3b> calculatedMeans;
    if(ui->lefilePath->text().length() != 0) {
        VideoProcessor processor(ui->lefilePath->text().toStdString());
        calculatedMeans = processor.calculateMeans(ui->cbQuickMode->isChecked());
    }
    cv::Mat* resultingImage = VideoProcessor::imageFromVector(calculatedMeans,
                                                              ui->leNrColumns->text().toInt(),
                                                              ui->leNrRows->text().toInt());

    cv::imwrite(ui->leOuputPath->text().toStdString(), *resultingImage);

    cv::imshow("Output",*resultingImage);

    cv::waitKey(0);

//    delete(resultingImage);
    enableInput();
}

void MainWindow::disableInput() {
    ui->pbProcessVideo->setEnabled(false);
    ui->lefilePath->setEnabled(false);
    ui->leNrColumns->setEnabled(false);
    ui->leNrRows->setEnabled(false);
}

void MainWindow::enableInput() {
    ui->pbProcessVideo->setEnabled(true);
    ui->lefilePath->setEnabled(true);
    ui->leNrColumns->setEnabled(true);
    ui->leNrRows->setEnabled(true);
}

void MainWindow::fileDialogInput() { //TODO: spits out errors
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Choose Input Video"), ".", tr("Video Formats (*.mkv *.mp4 *.avi)"));
    ui->lefilePath->setText(fileName);

}
