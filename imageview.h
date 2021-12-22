#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H

#include <QWidget>
#include "common.h"

namespace Ui {
class imageview;
}

class imageview : public QWidget
{
    Q_OBJECT

public:
    explicit imageview(QWidget *parent = nullptr);
    ~imageview();

private:
    Ui::imageview *ui;

public slots:
    void displayImage(QPixmap Pixmap,
                      int Min,
                      int Mean,
                      int Max);
};

#endif // IMAGEVIEW_H
