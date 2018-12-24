#ifndef HUMAN_H
#define HUMAN_H
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QImage>

using namespace std;
using namespace cv;

class Human
{
public:
    Human();
    Human(vector<Point> contour);

    // Tap hop cac diem duong vien
    vector<Point> currentContour;

    // Tap hop cac diem trung tam
    vector<Point> centerPositions;

    // Khung bao chua doi tuong
    Rect currentBoundingRect;

    // Kich thuoc duong cheo cua khung bao doi tuong
    double CurrentDiagonalSize;

    // Ti le w/h
    double CurrentAspectRatio;

    // Xac dinh co nguoi moi xuat hien hay khong
    bool OldOrNew;

    // Dang trong vung quan sat
    bool StillTracked;

    // So frame lien tiep khong tim thay doi tuong nay
    int NumOfConsecutiveFramesWithoutAMatch;

    // Du doan vi tri ke tiep
    Point predictedNextPosition;
    void predictNextPosition();

    // Phan biet gioi tinh
    int iD;
    QImage image; // hinh anh dung phan biet gioi tinh
    bool isMan;
    bool Gendered;
    int track;
    int getTrack(); //Lay so khung hinh da theo doi
    void setImage(QImage img);
    void extractFeature();
    void setId(int id);
    void subFree();
};

#endif // HUMAN_H
