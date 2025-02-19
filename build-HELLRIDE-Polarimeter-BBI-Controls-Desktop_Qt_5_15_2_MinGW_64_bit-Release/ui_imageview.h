/********************************************************************************
** Form generated from reading UI file 'imageview.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGEVIEW_H
#define UI_IMAGEVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_imageview
{
public:
    QLabel *labelImage;
    QLabel *labelMin;
    QLabel *labelMean;
    QLabel *labelMax;
    QLineEdit *lineEditMin;
    QLineEdit *lineEditMean;
    QLineEdit *lineEditMax;

    void setupUi(QWidget *imageview)
    {
        if (imageview->objectName().isEmpty())
            imageview->setObjectName(QString::fromUtf8("imageview"));
        imageview->resize(800, 840);
        labelImage = new QLabel(imageview);
        labelImage->setObjectName(QString::fromUtf8("labelImage"));
        labelImage->setGeometry(QRect(0, 30, 800, 800));
        labelImage->setAlignment(Qt::AlignCenter);
        labelMin = new QLabel(imageview);
        labelMin->setObjectName(QString::fromUtf8("labelMin"));
        labelMin->setGeometry(QRect(0, 10, 60, 20));
        labelMin->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        labelMean = new QLabel(imageview);
        labelMean->setObjectName(QString::fromUtf8("labelMean"));
        labelMean->setGeometry(QRect(140, 10, 60, 20));
        labelMean->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        labelMax = new QLabel(imageview);
        labelMax->setObjectName(QString::fromUtf8("labelMax"));
        labelMax->setGeometry(QRect(280, 10, 60, 20));
        labelMax->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEditMin = new QLineEdit(imageview);
        lineEditMin->setObjectName(QString::fromUtf8("lineEditMin"));
        lineEditMin->setGeometry(QRect(60, 10, 60, 20));
        lineEditMin->setReadOnly(true);
        lineEditMean = new QLineEdit(imageview);
        lineEditMean->setObjectName(QString::fromUtf8("lineEditMean"));
        lineEditMean->setGeometry(QRect(200, 10, 60, 20));
        lineEditMean->setReadOnly(true);
        lineEditMax = new QLineEdit(imageview);
        lineEditMax->setObjectName(QString::fromUtf8("lineEditMax"));
        lineEditMax->setGeometry(QRect(340, 10, 60, 20));
        lineEditMax->setReadOnly(true);

        retranslateUi(imageview);

        QMetaObject::connectSlotsByName(imageview);
    } // setupUi

    void retranslateUi(QWidget *imageview)
    {
        imageview->setWindowTitle(QCoreApplication::translate("imageview", "Form", nullptr));
        labelImage->setText(QCoreApplication::translate("imageview", "Waiting for the image...", nullptr));
        labelMin->setText(QCoreApplication::translate("imageview", "Minimum", nullptr));
        labelMean->setText(QCoreApplication::translate("imageview", "Mean", nullptr));
        labelMax->setText(QCoreApplication::translate("imageview", "Maximum", nullptr));
    } // retranslateUi

};

namespace Ui {
    class imageview: public Ui_imageview {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGEVIEW_H
