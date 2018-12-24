/*
 *https://www.learnopencv.com/blob-detection-using-opencv-python-c/
 */

#ifndef HumanDetection_H
#define HumanDetection_H
#include <svm.h>
#include <QLabel>
#include <human.h>
#include <iostream>
#include <fstream>
#include <chrono>
#include <QLCDNumber>
#include <QProcess>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/objdetect/objdetect.hpp"

using namespace std;
using namespace cv;

class HumanDetection
{
public:
    HumanDetection();
    HumanDetection(int width, int height);
    int setStreamVideo(string video);
    void setSpause(bool set);
    void setStop(bool set);
    // Tien trinh xu ly chung
    void DetectionProcessing(QLabel *show, QLCDNumber *total);
    // Tra ve FPS cua video hien tai
    int getFPS();

    /*
     * Bat dau qua trinh xu ly SVM phan biet nam nu
     * */
    void genderEvent(QLCDNumber *men, QLCDNumber *women);

private:
    VideoCapture capVideo; // Video duoc truyen vao xu ly
    bool stop, spause; // Gia tri dieu khien video
    int w, h; // Kich thuoc khung trinh chieu
    int counter, c_men, c_women; // Dem so Human da xuat hien, nam, nu
    Mat imgFrame1;
    Mat imgFrame2;
    vector<Human*> Exist; // Danh sach cac Human da tung xuat hien trong vung quan sat

    // Kiem tra ton tai Human
    void MatchCurrentWithExisting(vector<Human*> current, vector<Human*> exist);
    //Cap nhat thong tin Human
    void UpdateExisting(Human* current, vector<Human*> exist, int index);
    // Them mot Human moi
    void AddNewHuman(Human* current);
    // Hien thi thong tin xu ly lien Frame trinh chieu
    void DrawToMat(vector <Human*> exist, Mat frame);
    // Hien thi ket qua
    void showResult(QLabel *show, Mat frame);
    // Khoan cach AB theo tich vo huong
    double DistanceTwoPoints(Point A, Point B);
    // Qua trinh xu ly cua giai thuat Blob tren OpenCV
    void BlobProcessing(Mat Frame1, Mat Frame2, bool first);
    CascadeClassifier face_cascade;

    string Int2String(int n);
    int c_save; // Bien dem dung dat ten file khi xuat du lieu anh tu video trong qua trinh training

    /*
     * Bat dau qua trinh xu ly SVM phan biet nam nu
     * */
    struct svm_node *x;
    int max_nr_attr;

    struct svm_model* model;
    int predict_probability;

    char *line = NULL;
    int max_line_len;

    char* readline(FILE *input);
    void exit_input_error(int line_num);
    void predict(FILE *input, FILE *output);
    void SetGender();

};

#endif // HumanDetection_H
