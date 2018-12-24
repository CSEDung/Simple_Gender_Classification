#include "humandetection.h"
#include <QDebug>
HumanDetection::HumanDetection()
{
    stop = false;
    spause = false;
    counter = 0;
    c_men = 0;
    c_women = 0;
    c_save = 0;
}

HumanDetection::HumanDetection(int width, int height)
{
    h = height;
    w = width;
    stop = false;
    spause = false;
    counter = 0;
}

int HumanDetection::setStreamVideo(string video)
{
    capVideo.open(video);
    if (!capVideo.isOpened()) {
        return(1);
    }
    if (capVideo.get(CV_CAP_PROP_FRAME_COUNT) < 2) {
        return(2);
    }
    capVideo.read(imgFrame1);
    capVideo.read(imgFrame2);
    return 0;
}

void HumanDetection::setSpause(bool set)
{
    spause = set;
}

void HumanDetection::setStop(bool set)
{
    stop = set;
}

void HumanDetection::DetectionProcessing(QLabel *show, QLCDNumber *total)
{
    int fps = 1000 / getFPS();
    auto start = std::chrono::steady_clock::now( );
    bool FirstRun = true;
    while (capVideo.isOpened() && !stop) {
        if(!spause){
            start = std::chrono::steady_clock::now( );
            // Dong bo kinh thuoc video voi kich thuoc trinh chieu
            resize(imgFrame1, imgFrame1, Size(w,h));
            resize(imgFrame2, imgFrame2, Size(w,h));
            // Xu ly frame
            BlobProcessing(imgFrame1, imgFrame2, FirstRun);
            total->display(counter);
            //Hien thi frame;
            Mat S = imgFrame2.clone();
            DrawToMat(Exist, S);
            showResult(show,S);
            if ((capVideo.get(CV_CAP_PROP_POS_FRAMES) + 1)
                    < capVideo.get(CV_CAP_PROP_FRAME_COUNT)) {
                imgFrame1 = imgFrame2.clone();
                capVideo.read(imgFrame2);
            }
            else {
                stop = true;
                break;
            }
        }
        while (true){
            waitKey(1);
            auto elapsed = chrono::duration_cast<chrono::milliseconds>
                    ( chrono::steady_clock::now( ) - start );
            if(elapsed.count() > fps){
                break;
            }
        }
        if(!Exist.empty())
            FirstRun = false;
    }
}

int HumanDetection::getFPS()
{
    return (int)capVideo.get(CV_CAP_PROP_FPS);
}

void HumanDetection::genderEvent(QLCDNumber *men, QLCDNumber *women)
{
    //qDebug() << "Event";
    // Trich dac trung cac doi tuong chua phan biet gioi tinh
    vector <Human *> temp;
    for(unsigned int i =0; i<Exist.size(); i++){
        Human *p = Exist[i];
        temp.push_back(p);
        if(p->getTrack() > 10 && !p->Gendered){
            p->extractFeature();
        }
    }
    // Goi trinh trich loc dac trung CNN tu python

        //Lenh thu thi file Features.py
    QString  command("python");
    QStringList params = QStringList() << "Features.py";
    QProcess *process = new QProcess();
    process->startDetached(command, params, "../Data/");
    process->waitForFinished();
    process->close();

    // Ket thuc tien trinh python
    // Bat dau Goi SVM phan biet gioi tinh
    ifstream feature("../Data/features.csv");
    FILE *in = fopen("../Data/in","w");
    string line;
    while (getline(feature, line))
    {
        string s = "0";
        int k=0;
        for(unsigned int i=3; i<line.length(); i++){
            if(s[i] !=','){
                s += s[i];
            }else{
                s += " " +Int2String(k) + ":";
                k++;
            }
        }
        fprintf(in,s.c_str());
        fprintf(in,"\n");
    }
    fclose(in);
    SetGender();
    // Ket thuc SVM
    // Doc ket qua
    FILE *out = fopen("../Data/out","r");
    int man;
    for (unsigned int i = 0; i < temp.size(); i++)
    {
        Human *p = temp[i];
        fscanf(out,"%d",&man);
        if(man == 0){
            c_women++;
            p->isMan = false;
            women->display(c_women);
        }else{
            c_men++;
            p->isMan = true;
            men->display(c_men);
        }
        p->Gendered = true;
        p->subFree();
    }
    fclose(out);
    // Ket thuc tien trinh phan biet gioi tinh
}

char *HumanDetection::readline(FILE *input)
{
    int len;
    if(fgets(line,max_line_len,input) == NULL)
        return NULL;
    while(strrchr(line,'\n') == NULL)
    {
        max_line_len *= 2;
        line = (char *) realloc(line,max_line_len);
        len = (int) strlen(line);
        if(fgets(line+len,max_line_len-len,input) == NULL)
            break;
    }
    return line;
}

void HumanDetection::exit_input_error(int line_num)
{
    fprintf(stderr,"Wrong input format at line %d\n", line_num);
    exit(1);
}

void HumanDetection::predict(FILE *input, FILE *output)
{
    int correct = 0;
    int total = 0;
    double error = 0;
    double sump = 0, sumt = 0, sumpp = 0, sumtt = 0, sumpt = 0;

    int svm_type=svm_get_svm_type(model);
    int nr_class=svm_get_nr_class(model);
    double *prob_estimates=NULL;
    int j;

    if(predict_probability)
    {
        if (svm_type==NU_SVR || svm_type==EPSILON_SVR)
            ;//info("Prob. model for test data: target value = predicted value + z,\nz: Laplace distribution e^(-|z|/sigma)/(2sigma),sigma=%g\n",svm_get_svr_probability(model));
        else
        {
            int *labels=(int *) malloc(nr_class*sizeof(int));
            svm_get_labels(model,labels);
            prob_estimates = (double *) malloc(nr_class*sizeof(double));
            fprintf(output,"labels");
            for(j=0;j<nr_class;j++)
                fprintf(output," %d",labels[j]);
            fprintf(output,"\n");
            free(labels);
        }
    }

    max_line_len = 1024;
    line = (char *)malloc(max_line_len*sizeof(char));
    while(readline(input) != NULL)
    {
        int i = 0;
        double target_label, predict_label;
        char *idx, *val, *label, *endptr;
        int inst_max_index = -1; // strtol gives 0 if wrong format, and precomputed kernel has <index> start from 0

        label = strtok(line," \t\n");
        if(label == NULL) // empty line
            exit_input_error(total+1);

        target_label = strtod(label,&endptr);
        if(endptr == label || *endptr != '\0')
            exit_input_error(total+1);

        while(1)
        {
            if(i>=max_nr_attr-1)	// need one more for index = -1
            {
                max_nr_attr *= 2;
                x = (struct svm_node *) realloc(x,max_nr_attr*sizeof(struct svm_node));
            }

            idx = strtok(NULL,":");
            val = strtok(NULL," \t");

            if(val == NULL)
                break;
            errno = 0;
            x[i].index = (int) strtol(idx,&endptr,10);
            if(endptr == idx || errno != 0 || *endptr != '\0' || x[i].index <= inst_max_index)
                exit_input_error(total+1);
            else
                inst_max_index = x[i].index;

            errno = 0;
            x[i].value = strtod(val,&endptr);
            if(endptr == val || errno != 0 || (*endptr != '\0' && !isspace(*endptr)))
                exit_input_error(total+1);

            ++i;
        }
        x[i].index = -1;

        if (predict_probability && (svm_type==C_SVC || svm_type==NU_SVC))
        {
            predict_label = svm_predict_probability(model,x,prob_estimates);
            fprintf(output,"%g",predict_label);
            for(j=0;j<nr_class;j++)
                fprintf(output," %g",prob_estimates[j]);
            fprintf(output,"\n");
        }
        else
        {
            predict_label = svm_predict(model,x);
            fprintf(output,"%g\n",predict_label);
        }

        if(predict_label == target_label)
            ++correct;
        error += (predict_label-target_label)*(predict_label-target_label);
        sump += predict_label;
        sumt += target_label;
        sumpp += predict_label*predict_label;
        sumtt += target_label*target_label;
        sumpt += predict_label*target_label;
        ++total;
    }
    if(predict_probability)
        free(prob_estimates);
}

void HumanDetection::SetGender()
{
    FILE *input, *output;

    input = fopen("../Data/in","r");
    if(input == NULL)
    {
        exit(1);
    }

    output = fopen("../Data/out","w");
    if(output == NULL)
    {
        exit(1);
    }

    if((model=svm_load_model("../Data/model"))==0)
    {
        exit(1);
    }

    x = (struct svm_node *) malloc(max_nr_attr*sizeof(struct svm_node));
    if(predict_probability)
    {
        if(svm_check_probability_model(model)==0)
        {
            //fprintf(stderr,"Model does not support probabiliy estimates\n");
            exit(1);
        }
    }
    else
    {
        if(svm_check_probability_model(model)!=0)
            ;//info("Model supports probability estimates, but disabled in prediction.\n");
    }

    predict(input,output);
    svm_free_and_destroy_model(&model);
    free(x);
    free(line);
    fclose(input);
    fclose(output);
}

void HumanDetection::MatchCurrentWithExisting(vector<Human *> current, vector<Human *> exist)
{
    // Du bao vi tri tiep theo maf Human co the di chuyen
    for(unsigned int i = 0; i< exist.size(); i++){
        exist[i]->OldOrNew = false;
        exist[i]->predictNextPosition();
    }
    //Tim moi lien he giua cac Human hien tai va Human da co
    /*
      Khoang cach = tich vo huong cua 2 tam Human
      Human nao da co nao gan nhat voi Human hien tai duoc xem la vi tri truoc kia cua Human do
     */
    for(unsigned int i = 0; i< current.size(); i++){
        int MinDistanceIndex = 0;
        double MinDistance = 100000.0;
        for(unsigned int j = 0; j< exist.size(); j++){
            if(exist[j]->StillTracked){
                double Distance = DistanceTwoPoints(current[i]->centerPositions.back(),
                                                    exist[j]->predictedNextPosition);
                if(Distance < MinDistance){
                    MinDistance = Distance;
                    MinDistanceIndex = j;
                }
            }
        }
        /*
         Neu lon hon do dai duong cheo cua khung bao thi xem nhu Human moi
         */
        if(MinDistance < current[i]->CurrentDiagonalSize){
            UpdateExisting(current[i],exist,MinDistanceIndex);
        }
        else{
            AddNewHuman(current[i]);
            counter++;

        }
    }
    // Ra khoi vung quan sat
    for(unsigned int i = 0; i< exist.size(); i++){
        if(!exist[i]->OldOrNew){
            exist[i]->NumOfConsecutiveFramesWithoutAMatch ++;
        }
        if(exist[i]->NumOfConsecutiveFramesWithoutAMatch > 40){
            exist[i]->StillTracked = false;
        }
    }
}

void HumanDetection::UpdateExisting(Human *current, vector<Human *> exist, int index)
{
    exist[index]->currentContour = current->currentContour;
    exist[index]->currentBoundingRect = current->currentBoundingRect;
    exist[index]->centerPositions.push_back(current->centerPositions.back());
    exist[index]->CurrentDiagonalSize = current->CurrentDiagonalSize;
    exist[index]->CurrentAspectRatio = current->CurrentAspectRatio;
    exist[index]->StillTracked = true;
    exist[index]->OldOrNew = true;
}

void HumanDetection::AddNewHuman(Human *current)
{
    current->OldOrNew = true;
    Exist.push_back(current);

}

void HumanDetection::DrawToMat(vector<Human *> exist, Mat frame)
{
    for(unsigned int i= 0; i < exist.size(); i++){
        if(exist.at(i)->StillTracked){
            Rect r = exist.at(i)->currentBoundingRect;
            rectangle(frame, r, Scalar(0, 255, 0));
/*
 * Xuat du lieu xay dung bo du lieu huan luyen SVM phan biet gioi tinh
            //Mat cut = imgFrame2(r);
            //imshow("Cut",cut);
            //waitKey(1);

            QImage img((unsigned char*) imgFrame2.data, imgFrame2.cols, imgFrame2.rows,
                       QImage::Format_RGB888);
            img = img.rgbSwapped();
            QImage s = img.copy(r.x,r.y,r.width,r.height);
            QString name = "img/name_"+QString::fromStdString(Int2String(c_save)+Int2String(i))+".png";
            s.save(name);
            // Ket thuc xuat du lieu
*/
/* Tien trinh xu ly phan biet gioi tinh
 * Lay khung anh theo doi thu X de phan biet gioi tinh
 */
            if(exist.at(i)->getTrack() == 10){
                QImage img((unsigned char*) imgFrame2.data, imgFrame2.cols, imgFrame2.rows,
                           QImage::Format_RGB888);
                img = img.rgbSwapped();
                QImage s = img.copy(r.x,r.y,r.width,r.height);
                exist.at(i)->setImage(s);
            }
        }
    }
    c_save++;
}

void HumanDetection::showResult(QLabel *show, Mat frame)
{
    QImage img((unsigned char*) frame.data, frame.cols, frame.rows,
               QImage::Format_RGB888);
    img = img.rgbSwapped();
    QPixmap pixmap = QPixmap::fromImage(img);
    show->setPixmap(pixmap);
}

double HumanDetection::DistanceTwoPoints(Point A, Point B)
{
    int x = pow((A.x - B.x),2);
    int y = pow((A.y - B.y),2);
    return sqrt(x+y);
}

void HumanDetection::BlobProcessing(Mat Frame1, Mat Frame2, bool first)
{
    Mat frame1 = Frame1.clone();
    Mat frame2 = Frame2.clone();
    Mat Difference; // Ket qua tru nen ABSDIFF
    Mat Thresh; // Ket qua phan nguong
    vector<Human*> Current;

    cvtColor(frame1, frame1, CV_RGB2GRAY);
    cvtColor(frame2, frame2, CV_RGB2GRAY);
    GaussianBlur(frame1, frame1, Size(5, 5), 0);
    GaussianBlur(frame2, frame2, Size(5, 5), 0);
    absdiff(frame1, frame2,Difference);
    //imshow("DIFF",Difference);
    threshold(Difference,Thresh,16, 255, CV_THRESH_BINARY);
    Mat StructuringElement = getStructuringElement(MORPH_RECT, Size(5,5));
    dilate(Thresh, Thresh, StructuringElement); // Phep gian no
    dilate(Thresh, Thresh, StructuringElement); // Phep gian no
    erode(Thresh, Thresh, StructuringElement); // Phep an mon
    //imshow("THRESH",Thresh);
    vector <vector<Point> > contours;
    findContours(Thresh,contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    drawContours(Thresh, contours, -1, Scalar(255,255,255), -1);
    vector <vector<Point> > convexHulls(contours.size());
    for(unsigned int i=0; i< contours.size(); i++){
        convexHull(contours[i], convexHulls[i]);
    }
    for(unsigned int i=0; i<convexHulls.size();i++){
        Human *temp= new Human(convexHulls[i]);
        if(//temp->currentBoundingRect.y < h/2 - temp->currentBoundingRect.height &&
            temp->CurrentAspectRatio > 0.3 &&// goi y thay doi theo tung video
            temp->CurrentAspectRatio < 0.5 &&
            temp->currentBoundingRect.width > 50 &&
            temp->currentBoundingRect.height > 85 &&
            (contourArea(temp->currentContour) /
            (double)temp->currentBoundingRect.area()) > 0.1){
                Current.push_back(temp);
        }
    }

    if(first){
        for(unsigned int i=0; i< Current.size(); i++){
            Exist.push_back(Current[i]);
            counter++;
        }
    }else{
        MatchCurrentWithExisting(Current, Exist);
    }
    Current.clear();
}

string HumanDetection::Int2String(int n)
{
    ostringstream oOStrStream;
        oOStrStream << n;
        return oOStrStream.str();
}
