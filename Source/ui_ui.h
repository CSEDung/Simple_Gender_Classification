/********************************************************************************
** Form generated from reading UI file 'ui.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UI_H
#define UI_UI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UI
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_2;
    QLabel *lb_show;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox_3;
    QRadioButton *radioButton;
    QLineEdit *txt_video;
    QPushButton *btn_Browse;
    QGroupBox *groupBox_6;
    QPushButton *btn_spause;
    QPushButton *btn_stop;
    QGroupBox *groupBox_4;
    QLabel *label;
    QLCDNumber *txt_sum;
    QLCDNumber *txt_men;
    QLabel *label_2;
    QLCDNumber *txt_women;
    QLabel *label_3;
    QGroupBox *groupBox_5;
    QLabel *label_5;
    QLabel *lb_pfs;

    void setupUi(QMainWindow *UI)
    {
        if (UI->objectName().isEmpty())
            UI->setObjectName(QStringLiteral("UI"));
        UI->resize(1200, 650);
        UI->setLayoutDirection(Qt::LeftToRight);
        centralWidget = new QWidget(UI);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        horizontalLayout_2 = new QHBoxLayout(groupBox);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        lb_show = new QLabel(groupBox);
        lb_show->setObjectName(QStringLiteral("lb_show"));

        horizontalLayout_2->addWidget(lb_show);


        horizontalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy);
        groupBox_2->setMaximumSize(QSize(200, 16777215));
        verticalLayout = new QVBoxLayout(groupBox_2);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        groupBox_3 = new QGroupBox(groupBox_2);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setMinimumSize(QSize(0, 120));
        groupBox_3->setMaximumSize(QSize(16777215, 120));
        radioButton = new QRadioButton(groupBox_3);
        radioButton->setObjectName(QStringLiteral("radioButton"));
        radioButton->setGeometry(QRect(10, 30, 112, 23));
        radioButton->setChecked(true);
        txt_video = new QLineEdit(groupBox_3);
        txt_video->setObjectName(QStringLiteral("txt_video"));
        txt_video->setGeometry(QRect(10, 60, 161, 25));
        btn_Browse = new QPushButton(groupBox_3);
        btn_Browse->setObjectName(QStringLiteral("btn_Browse"));
        btn_Browse->setGeometry(QRect(80, 90, 89, 25));

        verticalLayout->addWidget(groupBox_3);

        groupBox_6 = new QGroupBox(groupBox_2);
        groupBox_6->setObjectName(QStringLiteral("groupBox_6"));
        groupBox_6->setMinimumSize(QSize(0, 60));
        groupBox_6->setMaximumSize(QSize(16777215, 60));
        btn_spause = new QPushButton(groupBox_6);
        btn_spause->setObjectName(QStringLiteral("btn_spause"));
        btn_spause->setGeometry(QRect(10, 30, 91, 25));
        btn_stop = new QPushButton(groupBox_6);
        btn_stop->setObjectName(QStringLiteral("btn_stop"));
        btn_stop->setGeometry(QRect(110, 30, 61, 25));

        verticalLayout->addWidget(groupBox_6);

        groupBox_4 = new QGroupBox(groupBox_2);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setMinimumSize(QSize(0, 220));
        groupBox_4->setMaximumSize(QSize(16777215, 220));
        label = new QLabel(groupBox_4);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 30, 67, 17));
        txt_sum = new QLCDNumber(groupBox_4);
        txt_sum->setObjectName(QStringLiteral("txt_sum"));
        txt_sum->setGeometry(QRect(43, 50, 121, 31));
        txt_men = new QLCDNumber(groupBox_4);
        txt_men->setObjectName(QStringLiteral("txt_men"));
        txt_men->setGeometry(QRect(43, 110, 121, 31));
        label_2 = new QLabel(groupBox_4);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 90, 67, 17));
        txt_women = new QLCDNumber(groupBox_4);
        txt_women->setObjectName(QStringLiteral("txt_women"));
        txt_women->setGeometry(QRect(43, 170, 121, 31));
        label_3 = new QLabel(groupBox_4);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 150, 67, 17));

        verticalLayout->addWidget(groupBox_4);

        groupBox_5 = new QGroupBox(groupBox_2);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        label_5 = new QLabel(groupBox_5);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(10, 30, 67, 17));
        lb_pfs = new QLabel(groupBox_5);
        lb_pfs->setObjectName(QStringLiteral("lb_pfs"));
        lb_pfs->setGeometry(QRect(50, 30, 67, 17));

        verticalLayout->addWidget(groupBox_5);


        horizontalLayout->addWidget(groupBox_2);

        UI->setCentralWidget(centralWidget);

        retranslateUi(UI);

        QMetaObject::connectSlotsByName(UI);
    } // setupUi

    void retranslateUi(QMainWindow *UI)
    {
        UI->setWindowTitle(QApplication::translate("UI", "Human Counter", Q_NULLPTR));
        groupBox->setTitle(QString());
        lb_show->setText(QString());
        groupBox_2->setTitle(QString());
        groupBox_3->setTitle(QApplication::translate("UI", "Source", Q_NULLPTR));
        radioButton->setText(QApplication::translate("UI", "From file:", Q_NULLPTR));
        btn_Browse->setText(QApplication::translate("UI", "Browse", Q_NULLPTR));
        groupBox_6->setTitle(QApplication::translate("UI", "Controller", Q_NULLPTR));
        btn_spause->setText(QApplication::translate("UI", "Play", Q_NULLPTR));
        btn_stop->setText(QApplication::translate("UI", "Stoped", Q_NULLPTR));
        groupBox_4->setTitle(QApplication::translate("UI", "Processing", Q_NULLPTR));
        label->setText(QApplication::translate("UI", "Counter:", Q_NULLPTR));
        label_2->setText(QApplication::translate("UI", "Men:", Q_NULLPTR));
        label_3->setText(QApplication::translate("UI", "Women:", Q_NULLPTR));
        groupBox_5->setTitle(QApplication::translate("UI", "Information", Q_NULLPTR));
        label_5->setText(QApplication::translate("UI", "Fps:", Q_NULLPTR));
        lb_pfs->setText(QApplication::translate("UI", "0", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class UI: public Ui_UI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UI_H
