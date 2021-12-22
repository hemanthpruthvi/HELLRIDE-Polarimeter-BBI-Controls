#ifndef ACQUISITION_H
#define ACQUISITION_H

#include "polarimeter.h"
#include "twostages.h"
#include "rotmount.h"
#include "etalon.h"
#include "camera.h"
#include "common.h"
#include "vttnet.h"
#include "vtt.h"

class Acquisition : public QObject
{ Q_OBJECT

public:
    explicit Acquisition(QObject *parent = nullptr);
    ~Acquisition();
    //
    VTT *VTTControls;                                 // VTT instrument calibration unit
    VTTNet *VTTServer;
    Etalon *ET50;                                   // First etalon object (CA = 50 mm)
    Etalon *ET70;                                   // Second etalon object (CAm = 70 mm)
    RotMount *CWPMount;                             // Characterization wave plate mount
    Details *DataDetails;                           // Data details
    QSettings *LineSettings;                        // Line settings
    TwoStages *FilterMatrix;                        // Filter matrix object
    std::ofstream TimeStamps;                       // Time stamps for the images (*.csv)
    TwoStages *PolarimeterStages;                   // Focus stage object
    Polarimeter *LCVRPolarimeter;                   // LCVR controls object
    //
    int Mode;                                       // Mode of observation
    int LiveMode;                                   // Mode of live preview
    int Error = 0;                                  //
    std::string LineLabel;                          // Lable for the spectral line
    std::string ModeString;                         // Mode name
    std::string AutoSaveDir;                        // Auto-save top-directory
    std::string AutoSaveSubDir;                     // Auto-save subdirectory
    // Observations---------------------------------
    int NLines;                                     // Number of spectral lines to be observed
    int NCycles;                                    // Number of cycles for science/flat observations
    int NWavePoints;                                // Number of points per given spectral line
    int NModulations;                               // Number of modulations per wave point
    int NAccumulations;                             // Number of accumulations per modulation
    //
//    double FilterCWL;                               // Central wavelength of the filter
//    double FilterFWHM;                              // Wavelength passband for the filter
//    double FilterTrans;                             // Transmission of the pre-filter
    // Polarimetric calibration
    int NICUPolCalib;                               // Number of ICU polarizer positions for calibration
    int NICURetCalib;                               // NUmber of ICU retarder positions for calibration
    bool POLARIMETRY;
    // Characterization-----------------------------
    // ET-1 match / ET-1 profiling
    int ET1Start;                                   // ET50 scan start value in counts
    int ET1Step;                                    // ET50 scan step value in counts
    int ET1Stop;                                    // ET50 scan stop in counts
    int iPreFilter;                                 // Index of pre-filter
    // ET-2 match / ET-2 profiling
    int ET2Start;                                   // ET70 scan start value in counts
    int ET2Step;                                    // ET70 scan step value in counts
    int ET2Stop;                                    // ET70 scan stop in counts
    int ET1Zero;                                    // ET50 'Zero' or reference value in counts
    // Line center match
    int ET2Zero;                                    // ET70 'Zero' or reference value in counts
    double Wavelength;                              // Etalon operating wavelength in Angstrom
    double WaveStep;                                // Etalon transmission wavelength tuning step in Angstrom
    double WaveRange;                               // Etalon transmission wavelength scan range in Angstrom
    // Focus test
    double FocusStart;                              // focus stage start position in native units
    double FocusStep;                               // Focus stage scan step in native units
    double FocusStop;                               // Focus stage scan range in native units
    // LCVR1
    int LCVR1Start;                                 // LCVR1 starting voltage in millivolts
    int LCVR1Step;                                  // LCVR1 step voltage in millivolts
    int LCVR1Stop;                                  // LCVR1 stop voltage in millivolts
    int BiasCounts;
    int NPolarizer;                                 // Number of polarizer positions
    // LCVR2
    int LCVR2Start;                                 // LCVR2 starting voltage in millivolts
    int LCVR2Step;                                  // LCVR2 step voltage in millivolts
    int LCVR2Stop;                                  // LCVR2 stop voltage in millivolts
    //
    bool CAM0_LIVE_FLAG;                            // Flag to enable live preview of DetectorBBCh
    bool CAM1_LIVE_FLAG;                            // Flag to enable live preview of DetectorPCh1
    bool CAM2_LIVE_FLAG;                            // Flag to enable live preview of DetectorPCh2
    bool SAVE_LIVE_FLAG;                            // Flag to enable saving images of live preview

private:
    bool ACQ_RUN_FLAG = false;                      //
    void addLog(std::string Log);                   //
    void addLog(const char* Log);                   //
    void initAcquisition();                         // Start the acquisition
    void finishAcquisition();                       // Wrap-up the acquisition
    void loadLineSettings(QString Name);            // Load spectral line settings
    void computeRetardance(int N);                      // Fit for retardance from characterization data
    void computeRetardance();

public slots:
    void Interrupt();                               // Stop acquisition
    void startLive();                               // Save files just like that
    // Observations
    void getFlatsData();                            // Acquire flat frames
    void getDarksData();                            // Acquire dark frames
    void getPinholeData();                          // Acquire pinhole frames
    void getScienceData();                          // Acquire science data
    void getCalibrationData();                      // Acquire polarimetric calibration data
    void getTargetplateData();                      // Acquire target plate frames
    // Characterization
    void doET1Profiling();                          // Etalon-1 transmission profile with LASER
    void doET2Profiling();                          // Etalon-2 transmission profile with LASER
    void matchET1Passband();                        // Match Etalon-1 passband with pre-filter passband
    void matchET2Passband();                        // Match Etalon-2 passband with Etalon-1 passband
    void examineBestFocus();                        // Find best position for imaging lens FocusStage
    void matchETPassbandsLine();                    // Match Etalon-1 and Etalon-2 passbands with line
    void doLCVR1Characterization();                 // LCVR1 Retardance vs. Voltage
    void doLCVR2Characterization();                 // LCVR2 Retardance vs. Voltage

signals:
    void Finished();                                // Acquisition done
    void plotData(int Index);                       // Plot 1D data
    void addLog(QString Log);                       // Send log message
    void updateProgress(int Percent);               // Send progress
    void updateOProgress(int Percent);              // Send overall progress
};

#endif // ACQUISITION_H
