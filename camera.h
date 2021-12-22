#ifndef CAMERA_H
#define CAMERA_H

#include "common.h"

class Camera : public QObject
{ Q_OBJECT
public:
    explicit Camera(QObject *parent = nullptr);
    ~Camera();
    //
    void initDetector(QString Name);                    // Initialize detector with settings
    void prepareAcquisition();                          // Setup acquisition with given parameters
    void initAcquisition();                             // Initialize acquisition with settings
    void stopAcquisition();                             // Halt the acquisition
    void finishAcquisition();                           // Wrap up the acquisition
    void prepareLive(bool SAVE_IMAGE_FLAG_);            // Setup live preview
    void setupTrigger();                                // Setup cameras with desired trigger
    void viewImage();                                   // Get image and only display the image
    void saveImage();                                   // Get image and only save the image
    void recordImage();                                 // Get image and save & display image
    void displayImage();                                // Display acquired image
    void displayPixmap();                               // Only emit display signal
    void prepareImageDisplay();                         // Prepare image for display
    //
    int Mode;                                           // Index of the mode of operation
    int Error;                                          //
    int Index;                                          // Index of camera (usually 1,2: polarimeter, 0: BBI)
    int NPixel;                                         // Total number of pixels per frame = ROIHeight x ROIWidth
    int Trigger;                                        // Select trigger type from xiApi
    int NFrames;                                        // Number of frames
    int iFrames;                                        // Index of current frame
    int ROI;                                            // Region of interest
    int Binning;                                        // X and Y Binning
    int ROITop;                                         // ROI top pad
    int ROILeft;                                        // ROI left pad
    int ROIWidth;                                       // Frame width in pixels
    int ROIHeight;                                      // Frame height in pixel
    int BufferSize;                                     // Buffer size in MB
    int ExposureTime;                                   // Exposure time setting in us for camera
    int TriggerDelay;                                   // Extra delay to be introduced after trigger
    int MaxCountValue;                                  // Minimum value in the counts
    int MinCountValue;                                  // Maximum value in the counts
    int MeanCountValue;                                 // Mean value of the counts
    long ImageShape[3];                                 // 3D data cube dimensions = (ImageWidth, ImageHeight, NFrames)
    bool SAVE_IMAGE_FLAG;
    unsigned int iPreFilters;                           // Index of pre-filter that is being used
    XI_IMG Image;                                       // Image object from detector; oldest unread frame in the buffer queue will be read into this object.
    fitsfile *FITSFile;                                 // FITS file handle
    QThread *MainThread;                                // Record of maiin thread
    std::ofstream DATFile;                              // DAT binary file for saving data
    QPixmap DisplayPixmap;                              // Pixel map style image for display
    HANDLE Detector = NULL;                             // Detector handle for the camera
    std::string Label;                                  // Label of the camera
    std::string MakeModel;                              // Make and model of the camera
    std::string ModeString;                             // String describing the mode of operation
    std::string DATFileName;                            // Name of the binary file for saving images
    std::string FITSFileName;                           // Name of the FITS file for saving image
    std::string SerialNumber;                           // Serial number of the camera
    std::string AutoSaveDir = ".";                      // Directory to which FITS are to be saved
    std::string FileNameModeSuffix;                     // File name suffix according to acquisition mode (sc, ff, pc, dk, tg, ph)
    std::string FileNameCameraSuffix;                   // File name suffix according to camera (pol1, pol2, bbi)

public slots:
    void startLive();                                   // Start live preview
    void saveImages();                                  // Save binary images, for multi-threaded live

private:
    bool ACQ_RUN_FLAG;                                  //
    void addLog(std::string Log);                       //
    void addLog(const char* Log);                       //
    void initData();
    void closeData();
    void handleError(int Error,
                     std::string Message);              // Handle the status and send error message

signals:
    void Finished();                                    //
    void addLog(QString Log);                           //
    void displayImage(QPixmap Pixmap,
                      int Min,
                      int Mean,
                      int Max);                         //
};

/***
Define camera objects as global variables
That way they can be accessed both by observations thread and main thread
This cannot be done for all objects because Qt network objects work differently
***/

extern Camera *DetectorBBCh;
extern Camera *DetectorPCh1;
extern Camera *DetectorPCh2;

#endif // CAMERA_H
