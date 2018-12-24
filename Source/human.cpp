#include "human.h"

Human::Human()
{

}

Human::Human(vector<Point> contour)
{
    currentContour = contour;
    currentBoundingRect = boundingRect(currentContour);

    Point currentCenter;
    currentCenter.x = currentBoundingRect.x +
            (currentBoundingRect.x + currentBoundingRect.width) / 2;
    currentCenter.y = currentBoundingRect.y +
            (currentBoundingRect.y + currentBoundingRect.height) / 2;
    centerPositions.push_back(currentCenter);

    CurrentDiagonalSize = sqrt(pow(currentBoundingRect.width, 2) +
                               pow(currentBoundingRect.height, 2));
    CurrentAspectRatio = (float)currentBoundingRect.width /
                         (float)currentBoundingRect.height;
    StillTracked = true;
    OldOrNew = true;
    NumOfConsecutiveFramesWithoutAMatch = 0;

    //Phan biet gioi tinh
    Gendered = false;
    track = 0;
}

void Human::predictNextPosition()
{
    int numberOfPositions = centerPositions.size();
    switch(numberOfPositions){
    case 1:{
        predictedNextPosition.x = centerPositions.back().x;
        predictedNextPosition.y = centerPositions.back().y;
        break;
    }
    case 2:{
        int deltaX = centerPositions[1].x - centerPositions[0].x;
        int deltaY = centerPositions[1].y - centerPositions[0].y;
        predictedNextPosition.x = centerPositions[1].x + deltaX;
        predictedNextPosition.y = centerPositions[1].y + deltaY;
        break;
    }
    case 3:{
        int sumOfXChanges =
            ((centerPositions[2].x - centerPositions[1].x) * 2) +
            ((centerPositions[1].x - centerPositions[0].x) * 1);
        int deltaX = (int)std::round((float)sumOfXChanges / 3.0);

        int sumOfYChanges =
            ((centerPositions[2].y - centerPositions[1].y) * 2) +
            ((centerPositions[1].y - centerPositions[0].y) * 1);
        int deltaY = (int)std::round((float)sumOfYChanges / 3.0);

        predictedNextPosition.x = centerPositions[2].x + deltaX;
        predictedNextPosition.y = centerPositions[2].y + deltaY;
        break;
    }
    case 4:{
        int sumOfXChanges =
            ((centerPositions[3].x - centerPositions[2].x) * 3) +
            ((centerPositions[2].x - centerPositions[1].x) * 2) +
            ((centerPositions[1].x - centerPositions[0].x) * 1);
        int deltaX = (int)std::round((float)sumOfXChanges / 6.0);

        int sumOfYChanges =
            ((centerPositions[3].y - centerPositions[2].y) * 3) +
            ((centerPositions[2].y - centerPositions[1].y) * 2) +
            ((centerPositions[1].y - centerPositions[0].y) * 1);
        int deltaY = (int)std::round((float)sumOfYChanges / 6.0);

        predictedNextPosition.x = centerPositions[3].x + deltaX;
        predictedNextPosition.y = centerPositions[3].y + deltaY;
        break;
    }
    default:{
        int sumOfXChanges =
            ((centerPositions[numberOfPositions - 1].x - centerPositions[numberOfPositions - 2].x) * 4) +
            ((centerPositions[numberOfPositions - 2].x - centerPositions[numberOfPositions - 3].x) * 3) +
            ((centerPositions[numberOfPositions - 3].x - centerPositions[numberOfPositions - 4].x) * 2) +
            ((centerPositions[numberOfPositions - 4].x - centerPositions[numberOfPositions - 5].x) * 1);
        int deltaX = (int)std::round((float)sumOfXChanges / 10.0);

        int sumOfYChanges =
            ((centerPositions[numberOfPositions - 1].y - centerPositions[numberOfPositions - 2].y) * 4) +
            ((centerPositions[numberOfPositions - 2].y - centerPositions[numberOfPositions - 3].y) * 3) +
            ((centerPositions[numberOfPositions - 3].y - centerPositions[numberOfPositions - 4].y) * 2) +
            ((centerPositions[numberOfPositions - 4].y - centerPositions[numberOfPositions - 5].y) * 1);
        int deltaY = (int)std::round((float)sumOfYChanges / 10.0);

        predictedNextPosition.x = centerPositions[numberOfPositions - 1].x + deltaX;
        predictedNextPosition.y = centerPositions[numberOfPositions - 1].y + deltaY;
    }
    }

    // Phan biet gioi tinh
    track++;
}

int Human::getTrack()
{
    return track;
}

void Human::setImage(QImage img)
{
    image = img;
}

void Human::extractFeature()
{
    QString s = "../Data/img/0/"+QString::number(iD) + "_fea.jpg";
    image.save(s);
}

void Human::setId(int id)
{
    iD = id;
}

void Human::subFree()
{
    image.~QImage();
}
