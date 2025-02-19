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
    int Error;                                          // Error (duh?)
    int Index;                                          // Index of camera (usually 1,2: polarimeter, 0: BBI)
    int Trigger;                                        // Select trigger type from xiApi
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
    long ImageShape[3];                                 // 3D data cube dimensions = (ImageWidth, ImageHeight, NFrames)
    bool SAVE_IMAGE_FLAG;                               // Save the image frame or not?
    unsigned int iPreFilters;                           // Index of pre-filter that is being used
    long long int MeanCountValue;                       // Mean value of the counts
    long long int NFrames;                              // Number of frames
    long long int iFrames;                              // Index of current frame
    long long int NPixel;                               // Total number of pixels per frame = ROIHeight x ROIWidth
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
    bool ACQ_RUN_FLAG;                                  // Acquisition running?
    void addLog(std::string Log);                       // Add string to log
    void addLog(const char* Log);                       // Add array of chars to log
    void initData();                                    // Initialize data writing by creating the handle
    void closeData();                                   // Finish data writing by closing the handle
    void handleError(int Error,
                     std::string Message);              // Handle the status and send error message

signals:
    void Finished();                                    // Acquisition is finished
    void addLog(QString Log);                           // Add string to log
    void displayImage(QPixmap Pixmap,
                      int Min,
                      int Mean,
                      int Max);                         // Display the pixmap image
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
