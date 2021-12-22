#ifndef PLOTVIEW_H
#define PLOTVIEW_H

#include <QWidget>
#include <qcustomplot.h>
#include "common.h"

namespace Ui {
class plotview;
}

class plotview : public QWidget
{
    Q_OBJECT

public:
    explicit plotview(QWidget *parent = nullptr);
    ~plotview();
    std::string AutoSaveDir;
    void plotData();
    int Mode;

private:
    Ui::plotview *ui;
    void plotData(std::vector<double> X,
                  std::vector<double> Y,
                  int Index);
    void savePlot();
    void plotData(int Index);

public slots:
    void plotDataXY(std::vector<double> X,
                    std::vector<double> Y);
    void plotDataXXY(std::vector<double> X1,
                     std::vector<double> X2,
                     std::vector<double> Y);
    void plotDataXYY(std::vector<double> X,
                     std::vector<double> Y1,
                     std::vector<double> Y2);
    void plotDataXXYY(std::vector<double> X1,
                      std::vector<double> X2,
                      std::vector<double> Y1,
                      std::vector<double> Y2);
};

#endif // PLOTVIEW_H
