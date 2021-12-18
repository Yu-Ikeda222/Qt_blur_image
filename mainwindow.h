#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>

#include "processimage.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    typedef void (*FUNC_POINTER)(long long, long long);
    struct data
    {
        QImage *dst;
        int size;
        FUNC_POINTER call_back;
        MainWindow main_window(QWidget *parent = nullptr);
    };
    struct data process_image_data;
    ProcessImage *process_image;
    QThread *process_image_thread;
    int progress_status;

private slots:
    void on_openButton_clicked();
    void on_blurButton_clicked();

public slots:
    void on_image_process(int);

private:
    Ui::MainWindow *ui;

signals:
    void pass_image_data(data);


};
#endif // MAINWINDOW_H
