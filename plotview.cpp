#include "plotview.h"
#include "ui_plotview.h"

plotview::plotview(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::plotview)
{
    ui->setupUi(this);
    ui->customPlot->xAxis2->setVisible(true);
    ui->customPlot->yAxis2->setVisible(true);
//    std::vector<double> TempX, TempY;
//    for (int i=0; i<100; i++) {
//        TempX.push_back(i);
//        TempY.push_back(i*i);
//    }
//    plotDataXY(TempX, TempY);
}

plotview::~plotview()
{
    delete ui;
}

void plotview::plotData(std::vector<double> X, std::vector<double> Y, int Index)
{
    QVector<double> DataX = QVector<double>(X.begin(), X.end());
    QVector<double> DataY = QVector<double>(Y.begin(), Y.end());
    switch(Index){
    case 0:
        ui->customPlot->graph(Index)->setPen(QPen(Qt::red));
        break;
    case 1:
        ui->customPlot->graph(Index)->setPen(QPen(Qt::green));
        break;
    case 2:
        ui->customPlot->graph(Index)->setPen(QPen(Qt::blue));
        break;
    case 3:
        ui->customPlot->graph(Index)->setPen(QPen(Qt::yellow));
        break;
    case 4:
        ui->customPlot->graph(Index)->setPen(QPen(Qt::cyan));
        break;
    case 5:
        ui->customPlot->graph(Index)->setPen(QPen(Qt::magenta));
        break;
    default:
        break;
    }
    ui->customPlot->graph(Index)->addData(DataX, DataY);
//    ui->customPlot->replot();
}


void plotview::plotDataXY(std::vector<double> X, std::vector<double> Y)
{
    double Min;
    double Max;
    ui->customPlot->clearGraphs();
    //
    ui->customPlot->addGraph(ui->customPlot->xAxis, ui->customPlot->yAxis);
    Min = *std::min_element(std::begin(X),std::end(X));
    Max = *std::max_element(std::begin(X),std::end(X));
    ui->customPlot->xAxis->setRange(Min, Max);
//    ui->customPlot->xAxis->setRange(Min-0.2*std::abs(Max), Max+0.2*std::abs(Max));
    Min = *std::min_element(std::begin(Y),std::end(Y));
    Max = *std::max_element(std::begin(Y),std::end(Y));
    ui->customPlot->yAxis->setRange(Min-0.2*std::abs(Max), Max+0.2*std::abs(Max));
    plotData(X, Y, 0);
    //
    savePlot();
}

void plotview::plotDataXXY(std::vector<double> X1, std::vector<double> X2, std::vector<double> Y)
{
    double Min;
    double Max;
    ui->customPlot->clearGraphs();
    //
    ui->customPlot->addGraph(ui->customPlot->xAxis, ui->customPlot->yAxis);
    Min = *std::min_element(std::begin(X1),std::end(X1));
    Max = *std::max_element(std::begin(X1),std::end(X1));
    ui->customPlot->xAxis->setRange(Min, Max);
//    ui->customPlot->xAxis->setRange(Min-0.2*std::abs(Max), Max+0.2*std::abs(Max));
    Min = *std::min_element(std::begin(Y),std::end(Y));
    Max = *std::max_element(std::begin(Y),std::end(Y));
    ui->customPlot->yAxis->setRange(Min-0.2*std::abs(Max), Max+0.2*std::abs(Max));
    plotData(X1, Y, 0);
    //
    ui->customPlot->addGraph(ui->customPlot->xAxis2, ui->customPlot->yAxis);
    Min = *std::min_element(std::begin(X2),std::end(X2));
    Max = *std::max_element(std::begin(X2),std::end(X2));
    ui->customPlot->xAxis2->setRange(Min, Max);
//    ui->customPlot->xAxis2->setRange(Min-0.2*std::abs(Max), Max+0.2*std::abs(Max));
    Min = *std::min_element(std::begin(Y),std::end(Y));
    Max = *std::max_element(std::begin(Y),std::end(Y));
    ui->customPlot->yAxis->setRange(Min-0.2*std::abs(Max), Max+0.2*std::abs(Max));
    //
    plotData(X2, Y, 1);
    savePlot();
}

void plotview::plotDataXYY(std::vector<double> X, std::vector<double> Y1, std::vector<double> Y2)
{
    double Min;
    double Max;
    ui->customPlot->clearGraphs();
    //
    ui->customPlot->addGraph(ui->customPlot->xAxis, ui->customPlot->yAxis);
    Min = *std::min_element(std::begin(X),std::end(X));
    Max = *std::max_element(std::begin(X),std::end(X));
    ui->customPlot->xAxis->setRange(Min, Max);
//    ui->customPlot->xAxis->setRange(Min-0.2*std::abs(Max), Max+0.2*std::abs(Max));
    Min = *std::min_element(std::begin(Y1),std::end(Y1));
    Max = *std::max_element(std::begin(Y1),std::end(Y1));
    ui->customPlot->yAxis->setRange(Min-0.2*std::abs(Max), Max+0.2*std::abs(Max));
    plotData(X, Y1, 0);
    //
    ui->customPlot->addGraph(ui->customPlot->xAxis, ui->customPlot->yAxis2);
    Min = *std::min_element(std::begin(X),std::end(X));
    Max = *std::max_element(std::begin(X),std::end(X));
    ui->customPlot->xAxis->setRange(Min, Max);
//    ui->customPlot->xAxis->setRange(Min-0.2*std::abs(Max), Max+0.2*std::abs(Max));
    Min = *std::min_element(std::begin(Y2),std::end(Y2));
    Max = *std::max_element(std::begin(Y2),std::end(Y2));
    ui->customPlot->yAxis2->setRange(Min-0.2*std::abs(Max), Max+0.2*std::abs(Max));
    plotData(X, Y2, 1);
    //
    savePlot();
}

void plotview::plotDataXXYY(std::vector<double> X1, std::vector<double> X2, std::vector<double> Y1, std::vector<double> Y2)
{
    double Min;
    double Max;
    ui->customPlot->clearGraphs();
    //
    ui->customPlot->addGraph(ui->customPlot->xAxis, ui->customPlot->yAxis);
    Min = *std::min_element(std::begin(X1),std::end(X1));
    Max = *std::max_element(std::begin(X1),std::end(X1));
    ui->customPlot->xAxis->setRange(Min, Max);
//    ui->customPlot->xAxis->setRange(Min-0.2*std::abs(Max), Max+0.2*std::abs(Max));
    Min = *std::min_element(std::begin(Y1),std::end(Y1));
    Max = *std::max_element(std::begin(Y1),std::end(Y1));
    ui->customPlot->yAxis->setRange(Min-0.2*std::abs(Max), Max+0.2*std::abs(Max));
    plotData(X1, Y1, 0);
    //
    ui->customPlot->addGraph(ui->customPlot->xAxis2, ui->customPlot->yAxis2);
    Min = *std::min_element(std::begin(X2),std::end(X2));
    Max = *std::max_element(std::begin(X2),std::end(X2));
    ui->customPlot->xAxis2->setRange(Min, Max);
//    ui->customPlot->xAxis2->setRange(Min-0.2*std::abs(Max), Max+0.2*std::abs(Max));
    Min = *std::min_element(std::begin(Y2),std::end(Y2));
    Max = *std::max_element(std::begin(Y2),std::end(Y2));
    ui->customPlot->yAxis2->setRange(Min-0.2*std::abs(Max), Max+0.2*std::abs(Max));
    plotData(X2, Y2, 1);
    //
    savePlot();
}

void plotview::savePlot()
{
    std::string PlotFileName;
    PlotFileName = AutoSaveDir + "/HELLRIDE_" + getDateTimeStringNow() + "_plot.png";
    ui->customPlot->savePng(QString::fromStdString(PlotFileName), ui->customPlot->width(), ui->customPlot->height());
}


void plotview::plotData(int Index)
{
    double Min;
    double Max;
    QVector<double> DataX = QVector<double>(XData.begin(), XData.end());
    QVector<double> DataY = QVector<double>(YData.begin(), YData.end());
    QVector<double> DataX2 = QVector<double>(XData2.begin(), XData2.end());
    QVector<double> DataY2 = QVector<double>(YData2.begin(), YData2.end());
    switch(Index) {
    case BOT_LEF:
        ui->customPlot->graph(Index)->setPen(QPen(Qt::red));
        Min = *std::min_element(std::begin(XData),std::end(XData));
        Max = *std::max_element(std::begin(XData),std::end(XData));
        ui->customPlot->xAxis->setRange(Min, Max);
//        ui->customPlot->xAxis->setRange(Min-0.2*std::abs(Max), Max+0.2*std::abs(Max));
        Min = *std::min_element(std::begin(YData),std::end(YData));
        Max = *std::max_element(std::begin(YData),std::end(YData));
        ui->customPlot->yAxis->setRange(Min-0.2*std::abs(Max), Max+0.2*std::abs(Max));
        ui->customPlot->graph(Index)->addData(DataX, DataY);
        break;
    case TOP_LEF:
        ui->customPlot->graph(Index)->setPen(QPen(Qt::green));
        Min = *std::min_element(std::begin(XData2),std::end(XData2));
        Max = *std::max_element(std::begin(XData2),std::end(XData2));
        ui->customPlot->xAxis2->setRange(Min, Max);
//        ui->customPlot->xAxis2->setRange(Min-0.2*std::abs(Max), Max+0.2*std::abs(Max));
        Min = *std::min_element(std::begin(YData),std::end(YData));
        Max = *std::max_element(std::begin(YData),std::end(YData));
        ui->customPlot->yAxis->setRange(Min-0.2*std::abs(Max), Max+0.2*std::abs(Max));
        ui->customPlot->graph(Index)->addData(DataX2, DataY);
        break;
    case BOT_RIG:
        ui->customPlot->graph(Index)->setPen(QPen(Qt::blue));
        Min = *std::min_element(std::begin(XData),std::end(XData));
        Max = *std::max_element(std::begin(XData),std::end(XData));
        ui->customPlot->xAxis->setRange(Min, Max);
//        ui->customPlot->xAxis->setRange(Min-0.2*std::abs(Max), Max+0.2*std::abs(Max));
        Min = *std::min_element(std::begin(YData2),std::end(YData2));
        Max = *std::max_element(std::begin(YData2),std::end(YData2));
        ui->customPlot->yAxis2->setRange(Min-0.2*std::abs(Max), Max+0.2*std::abs(Max));
        ui->customPlot->graph(Index)->addData(DataX, DataY2);
        break;
    case TOP_RIG:
        ui->customPlot->graph(Index)->setPen(QPen(Qt::black));
        Min = *std::min_element(std::begin(XData2),std::end(XData2));
        Max = *std::max_element(std::begin(XData2),std::end(XData2));
        ui->customPlot->xAxis2->setRange(Min, Max);
//        ui->customPlot->xAxis2->setRange(Min-0.2*std::abs(Max), Max+0.2*std::abs(Max));
        Min = *std::min_element(std::begin(YData2),std::end(YData2));
        Max = *std::max_element(std::begin(YData2),std::end(YData2));
        ui->customPlot->yAxis2->setRange(Min-0.2*std::abs(Max), Max+0.2*std::abs(Max));
        ui->customPlot->graph(Index)->addData(DataX2, DataY2);
        break;
    default:
        break;
    }
}

void plotview::plotData()
{
    ui->customPlot->clearGraphs();
    ui->customPlot->addGraph(ui->customPlot->xAxis, ui->customPlot->yAxis);
    ui->customPlot->addGraph(ui->customPlot->xAxis2, ui->customPlot->yAxis);
    ui->customPlot->addGraph(ui->customPlot->xAxis, ui->customPlot->yAxis2);
    ui->customPlot->addGraph(ui->customPlot->xAxis2, ui->customPlot->yAxis2);
    ui->customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignBottom|Qt::AlignRight);
    switch(Mode) {
    case CHR_MODE_ET1_MATCH:
        this->setWindowTitle("Match ET50 transmission with prefilter transmission profile");
        ui->customPlot->xAxis->setLabel("ET50 spacing counts");
        ui->customPlot->yAxis->setLabel("Intensity counts");
        plotData(BOT_LEF);
        break;
    case CHR_MODE_ET2_MATCH:
        this->setWindowTitle("Match ET70 transmission with ET50 transmission profile");
        ui->customPlot->xAxis->setLabel("ET50 spacing counts");
        ui->customPlot->yAxis->setLabel("Intensity counts");
        plotData(BOT_LEF);
        break;
    case CHR_MODE_LINE_PROF:
        this->setWindowTitle("Match ET50 and ET70 transmission with spectral line profile");
        ui->customPlot->xAxis->setLabel("ET50 spacing counts");
        ui->customPlot->xAxis2->setLabel("ET70 spacing counts");
        ui->customPlot->yAxis->setLabel("Intensity counts");
        plotData(BOT_LEF);
        plotData(TOP_LEF);
        break;
    case CHR_MODE_LCVR1_PROF:
        this->setWindowTitle("LCVR1 Retardance vs. Voltage");
        ui->customPlot->xAxis->setLabel("Voltage in mV");
        ui->customPlot->yAxis->setLabel("Retardance in degrees");
        plotData(BOT_LEF);
        break;
    case CHR_MODE_LCVR2_PROF:
        this->setWindowTitle("LCVR2 Retardance vs. Voltage");
        ui->customPlot->xAxis->setLabel("Voltage in mV");
        ui->customPlot->yAxis->setLabel("Retardance in degrees");
        plotData(BOT_LEF);
        break;
    case CHR_MODE_ET1_PROF:
        this->setWindowTitle("ET50 transmission profile with LASER");
        ui->customPlot->xAxis->setLabel("ET50 spacing counts");
        ui->customPlot->yAxis->setLabel("Intensity counts");
        plotData(BOT_LEF);
        break;
    case CHR_MODE_ET2_PROF:
        this->setWindowTitle("ET70 transmission profile with LASER");
        ui->customPlot->xAxis->setLabel("ET70 spacing counts");
        ui->customPlot->yAxis->setLabel("Intensity counts");
        plotData(BOT_LEF);
        break;
    default:
        break;
    }
    savePlot();
}










