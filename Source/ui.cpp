#include "ui.h"
#include "ui_ui.h"

UI::UI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UI)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(genderEvent()));

}

UI::~UI()
{
    delete ui;
}

void UI::on_btn_Browse_clicked()
{
    QString f = QFileDialog::getOpenFileName(this,"Open video","../",
                "*.* All Files;; *.mp4;;*.avi;;*.vob;;*.wmv;;*.flv");
    if(f.isEmpty()) return;
    file =f;
    ui->txt_video->setText(file);
    ui->btn_spause->setText("Play");
}

int UI::GetVideoFile()
{
    detection = new HumanDetection(ui->lb_show->width(), ui->lb_show->height());
    int load = detection->setStreamVideo(file.toStdString());
    ui->lb_pfs->setText(QString::number(detection->getFPS()));
    detection->DetectionProcessing(ui->lb_show, ui->txt_sum);
    return load;
}

void UI::on_btn_spause_clicked()
{
    if(ui->btn_spause->text() == "Play" ){
        ui->btn_spause->setText("Spause");
        ui->btn_stop->setText("Stop");
        GetVideoFile();
        timer->start(10000);
    }else{
        spause = !spause;
        if(spause) ui->btn_spause->setText("Resume");
        else ui->btn_spause->setText("Spause");
        detection->setSpause(spause);
    }
}

void UI::on_btn_stop_clicked()
{
    detection->setStop(true);
    ui->btn_stop->setText("Stoped");
}

void UI::genderEvent()
{
    detection->genderEvent(ui->txt_men, ui->txt_women);
}
