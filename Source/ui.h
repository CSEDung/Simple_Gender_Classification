/*
 * Dinh nghia cac doi tuong tuong tac voi nguoi dung
 */

#ifndef UI_H
#define UI_H

#include <QMainWindow>
#include <QFileDialog>
#include <humandetection.h>
#include <QTimer>
namespace Ui {
class UI;
}

class UI : public QMainWindow
{
    Q_OBJECT

public:
    explicit UI(QWidget *parent = 0);
    ~UI();

private slots:
    void on_btn_Browse_clicked();

    void on_btn_spause_clicked();

    void on_btn_stop_clicked();

    void genderEvent();

private:
    Ui::UI *ui;
    QString file;
    bool spause, stop;
    HumanDetection *detection;
    QTimer *timer;

    int GetVideoFile();

};

#endif // UI_H
