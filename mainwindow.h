#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <videoprocessor.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void slotProcessVideo(bool);

private:
    Ui::MainWindow *ui;
    void disableInput();
    void enableInput();
};

#endif // MAINWINDOW_H
