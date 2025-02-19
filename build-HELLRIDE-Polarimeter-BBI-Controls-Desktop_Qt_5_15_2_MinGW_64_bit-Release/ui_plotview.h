/********************************************************************************
** Form generated from reading UI file 'plotview.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLOTVIEW_H
#define UI_PLOTVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_plotview
{
public:
    QCustomPlot *customPlot;

    void setupUi(QWidget *plotview)
    {
        if (plotview->objectName().isEmpty())
            plotview->setObjectName(QString::fromUtf8("plotview"));
        plotview->resize(800, 600);
        customPlot = new QCustomPlot(plotview);
        customPlot->setObjectName(QString::fromUtf8("customPlot"));
        customPlot->setGeometry(QRect(0, 0, 800, 600));

        retranslateUi(plotview);

        QMetaObject::connectSlotsByName(plotview);
    } // setupUi

    void retranslateUi(QWidget *plotview)
    {
        plotview->setWindowTitle(QCoreApplication::translate("plotview", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class plotview: public Ui_plotview {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLOTVIEW_H
