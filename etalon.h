#ifndef ETALON_H
#define ETALON_H

#include "common.h"

class Etalon : public QObject
{ Q_OBJECT

public:
    explicit Etalon(QObject *parent = nullptr);
    ~Etalon();
    void initEtalon(QString Name);                          //
    void tuneWavelength();                                  // Tune the etalon spacing to equivalent "ZCounts"
    void resetEtalon();                                     // Reset etalon
    void resetXYParallelism();                              // Reset etalon parallelism
    void getCurrentStatus();                                // Current values
    void gotoScanStartPosition();                           // Set the spacing to the point of beginning of the line scan
    void sendCommand();                                     // Send ASCII command to the controller
    //
    std::string Label = "";                                 // Assigned name for the object after creation
    QString TCPHostName = "192.168.90.116";                 // IP address of the device
    quint16 TCPPortNumber = 10001;                          // Port number of the device
    double ZSpacing = 1101;                                 // Spacing between plates in um
    double ZScanRange = 5.52;                               // Spacing scan range in um
    double Wavelength = 6328;                               // Line wavelength in A
    //
    int Error = 0;                                          //
    int NWavePoints;                                        // Number of wavelength points to be scanned
    double WaveScanRange;                                   // Wavelength scan range in Angstrom
    std::string Command = "";                               // ASCII command string to control device
    std::string CommandPreFix = "I1000P1P0I2000P1P0";       // String to be appended before tune command, so that X and Y parallelisms are explicitly set to 0
    std::string Response = "";                              // Response from the controller
    double WaveScan = 0.050;                                // Line scan step in A
    double XParallel = 0;                                   // X parallelism in counts
    double YParallel = 0;                                   // Y parallelism in counts
    double ZCounts = 0;                                     // Z tuning counts +/- 2048 counts for +/- tuning range
    double ZStep = 4096.0*(ZSpacing/ZScanRange)*
            (WaveScan/Wavelength);                          // Counts per step
    double ZZero = 0;                                       // Reference counts for scanning
    bool Operating = true;                                  // Is it in operating mode or balanced/error mode?

private:
    QTcpSocket *TCPSocket;                                  // TCP-IP socket for conecting to device
    void handleError(int Err,
                     std::string Message);                  //
    void addLog(std::string Log);                           //
    void addLog(const char* Log);
    //
    void generateCommandFromCounts();                       // Create controller compatible commands from counts
    double ResponseTime;                                    // Etalon response time 0.5/1.0/2.0 ms
    double XCounts = 0;                                     // X parallelism counts +/- 2048 counts for +/- 1000 nm
    double YCounts = 0;                                     // Y parallelism counts +/- 2048 counts for +/- 1000 nm

public slots:
    void readyRead();                                       // Received response is read and some actions corresponding to that
    void scanWavelength();                                  // Tune the etalon spacing by equivalent "WaveScan"

signals:
    void addLog(QString Log);                               //
};

#endif // ETALON_H
