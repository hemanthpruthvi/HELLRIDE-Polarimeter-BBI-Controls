#include "imageview.h"
#include "ui_imageview.h"

imageview::imageview(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::imageview)
{
    ui->setupUi(this);
}

imageview::~imageview()
{
    delete ui;
}

void imageview::displayImage(QPixmap Pixmap, int Min, int Mean, int Max)
{
    ui->labelImage->setPixmap(Pixmap);
    ui->lineEditMin->setText(QString::number(Min));
    ui->lineEditMean->setText(QString::number(Mean));
    ui->lineEditMax->setText(QString::number(Max));
}
