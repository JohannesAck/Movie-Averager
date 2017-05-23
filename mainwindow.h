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

    /**
     * @brief Starts processing of movie specified in input dialogue and displays result
     * Called upon pressing "Process Video" button
     */
    void slotProcessVideo(bool);

private:
    Ui::MainWindow *ui;
    /**
     * @brief Disables Input while busy.
     */
    void disableInput();
    /**
     * @brief Reenables Input.
     */
    void enableInput();
};

#endif // MAINWINDOW_H
